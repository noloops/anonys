"""Code generator for Anonys C++ FSM framework."""

from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

from .parser import Declaration, FsmDefinition, State


@dataclass
class GeneratorConfig:
    """Configuration for a code generation run."""
    fsm_definitions: list[Path]     # Paths to .txt definition files
    anonys_output_dir: str          # e.g. "../Example2/src/" (anonys/ appended automatically)
    fsm_output_dir: str             # e.g. "../Example2/src/Fsm"
    project_name: str               # e.g. "EXAMPLE1" or "EXAMPLE2" for include guards


def generate(config: GeneratorConfig) -> None:
    """Run the complete code generation."""
    from .parser import parse_definition

    fsm_defs: list[FsmDefinition] = []
    for path in config.fsm_definitions:
        fsm_defs.append(parse_definition(path))

    base_dir = Path(config.anonys_output_dir)
    anonys_dir = base_dir / "anonys"
    fsm_header_dir = anonys_dir / "fsm"
    impl_dir = anonys_dir / "impl"
    fsm_cpp_dir = Path(config.fsm_output_dir)

    # Ensure output directories exist
    for d in [anonys_dir, fsm_header_dir, impl_dir, fsm_cpp_dir]:
        d.mkdir(parents=True, exist_ok=True)

    # Collect all unique events across all FSMs
    all_events = _collect_unique_events(fsm_defs)

    # Determine max timeouts needed
    max_timeouts = _max_timeouts(fsm_defs)

    # Generate cross-FSM files
    _write_event_id_h(anonys_dir / "EventId.h", config.project_name, all_events, max_timeouts)
    _write_fsm_id_h(anonys_dir / "FsmId.h", config.project_name, fsm_defs)
    _write_generated_config_h(anonys_dir / "GeneratedConfig.h", config.project_name)
    _write_fsm_pool_h(anonys_dir / "FsmPool.h", config.project_name, fsm_defs)
    _write_fsm_pool_cpp(anonys_dir / "FsmPool.cpp", fsm_defs)

    # Generate per-FSM files
    for fsm_idx, fsm_def in enumerate(fsm_defs):
        _write_terminals_h(impl_dir / f"terminals{fsm_def.name}.h", config.project_name, fsm_idx, fsm_def)
        _write_handlers_h(impl_dir / f"handlers{fsm_def.name}.h", config.project_name, fsm_idx, fsm_def)
        _write_fsm_struct_h(fsm_header_dir / f"{fsm_def.name}.h", config.project_name, fsm_idx, fsm_def)

        # Generate per-state .cpp files
        _generate_state_cpps(fsm_cpp_dir, fsm_idx, fsm_def)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _collect_unique_events(fsm_defs: list[FsmDefinition]) -> list[Declaration]:
    """Collect unique event declarations across all FSMs, preserving order."""
    seen: set[str] = set()
    result: list[Declaration] = []
    for fsm_def in fsm_defs:
        for decl in fsm_def.get_events():
            if decl.namespace_path not in seen:
                seen.add(decl.namespace_path)
                result.append(decl)
    return result


def _max_timeouts(fsm_defs: list[FsmDefinition]) -> int:
    """Find the maximum number of timeouts used by any single state."""
    m = 0
    for fsm_def in fsm_defs:
        for s in fsm_def.all_states_flat():
            m = max(m, s.num_timeouts)
    return m


def _state_id_map(fsm_def: FsmDefinition) -> dict[str, int]:
    """Assign sequential state IDs (starting from 1) in definition order."""
    flat = fsm_def.all_states_flat()
    return {s.name: i + 1 for i, s in enumerate(flat)}


def _ns(fsm_idx: int, state_id: int) -> str:
    """Namespace for a state: anonys_F_S."""
    return f"anonys_{fsm_idx}_{state_id}"


def _fsm_ns(fsm_idx: int) -> str:
    """Namespace for FSM terminals: anonys_F."""
    return f"anonys_{fsm_idx}"


# ---------------------------------------------------------------------------
# EventId.h
# ---------------------------------------------------------------------------

