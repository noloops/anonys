"""Parser for FSM definition files (.txt)."""

from __future__ import annotations

import re
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class Declaration:
    """A declared type (event or terminal object)."""
    kind: str              # "struct" or "class"
    namespace_path: str    # e.g. "events.PowerOn" or "signals.alert.Emergency"
    element_name: str      # e.g. "powerOn" or "emergency"

    @property
    def cpp_qualified(self) -> str:
        """Full C++ qualified name, e.g. 'signals::alert::Emergency'."""
        return self.namespace_path.replace(".", "::")

    @property
    def cpp_namespace(self) -> str:
        """C++ namespace only (empty string if no namespace)."""
        parts = self.namespace_path.split(".")
        if len(parts) <= 1:
            return ""
        return "::".join(parts[:-1])

    @property
    def cpp_type_name(self) -> str:
        """Unqualified type name, e.g. 'Emergency'."""
        return self.namespace_path.split(".")[-1]

    @property
    def ptr_name(self) -> str:
        """Pointer member name in Terminals struct, e.g. 'pEmergency'."""
        return "p" + self.cpp_type_name


@dataclass
class State:
    """A parsed state definition."""
    name: str
    is_initial: bool = False
    has_enter: bool = False
    has_exit: bool = False
    num_timeouts: int = 0
    events: list[str] = field(default_factory=list)        # element names of handled events
    referenced: list[str] = field(default_factory=list)     # element names of referenced terminals (type-1)
    published: list[str] = field(default_factory=list)      # element names of published terminals (type-2)
    children: list[State] = field(default_factory=list)
    parent: State | None = field(default=None, repr=False)
    depth: int = 0  # nesting depth (0 = top-level)


@dataclass
class FsmDefinition:
    """Complete parsed FSM definition."""
    name: str                                    # FSM name from file name
    declarations: list[Declaration] = field(default_factory=list)
    states: list[State] = field(default_factory=list)  # top-level states only

    def all_states_flat(self) -> list[State]:
        """Return all states in definition order (depth-first)."""
        result: list[State] = []
        def _walk(states: list[State]) -> None:
            for s in states:
                result.append(s)
                _walk(s.children)
        _walk(self.states)
        return result

    def get_declaration(self, element_name: str) -> Declaration:
        """Look up a declaration by element name."""
        for d in self.declarations:
            if d.element_name == element_name:
                return d
        raise KeyError(f"No declaration found for element name '{element_name}'")

    def get_events(self) -> list[Declaration]:
        """Return declarations that are used as events (appear in any state's events list)."""
        event_names: set[str] = set()
        for s in self.all_states_flat():
            event_names.update(s.events)
        return [d for d in self.declarations if d.element_name in event_names]

    def get_terminals(self) -> list[Declaration]:
        """Return declarations that are used as terminals (appear in referenced or published)."""
        terminal_names: set[str] = set()
        for s in self.all_states_flat():
            terminal_names.update(s.referenced)
            terminal_names.update(s.published)
        return [d for d in self.declarations if d.element_name in terminal_names]

    def get_external_terminals(self) -> list[Declaration]:
        """Return terminal declarations that are only ever referenced, never published.
        These become parameters of the initialize function."""
        published_names: set[str] = set()
        referenced_names: set[str] = set()
        for s in self.all_states_flat():
            published_names.update(s.published)
            referenced_names.update(s.referenced)
        # External = referenced somewhere but never published anywhere
        external_names = referenced_names - published_names
        return [d for d in self.declarations if d.element_name in external_names]

    def get_published_terminals(self) -> list[Declaration]:
        """Return terminal declarations that are published by some state."""
        published_names: set[str] = set()
        for s in self.all_states_flat():
            published_names.update(s.published)
        return [d for d in self.declarations if d.element_name in published_names]


def _parse_state_line(line: str) -> State:
    """Parse a single state definition line (without leading tabs)."""
    rest = line.strip()

    # Initial state prefix
    is_initial = rest.startswith("!")
    if is_initial:
        rest = rest[1:]

    # State name
    parts = rest.split()
    name = parts[0]
    rest_parts = parts[1:]

    # Rejoin for parenthesis parsing
    rest_str = " ".join(rest_parts)

    # Split on parentheses to get three sections
    # Before '(' : flags + events
    # Between '(' and ')' : referenced terminals
    # After ')' : published terminals
    before_paren = ""
    in_paren = ""
    after_paren = ""

    if "(" in rest_str:
        idx_open = rest_str.index("(")
        idx_close = rest_str.index(")")
        before_paren = rest_str[:idx_open].strip()
        in_paren = rest_str[idx_open + 1:idx_close].strip()
        after_paren = rest_str[idx_close + 1:].strip()
    else:
        before_paren = rest_str

    # Parse flags and events from before_paren
    has_enter = False
    has_exit = False
    num_timeouts = 0
    events: list[str] = []

    tokens = before_paren.split() if before_paren else []
    flag_idx = 0
    if tokens:
        # First token might be flags like "+-1" or "+1" or "-" or "+-" etc.
        first = tokens[0]
        # Check if first token starts with + or - (flag token)
        if first and first[0] in "+-":
            flag_token = first
            flag_idx = 1
            i = 0
            while i < len(flag_token):
                ch = flag_token[i]
                if ch == "+":
                    has_enter = True
                    i += 1
                elif ch == "-":
                    # Check if next char is a digit — if so, it's a negative... no, actually
                    # the '-' always means exit. Digits after +/- are timeout count.
                    has_exit = True
                    i += 1
                elif ch.isdigit():
                    num_timeouts = int(ch)
                    i += 1
                else:
                    break
        events = tokens[flag_idx:]

    # Parse referenced terminals from in_paren
    referenced = in_paren.split() if in_paren else []

    # Parse published terminals from after_paren
    published = after_paren.split() if after_paren else []

    return State(
        name=name,
        is_initial=is_initial,
        has_enter=has_enter,
        has_exit=has_exit,
        num_timeouts=num_timeouts,
        events=events,
        referenced=referenced,
        published=published,
    )


def parse_definition(filepath: Path) -> FsmDefinition:
    """Parse an FSM definition file and return the structured definition."""
    fsm_name = filepath.stem
    lines = filepath.read_text(encoding="utf-8").splitlines()

    declarations: list[Declaration] = []
    state_lines: list[tuple[int, str]] = []  # (indent_level, line)
    in_states = False

    for raw_line in lines:
        stripped = raw_line.strip()
        if not stripped:
            continue

        if stripped.startswith("struct ") or stripped.startswith("class "):
            # Declaration line
            parts = stripped.split()
            kind = parts[0]
            namespace_path = parts[1]
            element_name = parts[2]
            declarations.append(Declaration(kind, namespace_path, element_name))
        else:
            # State line — count leading tabs for indent
            indent = 0
            for ch in raw_line:
                if ch == "\t":
                    indent += 1
                else:
                    break
            state_lines.append((indent, stripped))
            in_states = True

    # Build state tree
    top_level_states: list[State] = []
    # Stack of (indent_level, state)
    stack: list[tuple[int, State]] = []

    for indent, line in state_lines:
        state = _parse_state_line(line)
        state.depth = indent

        # Find parent: pop stack until we find a state at indent - 1
        while stack and stack[-1][0] >= indent:
            stack.pop()

        if stack:
            parent = stack[-1][1]
            state.parent = parent
            parent.children.append(state)
        else:
            top_level_states.append(state)

        stack.append((indent, state))

    return FsmDefinition(
        name=fsm_name,
        declarations=declarations,
        states=top_level_states,
    )
