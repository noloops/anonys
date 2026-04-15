#pragma once
namespace evt::sys {
struct PowerOn {};
struct PowerOff {};
struct EmergencyStop {};
struct Reset {};
struct Heartbeat {};
class Configure {};
class Calibrate {};
struct Acknowledge {};
struct DiagRequest {};
struct SelfTest {};
struct Shutdown {};
struct WarmRestart {};
}
namespace evt::wafer {
struct WaferArrived {};
struct WaferUnloaded {};
struct WaferAligned {};
struct WaferFlipped {};
struct WaferTransfer {};
struct WaferReject {};
class WaferIdScanned {};
struct CassetteInserted {};
struct CassetteRemoved {};
struct BatchComplete {};
struct LotStart {};
struct LotEnd {};
}
namespace evt::litho {
struct ExposureStart {};
struct ExposureDone {};
struct MaskLoaded {};
struct MaskAligned {};
struct FocusLocked {};
class DoseAdjust {};
struct ReticleSwap {};
struct ScanComplete {};
struct StepComplete {};
}
namespace evt::etch {
struct EtchStart {};
struct EtchDone {};
struct PlasmaIgnited {};
struct PlasmaOff {};
class GasFlowSet {};
class PressureSet {};
struct EndpointDetected {};
struct OverEtchDone {};
}
namespace evt::dep {
struct DepositStart {};
struct DepositDone {};
class TemperatureReached {};
class GasMixSet {};
struct PurgeComplete {};
struct FilmThicknessOk {};
struct ChamberSealed {};
struct ChamberVented {};
}
namespace evt::cmp {
struct PolishStart {};
struct PolishDone {};
struct PadConditioned {};
class SlurryFlowSet {};
class DownForceSet {};
struct EndpointHit {};
struct RinseComplete {};
}
namespace evt::inspect {
struct InspectStart {};
struct InspectDone {};
struct DefectFound {};
struct DefectClear {};
class ThresholdSet {};
struct ImageCaptured {};
struct MeasureDone {};
struct ReviewComplete {};
}
namespace evt::thermal {
struct AnnealStart {};
struct AnnealDone {};
class RampRate {};
struct SoakReached {};
struct CooldownDone {};
struct OxidationStart {};
struct OxidationDone {};
struct DiffusionStart {};
struct DiffusionDone {};
}
namespace evt::implant {
struct ImplantStart {};
struct ImplantDone {};
class EnergySet {};
class DoseSet {};
struct BeamReady {};
struct BeamOff {};
}
namespace evt::clean {
struct CleanStart {};
struct CleanDone {};
struct RinseDone {};
struct DryDone {};
struct ChemicalReady {};
}
namespace evt::pkg {
struct BondStart {};
struct BondDone {};
struct DiceStart {};
struct DiceDone {};
struct EncapDone {};
struct MarkDone {};
struct PackDone {};
}
namespace evt::xfer {
struct RobotReady {};
struct RobotBusy {};
struct RobotFault {};
struct ConveyorTick {};
struct LoadLockPumped {};
struct LoadLockVented {};
}
namespace evt::alarm {
struct OverTemp {};
struct UnderPressure {};
struct GasLeak {};
struct ParticleAlert {};
struct AlarmClear {};
}