def _write_event_id_h(path: Path, project: str, events: list[Declaration], max_timeouts: int) -> None:
    guard = f"{project}_ANONYS_EVENTID_H"
    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append('#include "anonys/Types.h"')
    lines.append("")

    # Forward declarations grouped by namespace
    _write_event_forward_decls(lines, events)

    lines.append("namespace anonys")
    lines.append("{")

    # Timeout classes — always generate 4
    num_timeout_classes = max(max_timeouts, 4)
    for i in range(1, num_timeout_classes + 1):
        lines.append(f"\tclass Timeout{i} {{}};")
    lines.append("")

    # Event ID template
    lines.append("\ttemplate <typename T> constexpr EventId getEventId() = delete;")
    for i, ev in enumerate(events):
        lines.append(f"\ttemplate <>\tconstexpr EventId getEventId<{ev.cpp_qualified}>() {{ return {i}; }}")
    lines.append("")

    # Timeout event IDs
    lines.append("\ttemplate <typename T> constexpr EventId getTimeoutEventId() = delete;")
    for i in range(1, num_timeout_classes + 1):
        lines.append(f"\ttemplate <>\tconstexpr EventId getTimeoutEventId<Timeout{i}>() {{ return {60000 + i}; }}")
    lines.append("\tstatic_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);")

    lines.append("}")
    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


def _write_event_forward_decls(lines: list[str], events: list[Declaration]) -> None:
    """Write forward declarations for event types, grouped by namespace."""
    # Group events by namespace
    ns_groups: dict[str, list[Declaration]] = {}
    for ev in events:
        ns = ev.cpp_namespace
        ns_groups.setdefault(ns, []).append(ev)

    for ns, decls in ns_groups.items():
        if not ns:
            # Global namespace
            for d in decls:
                lines.append(f"{d.kind} {d.cpp_type_name};")
        else:
            # Nested namespace
            lines.append(f"namespace {ns} {{ {'; '.join(f'{d.kind} {d.cpp_type_name}' for d in decls)}; }}")
    lines.append("")


# ---------------------------------------------------------------------------
# FsmId.h
# ---------------------------------------------------------------------------

def _write_fsm_id_h(path: Path, project: str, fsm_defs: list[FsmDefinition]) -> None:
    guard = f"{project}_ANONYSFSMID_H"
    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append("#include <cstdint>")
    lines.append("")
    lines.append("namespace anonys")
    lines.append("{")
    lines.append("\tenum class FsmId : uint16_t {")
    for i, fsm_def in enumerate(fsm_defs):
        lines.append(f"\t\t{fsm_def.name} = {i},")
    lines.append(f"\t\tCount_ = {len(fsm_defs)}")
    lines.append("\t};")
    lines.append("}")
    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


# ---------------------------------------------------------------------------
# GeneratedConfig.h
# ---------------------------------------------------------------------------

def _write_generated_config_h(path: Path, project: str) -> None:
    guard = f"{project}_ANONYS_GENERATEDCONFIG_H"
    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append("#include <cstdint>")
    lines.append("")
    lines.append("namespace anonys")
    lines.append("{")
    lines.append("\tconstexpr int32_t MaxNestedStates{ 8 };")
    lines.append("}")
    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


# ---------------------------------------------------------------------------
# terminals*.h
# ---------------------------------------------------------------------------

def _write_terminals_h(path: Path, project: str, fsm_idx: int, fsm_def: FsmDefinition) -> None:
    guard = f"{project}_ANONYS_TERMINALS_{fsm_def.name.upper()}_H"
    ns = _fsm_ns(fsm_idx)
    terminals = fsm_def.get_terminals()  # all terminal declarations

    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append('#include "anonys/Timer.h"')
    lines.append("")

    # Forward declarations for terminal types
    _write_terminal_forward_decls(lines, terminals)

    lines.append(f"namespace {ns} {{")
    lines.append("\tstruct Terminals {")
    lines.append("\t\tanonys::TimerCore* pTimer;")
    for t in terminals:
        lines.append(f"\t\t{t.cpp_qualified}* {t.ptr_name};")
    lines.append("\t};")
    lines.append("}")
    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


def _write_terminal_forward_decls(lines: list[str], terminals: list[Declaration]) -> None:
    """Write forward declarations for terminal types, grouped by namespace."""
    ns_groups: dict[str, list[Declaration]] = {}
    for t in terminals:
        ns = t.cpp_namespace
        ns_groups.setdefault(ns, []).append(t)

    for ns, decls in ns_groups.items():
        if not ns:
            for d in decls:
                lines.append(f"{d.kind} {d.cpp_type_name};")
        else:
            lines.append(f"namespace {ns} {{ {'; '.join(f'{d.kind} {d.cpp_type_name}' for d in decls)}; }}")
    lines.append("")


