// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_TERMINALS_SEMIFAB_H
#define EXAMPLE1_ANONYS_TERMINALS_SEMIFAB_H

#include "anonys/Timer.h"

namespace term::io {
    struct Std;
}
namespace term::ctrl {
    class Panel;
}
namespace term::hw {
    class Robot;
    class Conveyor;
    class LoadLock;
    class VacuumGauge;
}
namespace term::litho {
    class Scanner;
    class MaskStage;
    class LaserSource;
    class FocusUnit;
    class ReticleHandler;
}
namespace term::etch {
    class PlasmaGen;
    class GasCtrl;
    class PressureCtrl;
    class Endpoint;
}
namespace term::dep {
    class Heater;
    class GasMixer;
    class ThicknessMon;
    class Showerhead;
    class VacuumPump;
}
namespace term::cmp {
    class PolishHead;
    class SlurryPump;
    class PadCond;
    class CmpEndpoint;
}
namespace term::inspect {
    class Camera;
    class Classifier;
    class Stage;
    class ReviewStation;
}
namespace term::thermal {
    class Furnace;
    class CoolingSys;
    class TempCtrl;
    class GasSupply;
}
namespace term::implant {
    class BeamLine;
    class DoseCtrl;
    class Faraday;
}
namespace term::clean {
    class SpinChuck;
    class ChemDispenser;
    class Dryer;
}
namespace term::pkg {
    class Bonder;
    class Dicer;
    class Encapsulator;
    class Marker;
    class Sorter;
}
namespace term::sensor {
    class WaferSensor;
    class TempSensor;
    class PressureSensor;
    class FlowSensor;
    class ParticleSensor;
}

namespace anonys_0 {
    struct Terminals {
        anonys::TimerCore* pTimer;
        term::io::Std* pStd;
        term::ctrl::Panel* pPanel;
        term::hw::Robot* pRobot;
        term::hw::Conveyor* pConveyor;
        term::hw::LoadLock* pLoadLock;
        term::litho::Scanner* pScanner;
        term::litho::MaskStage* pMaskStage;
        term::litho::LaserSource* pLaserSource;
        term::litho::FocusUnit* pFocusUnit;
        term::litho::ReticleHandler* pReticleHandler;
        term::etch::PlasmaGen* pPlasmaGen;
        term::etch::GasCtrl* pGasCtrl;
        term::etch::PressureCtrl* pPressureCtrl;
        term::etch::Endpoint* pEndpoint;
        term::dep::Heater* pHeater;
        term::dep::GasMixer* pGasMixer;
        term::dep::ThicknessMon* pThicknessMon;
        term::dep::Showerhead* pShowerhead;
        term::dep::VacuumPump* pVacuumPump;
        term::cmp::PolishHead* pPolishHead;
        term::cmp::SlurryPump* pSlurryPump;
        term::cmp::PadCond* pPadCond;
        term::cmp::CmpEndpoint* pCmpEndpoint;
        term::inspect::Camera* pCamera;
        term::inspect::Classifier* pClassifier;
        term::inspect::Stage* pInspectStage;
        term::inspect::ReviewStation* pReviewStation;
        term::thermal::Furnace* pFurnace;
        term::thermal::CoolingSys* pCoolingSys;
        term::thermal::TempCtrl* pTempCtrl;
        term::thermal::GasSupply* pGasSupply;
        term::implant::BeamLine* pBeamLine;
        term::implant::DoseCtrl* pDoseCtrl;
        term::implant::Faraday* pFaraday;
        term::clean::SpinChuck* pSpinChuck;
        term::clean::ChemDispenser* pChemDispenser;
        term::clean::Dryer* pDryer;
        term::pkg::Bonder* pBonder;
        term::pkg::Dicer* pDicer;
        term::pkg::Encapsulator* pEncapsulator;
        term::pkg::Marker* pMarker;
        term::pkg::Sorter* pSorter;
        term::sensor::WaferSensor* pWaferSensor;
        term::sensor::TempSensor* pTempSensor;
        term::sensor::PressureSensor* pPressureSensor;
        term::sensor::FlowSensor* pFlowSensor;
        term::sensor::ParticleSensor* pParticleSensor;
        term::hw::VacuumGauge* pVacuumGauge;
    };
}

#endif // EXAMPLE1_ANONYS_TERMINALS_SEMIFAB_H
