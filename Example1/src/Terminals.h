#pragma once
namespace term::io {
struct Std {};
}
namespace term::ctrl {
class Panel {};
}
namespace term::hw {
class Robot {};
class Conveyor {};
class LoadLock {};
class VacuumGauge {};
}
namespace term::litho {
class Scanner {};
class MaskStage {};
class LaserSource { public: LaserSource() = default; LaserSource(Scanner& s) : m_pScanner{&s} {} Scanner* m_pScanner{}; };
class FocusUnit {};
class ReticleHandler { public: ReticleHandler() = default; ReticleHandler(MaskStage& m) : m_pMaskStage{&m} {} MaskStage* m_pMaskStage{}; };
}
namespace term::etch {
class PlasmaGen {};
class GasCtrl {};
class PressureCtrl { public: PressureCtrl() = default; PressureCtrl(GasCtrl& g) : m_pGasCtrl{&g} {} GasCtrl* m_pGasCtrl{}; };
class Endpoint { public: Endpoint() = default; Endpoint(PlasmaGen& p) : m_pPlasmaGen{&p} {} PlasmaGen* m_pPlasmaGen{}; };
}
namespace term::dep {
class Heater {};
class GasMixer {};
class ThicknessMon { public: ThicknessMon() = default; ThicknessMon(Heater& h) : m_pHeater{&h} {} Heater* m_pHeater{}; };
class Showerhead {};
class VacuumPump {};
}
namespace term::cmp {
class PolishHead {};
class SlurryPump {};
class PadCond { public: PadCond() = default; PadCond(PolishHead& p) : m_pPolishHead{&p} {} PolishHead* m_pPolishHead{}; };
class CmpEndpoint {};
}
namespace term::inspect {
class Camera {};
class Classifier { public: Classifier() = default; Classifier(Camera& c) : m_pCamera{&c} {} Camera* m_pCamera{}; };
class Stage {};
class ReviewStation {};
}
namespace term::thermal {
class Furnace {};
class CoolingSys {};
class TempCtrl { public: TempCtrl() = default; TempCtrl(Furnace& f) : m_pFurnace{&f} {} Furnace* m_pFurnace{}; };
class GasSupply {};
}
namespace term::implant {
class BeamLine {};
class DoseCtrl { public: DoseCtrl() = default; DoseCtrl(BeamLine& b) : m_pBeamLine{&b} {} BeamLine* m_pBeamLine{}; };
class Faraday {};
}
namespace term::clean {
class SpinChuck {};
class ChemDispenser {};
class Dryer { public: Dryer() = default; Dryer(SpinChuck& s) : m_pSpinChuck{&s} {} SpinChuck* m_pSpinChuck{}; };
}
namespace term::pkg {
class Bonder {};
class Dicer {};
class Encapsulator {};
class Marker {};
class Sorter { public: Sorter() = default; Sorter(Bonder& b) : m_pBonder{&b} {} Bonder* m_pBonder{}; };
}
namespace term::sensor {
class WaferSensor {};
class TempSensor {};
class PressureSensor {};
class FlowSensor {};
class ParticleSensor {};
}