# ---------------------------------------------------------------------------
# handlers*.h
# ---------------------------------------------------------------------------

def _write_handlers_h(path: Path, project: str, fsm_idx: int, fsm_def: FsmDefinition) -> None:
    guard = f"{project}_ANONYS_HANDLERS_{fsm_def.name.upper()}_H"
    flat = fsm_def.all_states_flat()
    id_map = _state_id_map(fsm_def)

    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append('#include "anonys/Types.h"')
    lines.append('#include "anonys/Utils.h"')
    lines.append("")
    lines.append(f'#include "terminals{fsm_def.name}.h"')

    for state in flat:
        sid = id_map[state.name]
        ns = _ns(fsm_idx, sid)
        lines.append("")
        lines.append(f"namespace {ns} {{")
        lines.append("\tuint16_t getMembersSize();")
        lines.append("\tvoid liveCycle(bool create, void* pTerminals, void* pMembers);")
        lines.append("\tconst anonys::StateDef* handleEvent(void* pMembers, anonys::Event& event);")
        lines.append("}")

    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


# ---------------------------------------------------------------------------
# fsm/FsmName.h (StateDef struct)
# ---------------------------------------------------------------------------

def _write_fsm_struct_h(path: Path, project: str, fsm_idx: int, fsm_def: FsmDefinition) -> None:
    guard = f"{project}_FSM_{fsm_def.name.upper()}_H"
    flat = fsm_def.all_states_flat()
    id_map = _state_id_map(fsm_def)

    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append(f'#include "anonys/impl/handlers{fsm_def.name}.h"')
    lines.append('#include "anonys/EventId.h"')
    lines.append('#include "anonys/FsmId.h"')
    lines.append("")
    lines.append("namespace anonys::fsm {")
    lines.append(f"\tstruct {fsm_def.name} {{")
    lines.append(f"\t\tstatic constexpr anonys::FsmId Id{{ anonys::FsmId::{fsm_def.name} }};")

    for state in flat:
        sid = id_map[state.name]
        ns = _ns(fsm_idx, sid)
        # Determine parent reference
        if state.parent is None:
            parent_ref = "nullptr"
        else:
            parent_ref = f"&{state.parent.name}"
        lines.append(
            f"\t\tstatic constexpr anonys::StateDef {state.name} = "
            f"{{ {sid}, anonys::FsmId::{fsm_def.name}, {parent_ref}, "
            f"{ns}::getMembersSize, {ns}::liveCycle, {ns}::handleEvent }};"
        )

    lines.append("\t};")
    lines.append("}")
    lines.append("")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


# ---------------------------------------------------------------------------
# FsmPool.h
# ---------------------------------------------------------------------------

def _write_fsm_pool_h(path: Path, project: str, fsm_defs: list[FsmDefinition]) -> None:
    guard = f"{project}_FSM_H"
    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append(f"#ifndef {guard}")
    lines.append(f"#define {guard}")
    lines.append("")
    lines.append("#include <type_traits>")
    lines.append("")
    lines.append('#include "anonys/FsmCore.h"')
    lines.append("")

    for i, fsm_def in enumerate(fsm_defs):
        lines.append(f'#include "impl/terminals{fsm_def.name}.h"')

    # Forward declarations for external terminal types used in initialize params
    ext_fwd_decls = _collect_external_forward_decls(fsm_defs)
    if ext_fwd_decls:
        lines.append("")
        for decl_line in ext_fwd_decls:
            lines.append(decl_line)

    lines.append("")
    lines.append("namespace anonys")
    lines.append("{")
    lines.append("\tclass FsmPool {")
    lines.append("\tpublic:")
    lines.append(f"\t\tstatic constexpr uint16_t Count{{ static_cast<uint16_t>(FsmId::Count_)}};")

    for i, fsm_def in enumerate(fsm_defs):
        lines.append(f"\t\tusing Terminals{fsm_def.name} = {_fsm_ns(i)}::Terminals;")

    lines.append("")
    lines.append("\t\tvoid handleEvent(FsmId fsmId, Event& event);")
    lines.append("")
    lines.append("\t\tvoid handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId);")
    lines.append("")
    lines.append("\t\tvoid setTracingService(TracingService* pTracingService = nullptr);")
    lines.append("")
    lines.append("\t\tvoid setTracingService(FsmId fsmId, TracingService* pTracingService = nullptr);")

    for i, fsm_def in enumerate(fsm_defs):
        params = _get_initialize_params(fsm_def)
        lines.append("")
        lines.append(f"\t\tvoid initialize{fsm_def.name}({params});")

    lines.append("")
    lines.append("\t\tvoid start();")
    lines.append("")
    lines.append("\tprivate:")
    lines.append("\t\tFsmCore m_fsm[Count]{};")
    lines.append("")

    for fsm_def in fsm_defs:
        lines.append(f"\t\tstd::aligned_storage_t<BufferSize::{fsm_def.name}, anonys::StdAlign> m_buffer{fsm_def.name}{{}};")

    lines.append("")
    for i, fsm_def in enumerate(fsm_defs):
        lines.append(f"\t\tTerminals{fsm_def.name} m_terminals{fsm_def.name}{{}};")

    lines.append("")
    lines.append("\t\tbool m_started{ false };")
    lines.append("\t};")
    lines.append("}")
    lines.append(f"#endif // {guard}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


def _collect_external_forward_decls(fsm_defs: list[FsmDefinition]) -> list[str]:
    """Collect forward declarations for types that appear as initialize parameters."""
    seen: set[str] = set()
    ns_groups: dict[str, list[Declaration]] = {}

    for fsm_def in fsm_defs:
        for ext in fsm_def.get_external_terminals():
            if ext.namespace_path not in seen:
                seen.add(ext.namespace_path)
                ns = ext.cpp_namespace
                ns_groups.setdefault(ns, []).append(ext)

    result: list[str] = []
    for ns, decls in ns_groups.items():
        if not ns:
            for d in decls:
                result.append(f"{d.kind} {d.cpp_type_name};")
        else:
            result.append(f"namespace {ns} {{ {'; '.join(f'{d.kind} {d.cpp_type_name}' for d in decls)}; }}")
    return result


def _get_initialize_params(fsm_def: FsmDefinition) -> str:
    """Build the parameter list for the initialize function."""
    params = ["TimerService& timerService"]
    for ext in fsm_def.get_external_terminals():
        params.append(f"{ext.cpp_qualified}& {ext.element_name}")
    return ", ".join(params)


# ---------------------------------------------------------------------------
# FsmPool.cpp
# ---------------------------------------------------------------------------

def _write_fsm_pool_cpp(path: Path, fsm_defs: list[FsmDefinition]) -> None:
    lines: list[str] = []
    lines.append("// Generated file, do not edit!")
    lines.append('#include "FsmPool.h"')
    lines.append('#include "anonys/Utils.h"')
    lines.append("")

    for fsm_def in fsm_defs:
        lines.append(f'#include "fsm/{fsm_def.name}.h"')

    lines.append("")
    lines.append("namespace anonys")
    lines.append("{")

    for fsm_def in fsm_defs:
        lines.append(f"\tstatic_assert(BufferSize::{fsm_def.name} % anonys::StdAlign == 0, \"Buffer size must be a multiple of alignment\");")

    lines.append("")

    # handleEvent
    lines.append("\tvoid FsmPool::handleEvent(FsmId fsmId, Event& event) {")
    lines.append("\t\tif (fsmId < FsmId::Count_) {")
    lines.append("\t\t\tm_fsm[static_cast<uint16_t>(fsmId)].handleEvent(event);")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")

    # handleTimeoutEvent
    lines.append("\tvoid FsmPool::handleTimeoutEvent(FsmId fsmId, int16_t depth, EventId eventId) {")
    lines.append("\t\tif (fsmId < FsmId::Count_) {")
    lines.append("\t\t\tm_fsm[static_cast<uint16_t>(fsmId)].handleTimeoutEvent(depth, eventId);")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")

    # setTracingService (all)
    lines.append("\tvoid FsmPool::setTracingService(TracingService* pTracingService) {")
    lines.append("\t\tfor (uint16_t fsmId{0}; fsmId < static_cast<uint16_t>(FsmId::Count_); ++fsmId) {")
    lines.append("\t\t\tm_fsm[fsmId].setTracingService(pTracingService);")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")

    # setTracingService (single)
    lines.append("\tvoid FsmPool::setTracingService(FsmId fsmId, TracingService* pTracingService) {")
    lines.append("\t\tif (fsmId < FsmId::Count_) {")
    lines.append("\t\t\tm_fsm[static_cast<uint16_t>(fsmId)].setTracingService(pTracingService);")
    lines.append("\t\t}")
    lines.append("\t}")

    # Per-FSM initialize functions
    for fsm_idx, fsm_def in enumerate(fsm_defs):
        lines.append("")
        params = _get_initialize_params(fsm_def)
        lines.append(f"\tvoid FsmPool::initialize{fsm_def.name}({params}) {{")
        lines.append(f"\t\tANONYS_ASSERT(m_terminals{fsm_def.name}.pTimer == nullptr);")
        lines.append(f"\t\tFsmCore& fsm{{ m_fsm[static_cast<uint16_t>(FsmId::{fsm_def.name})] }};")
        lines.append(f"\t\tm_terminals{fsm_def.name}.pTimer = &(fsm.getTimerCore());")

        for ext in fsm_def.get_external_terminals():
            lines.append(f"\t\tm_terminals{fsm_def.name}.{ext.ptr_name} = &{ext.element_name};")

        lines.append("")
        lines.append(f"\t\tuint8_t* const pBuffer{{ std::launder(reinterpret_cast<uint8_t*>(&m_buffer{fsm_def.name})) }};")
        lines.append(f"\t\tfsm.initialize(FsmId::{fsm_def.name}, &m_terminals{fsm_def.name}, pBuffer, sizeof(m_buffer{fsm_def.name}), &timerService);")
        lines.append("\t}")

    # start()
    lines.append("")
    lines.append("\tvoid FsmPool::start() {")
    lines.append("\t\tANONYS_ASSERT(!m_started);")
    lines.append("\t\tm_started = true;")
    for fsm_idx, fsm_def in enumerate(fsm_defs):
        # Find initial state (the one with !)
        initial = _find_initial_state(fsm_def)
        lines.append(
            f"\t\tm_fsm[static_cast<uint16_t>(FsmId::{fsm_def.name})].executeTransition(&fsm::{fsm_def.name}::{initial.name});"
        )
    lines.append("\t}")

    lines.append("}")
    lines.append("")

    path.write_text("\n".join(lines), encoding="utf-8")


def _find_initial_state(fsm_def: FsmDefinition) -> State:
    """Find the initial state (marked with !) in the FSM definition."""
    for s in fsm_def.all_states_flat():
        if s.is_initial:
            return s
    raise ValueError(f"No initial state found in FSM '{fsm_def.name}'")


# ---------------------------------------------------------------------------
# Per-state .cpp file generation
# ---------------------------------------------------------------------------

def _generate_state_cpps(fsm_cpp_dir: Path, fsm_idx: int, fsm_def: FsmDefinition) -> None:
    """Generate or update .cpp files for each state."""
    id_map = _state_id_map(fsm_def)

    for state in fsm_def.all_states_flat():
        state_id = id_map[state.name]
        cpp_path = _get_state_cpp_path(fsm_cpp_dir, fsm_def, state)
        cpp_path.parent.mkdir(parents=True, exist_ok=True)

        if cpp_path.exists():
            _update_state_cpp(cpp_path, fsm_idx, state_id, fsm_def, state)
        else:
            _create_state_cpp(cpp_path, fsm_idx, state_id, fsm_def, state)


def _get_state_cpp_path(fsm_cpp_dir: Path, fsm_def: FsmDefinition, state: State) -> Path:
    """Compute the file path for a state's .cpp file, reflecting the hierarchy."""
    # Build path segments from parent chain
    segments: list[str] = []
    current = state
    while current.parent is not None:
        segments.append(current.parent.name)
        current = current.parent

    segments.reverse()
    path = fsm_cpp_dir / fsm_def.name
    for seg in segments:
        path = path / seg
    path = path / f"{state.name}.cpp"
    return path


def _create_state_cpp(path: Path, fsm_idx: int, state_id: int, fsm_def: FsmDefinition, state: State) -> None:
    """Create a new state .cpp file with user-editable section and generated section."""
    lines: list[str] = []

    # Includes
    lines.append(f'#include "anonys/fsm/{fsm_def.name}.h"')
    lines.append("")

    # Anonymous namespace with user-editable code
    lines.append("namespace {")
    lines.append(f"\tusing Fsm = anonys::fsm::{fsm_def.name};")

    # Timeout aliases
    for i in range(1, state.num_timeouts + 1):
        letter = chr(ord("A") + i - 1)
        lines.append(f"\tusing Timeout{letter} = anonys::Timeout{i};")

    lines.append("")

    # Me struct
    lines.append("\tstruct Me {")
    me_members = _get_me_members(fsm_def, state)
    for member in me_members:
        lines.append(f"\t\t{member};")
    lines.append("\t};")

    # enter/exit stubs
    if state.has_enter:
        lines.append("")
        lines.append("\tvoid enter(Me& me) {")
        lines.append("\t}")

    if state.has_exit:
        lines.append("")
        lines.append("\tvoid exit(Me& me) {")
        lines.append("\t}")

    # Event handler stubs
    for ev_name in state.events:
        decl = fsm_def.get_declaration(ev_name)
        lines.append("")
        lines.append(f"\tanonys::State* handle(Me& me, {decl.cpp_qualified}& event) {{")
        lines.append("\t\treturn nullptr;")
        lines.append("\t}")

    # Timeout handler stubs
    for i in range(1, state.num_timeouts + 1):
        letter = chr(ord("A") + i - 1)
        lines.append("")
        lines.append(f"\tanonys::State* handle(Me& me, Timeout{letter}& event) {{")
        lines.append("\t\treturn nullptr;")
        lines.append("\t}")

    lines.append("}")
    lines.append("")

    # Generated section
    lines.append("// Generated code, do not edit:")
    lines.extend(_generate_state_section(fsm_idx, state_id, fsm_def, state))

    path.write_text("\n".join(lines), encoding="utf-8")


def _update_state_cpp(path: Path, fsm_idx: int, state_id: int, fsm_def: FsmDefinition, state: State) -> None:
    """Update only the generated section of an existing state .cpp file."""
    content = path.read_text(encoding="utf-8")
    marker = "// Generated code, do not edit:"
    idx = content.find(marker)
    if idx == -1:
        # No marker found — do not modify the file
        return

    # Keep everything up to and including the marker line
    user_section = content[:idx + len(marker)]

    # Generate new code section
    gen_lines = _generate_state_section(fsm_idx, state_id, fsm_def, state)
    new_content = user_section + "\n" + "\n".join(gen_lines)

    path.write_text(new_content, encoding="utf-8")


def _generate_state_section(fsm_idx: int, state_id: int, fsm_def: FsmDefinition, state: State) -> list[str]:
    """Generate the code section below '// Generated code, do not edit:'."""
    ns = _ns(fsm_idx, state_id)
    fsm_term_ns = _fsm_ns(fsm_idx)
    lines: list[str] = []

    # handleEvent
    lines.append(f"namespace {ns} {{")

    has_any_handler = bool(state.events) or state.num_timeouts > 0

    if not has_any_handler:
        # Halted-style: no handlers at all
        lines.append(f"\tanonys::State* handleEvent(void* pMembers, anonys::Event& event) {{")
        lines.append(f"\t\treturn &anonys::DummyStates::Unhandled;")
        lines.append("\t}")
    else:
        lines.append(f"\tanonys::State* handleEvent(void* pMembers, anonys::Event& event) {{")
        lines.append(f"\t\tMe& me{{ *static_cast<Me*>(pMembers) }};")
        lines.append(f"\t\tswitch (event.eventId.id) {{")

        for ev_name in state.events:
            decl = fsm_def.get_declaration(ev_name)
            lines.append(f"\t\tcase anonys::getEventId<{decl.cpp_qualified}>().id:")
            lines.append(f"\t\t\treturn handle(me, *static_cast<{decl.cpp_qualified}*>(event.pData));")

        for i in range(1, state.num_timeouts + 1):
            lines.append(f"\t\tcase anonys::getTimeoutEventId<anonys::Timeout{i}>().id:")
            letter = chr(ord("A") + i - 1)
            lines.append(f"\t\t\treturn handle(me, *static_cast<Timeout{letter}*>(event.pData));")

        lines.append("\t\tdefault:")
        lines.append("\t\t\treturn &anonys::DummyStates::Unhandled;")
        lines.append("\t\t}")
        lines.append("\t}")

    lines.append("")

    # liveCycle
    lines.append("\tvoid liveCycle(bool create, void* pTerminals, void* pMembers) {")

    has_published = bool(state.published)

    # Halted pattern: no handlers, no enter, no exit, no published — truly empty
    is_halted = (not has_any_handler and not state.has_enter and not state.has_exit
                 and not has_published)

    if is_halted:
        lines.append("\t\tif (create) {")
        lines.append(f"\t\t\t::new (pMembers) Me{{}};")
        lines.append("\t\t}")
        lines.append("\t\telse {")
        lines.append(f"\t\t\tMe& me{{ *static_cast<Me*>(pMembers) }};")
        lines.append("\t\t\tme.~Me();")
        lines.append("\t\t}")
    else:
        lines.append(f"\t\tauto& terminals{{ *static_cast<{fsm_term_ns}::Terminals*>(pTerminals) }};")
        ctor_args = _get_ctor_args(fsm_def, state)
        me_init = f"Me{{ {ctor_args} }}" if ctor_args else "Me{}"

        lines.append("\t\tif (create) {")

        # Determine new expression pattern based on enter/published presence
        if state.has_enter or has_published:
            lines.append(f"\t\t\tMe& me{{ *::new (pMembers) {me_init} }};")
        else:
            lines.append(f"\t\t\t::new (pMembers) {me_init};")

        # Set published terminal pointers
        for pub_name in state.published:
            decl = fsm_def.get_declaration(pub_name)
            lines.append(f"\t\t\tterminals.{decl.ptr_name} = &me.{pub_name};")

        if state.has_enter:
            lines.append("\t\t\tenter(me);")

        lines.append("\t\t}")
        lines.append("\t\telse {")

        lines.append(f"\t\t\tMe& me{{ *static_cast<Me*>(pMembers) }};")

        if state.has_exit:
            lines.append("\t\t\texit(me);")

        lines.append("\t\t\tme.~Me();")

        # Clear published terminal pointers
        for pub_name in state.published:
            decl = fsm_def.get_declaration(pub_name)
            lines.append(f"\t\t\tterminals.{decl.ptr_name} = nullptr;")

        lines.append("\t\t}")

    lines.append("\t}")
    lines.append("")

    # getMembersSize
    lines.append("\tuint16_t getMembersSize() {")
    lines.append("\t\treturn anonys::getAlignedSize<Me>();")
    lines.append("\t}")

    lines.append("}")
    lines.append("")

    return lines


def _get_me_members(fsm_def: FsmDefinition, state: State) -> list[str]:
    """Determine the Me struct members for a state.
    Order: timer (if any), then referenced terminals (type-1 refs), then published terminals (type-2 values)."""
    members: list[str] = []

    if _state_needs_timer(state):
        members.append("anonys::Timer timer")

    # Referenced terminals (type-1): pointers from parent states' published
    for ref_name in state.referenced:
        decl = fsm_def.get_declaration(ref_name)
        members.append(f"{decl.cpp_qualified}& {ref_name}")

    # Published terminals (type-2): value members created here
    for pub_name in state.published:
        decl = fsm_def.get_declaration(pub_name)
        members.append(f"{decl.cpp_qualified} {pub_name}{{}}")

    return members


def _state_needs_timer(state: State) -> bool:
    """Does this state need a timer member?"""
    return state.num_timeouts > 0


def _get_ctor_args(fsm_def: FsmDefinition, state: State) -> str:
    """Build the constructor arguments for placement new of Me struct."""
    args: list[str] = []

    if _state_needs_timer(state):
        args.append("*terminals.pTimer")

    for ref_name in state.referenced:
        decl = fsm_def.get_declaration(ref_name)
        args.append(f"*terminals.{decl.ptr_name}")

    # Published terminals are value-initialized (default ctor), no ctor arg needed

    return ", ".join(args)
