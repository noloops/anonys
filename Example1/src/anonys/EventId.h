// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

// ANONYS - Generated file, do not edit!
#ifndef EXAMPLE1_ANONYS_EVENTID_H
#define EXAMPLE1_ANONYS_EVENTID_H

#include "anonys/Types.h"

namespace evt::sys {
    struct PowerOn;
    struct PowerOff;
    struct EmergencyStop;
    struct Reset;
    struct Heartbeat;
    class Configure;
    class Calibrate;
    struct Acknowledge;
    struct DiagRequest;
    struct SelfTest;
    struct Shutdown;
    struct WarmRestart;
}
namespace evt::wafer {
    struct WaferArrived;
    struct WaferUnloaded;
    struct WaferAligned;
    struct WaferFlipped;
    struct WaferTransfer;
    struct WaferReject;
    class WaferIdScanned;
    struct CassetteInserted;
    struct CassetteRemoved;
    struct BatchComplete;
    struct LotStart;
    struct LotEnd;
}
namespace evt::litho {
    struct ExposureStart;
    struct ExposureDone;
    struct MaskLoaded;
    struct MaskAligned;
    struct FocusLocked;
    class DoseAdjust;
    struct ReticleSwap;
    struct ScanComplete;
    struct StepComplete;
}
namespace evt::etch {
    struct EtchStart;
    struct EtchDone;
    struct PlasmaIgnited;
    struct PlasmaOff;
    class GasFlowSet;
    class PressureSet;
    struct EndpointDetected;
    struct OverEtchDone;
}
namespace evt::dep {
    struct DepositStart;
    struct DepositDone;
    class TemperatureReached;
    class GasMixSet;
    struct PurgeComplete;
    struct FilmThicknessOk;
    struct ChamberSealed;
    struct ChamberVented;
}
namespace evt::cmp {
    struct PolishStart;
    struct PolishDone;
    struct PadConditioned;
    class SlurryFlowSet;
    class DownForceSet;
    struct EndpointHit;
    struct RinseComplete;
}
namespace evt::inspect {
    struct InspectStart;
    struct InspectDone;
    struct DefectFound;
    struct DefectClear;
    class ThresholdSet;
    struct ImageCaptured;
    struct MeasureDone;
    struct ReviewComplete;
}
namespace evt::thermal {
    struct AnnealStart;
    struct AnnealDone;
    class RampRate;
    struct SoakReached;
    struct CooldownDone;
    struct OxidationStart;
    struct OxidationDone;
    struct DiffusionStart;
    struct DiffusionDone;
}
namespace evt::implant {
    struct ImplantStart;
    struct ImplantDone;
    class EnergySet;
    class DoseSet;
    struct BeamReady;
    struct BeamOff;
}
namespace evt::clean {
    struct CleanStart;
    struct CleanDone;
    struct RinseDone;
    struct DryDone;
    struct ChemicalReady;
}
namespace evt::pkg {
    struct BondStart;
    struct BondDone;
    struct DiceStart;
    struct DiceDone;
    struct EncapDone;
    struct MarkDone;
    struct PackDone;
}
namespace evt::xfer {
    struct RobotReady;
    struct RobotBusy;
    struct RobotFault;
    struct ConveyorTick;
    struct LoadLockPumped;
    struct LoadLockVented;
}
namespace evt::alarm {
    struct OverTemp;
    struct UnderPressure;
    struct GasLeak;
    struct ParticleAlert;
    struct AlarmClear;
}

namespace anonys
{
    class Timeout1 {};
    class Timeout2 {};

    template <typename T> constexpr EventId getEventId() = delete;
    template<> constexpr EventId getEventId<evt::sys::PowerOn>() { return 0; }
    template<> constexpr EventId getEventId<evt::sys::PowerOff>() { return 1; }
    template<> constexpr EventId getEventId<evt::sys::EmergencyStop>() { return 2; }
    template<> constexpr EventId getEventId<evt::sys::Reset>() { return 3; }
    template<> constexpr EventId getEventId<evt::sys::Heartbeat>() { return 4; }
    template<> constexpr EventId getEventId<evt::sys::Configure>() { return 5; }
    template<> constexpr EventId getEventId<evt::sys::Calibrate>() { return 6; }
    template<> constexpr EventId getEventId<evt::sys::Acknowledge>() { return 7; }
    template<> constexpr EventId getEventId<evt::sys::DiagRequest>() { return 8; }
    template<> constexpr EventId getEventId<evt::sys::SelfTest>() { return 9; }
    template<> constexpr EventId getEventId<evt::sys::Shutdown>() { return 10; }
    template<> constexpr EventId getEventId<evt::sys::WarmRestart>() { return 11; }
    template<> constexpr EventId getEventId<evt::wafer::WaferArrived>() { return 12; }
    template<> constexpr EventId getEventId<evt::wafer::WaferUnloaded>() { return 13; }
    template<> constexpr EventId getEventId<evt::wafer::WaferAligned>() { return 14; }
    template<> constexpr EventId getEventId<evt::wafer::WaferFlipped>() { return 15; }
    template<> constexpr EventId getEventId<evt::wafer::WaferTransfer>() { return 16; }
    template<> constexpr EventId getEventId<evt::wafer::WaferReject>() { return 17; }
    template<> constexpr EventId getEventId<evt::wafer::WaferIdScanned>() { return 18; }
    template<> constexpr EventId getEventId<evt::wafer::CassetteInserted>() { return 19; }
    template<> constexpr EventId getEventId<evt::wafer::CassetteRemoved>() { return 20; }
    template<> constexpr EventId getEventId<evt::wafer::BatchComplete>() { return 21; }
    template<> constexpr EventId getEventId<evt::wafer::LotStart>() { return 22; }
    template<> constexpr EventId getEventId<evt::wafer::LotEnd>() { return 23; }
    template<> constexpr EventId getEventId<evt::litho::ExposureStart>() { return 24; }
    template<> constexpr EventId getEventId<evt::litho::ExposureDone>() { return 25; }
    template<> constexpr EventId getEventId<evt::litho::MaskLoaded>() { return 26; }
    template<> constexpr EventId getEventId<evt::litho::MaskAligned>() { return 27; }
    template<> constexpr EventId getEventId<evt::litho::FocusLocked>() { return 28; }
    template<> constexpr EventId getEventId<evt::litho::DoseAdjust>() { return 29; }
    template<> constexpr EventId getEventId<evt::litho::ReticleSwap>() { return 30; }
    template<> constexpr EventId getEventId<evt::litho::ScanComplete>() { return 31; }
    template<> constexpr EventId getEventId<evt::litho::StepComplete>() { return 32; }
    template<> constexpr EventId getEventId<evt::etch::EtchStart>() { return 33; }
    template<> constexpr EventId getEventId<evt::etch::EtchDone>() { return 34; }
    template<> constexpr EventId getEventId<evt::etch::PlasmaIgnited>() { return 35; }
    template<> constexpr EventId getEventId<evt::etch::PlasmaOff>() { return 36; }
    template<> constexpr EventId getEventId<evt::etch::GasFlowSet>() { return 37; }
    template<> constexpr EventId getEventId<evt::etch::PressureSet>() { return 38; }
    template<> constexpr EventId getEventId<evt::etch::EndpointDetected>() { return 39; }
    template<> constexpr EventId getEventId<evt::etch::OverEtchDone>() { return 40; }
    template<> constexpr EventId getEventId<evt::dep::DepositStart>() { return 41; }
    template<> constexpr EventId getEventId<evt::dep::DepositDone>() { return 42; }
    template<> constexpr EventId getEventId<evt::dep::TemperatureReached>() { return 43; }
    template<> constexpr EventId getEventId<evt::dep::GasMixSet>() { return 44; }
    template<> constexpr EventId getEventId<evt::dep::PurgeComplete>() { return 45; }
    template<> constexpr EventId getEventId<evt::dep::FilmThicknessOk>() { return 46; }
    template<> constexpr EventId getEventId<evt::dep::ChamberSealed>() { return 47; }
    template<> constexpr EventId getEventId<evt::dep::ChamberVented>() { return 48; }
    template<> constexpr EventId getEventId<evt::cmp::PolishStart>() { return 49; }
    template<> constexpr EventId getEventId<evt::cmp::PolishDone>() { return 50; }
    template<> constexpr EventId getEventId<evt::cmp::PadConditioned>() { return 51; }
    template<> constexpr EventId getEventId<evt::cmp::SlurryFlowSet>() { return 52; }
    template<> constexpr EventId getEventId<evt::cmp::DownForceSet>() { return 53; }
    template<> constexpr EventId getEventId<evt::cmp::EndpointHit>() { return 54; }
    template<> constexpr EventId getEventId<evt::cmp::RinseComplete>() { return 55; }
    template<> constexpr EventId getEventId<evt::inspect::InspectStart>() { return 56; }
    template<> constexpr EventId getEventId<evt::inspect::InspectDone>() { return 57; }
    template<> constexpr EventId getEventId<evt::inspect::DefectFound>() { return 58; }
    template<> constexpr EventId getEventId<evt::inspect::DefectClear>() { return 59; }
    template<> constexpr EventId getEventId<evt::inspect::ThresholdSet>() { return 60; }
    template<> constexpr EventId getEventId<evt::inspect::ImageCaptured>() { return 61; }
    template<> constexpr EventId getEventId<evt::inspect::MeasureDone>() { return 62; }
    template<> constexpr EventId getEventId<evt::inspect::ReviewComplete>() { return 63; }
    template<> constexpr EventId getEventId<evt::thermal::AnnealStart>() { return 64; }
    template<> constexpr EventId getEventId<evt::thermal::AnnealDone>() { return 65; }
    template<> constexpr EventId getEventId<evt::thermal::RampRate>() { return 66; }
    template<> constexpr EventId getEventId<evt::thermal::SoakReached>() { return 67; }
    template<> constexpr EventId getEventId<evt::thermal::CooldownDone>() { return 68; }
    template<> constexpr EventId getEventId<evt::thermal::OxidationStart>() { return 69; }
    template<> constexpr EventId getEventId<evt::thermal::OxidationDone>() { return 70; }
    template<> constexpr EventId getEventId<evt::thermal::DiffusionStart>() { return 71; }
    template<> constexpr EventId getEventId<evt::thermal::DiffusionDone>() { return 72; }
    template<> constexpr EventId getEventId<evt::implant::ImplantStart>() { return 73; }
    template<> constexpr EventId getEventId<evt::implant::ImplantDone>() { return 74; }
    template<> constexpr EventId getEventId<evt::implant::EnergySet>() { return 75; }
    template<> constexpr EventId getEventId<evt::implant::DoseSet>() { return 76; }
    template<> constexpr EventId getEventId<evt::implant::BeamReady>() { return 77; }
    template<> constexpr EventId getEventId<evt::implant::BeamOff>() { return 78; }
    template<> constexpr EventId getEventId<evt::clean::CleanStart>() { return 79; }
    template<> constexpr EventId getEventId<evt::clean::CleanDone>() { return 80; }
    template<> constexpr EventId getEventId<evt::clean::RinseDone>() { return 81; }
    template<> constexpr EventId getEventId<evt::clean::DryDone>() { return 82; }
    template<> constexpr EventId getEventId<evt::clean::ChemicalReady>() { return 83; }
    template<> constexpr EventId getEventId<evt::pkg::BondStart>() { return 84; }
    template<> constexpr EventId getEventId<evt::pkg::BondDone>() { return 85; }
    template<> constexpr EventId getEventId<evt::pkg::DiceStart>() { return 86; }
    template<> constexpr EventId getEventId<evt::pkg::DiceDone>() { return 87; }
    template<> constexpr EventId getEventId<evt::pkg::EncapDone>() { return 88; }
    template<> constexpr EventId getEventId<evt::pkg::MarkDone>() { return 89; }
    template<> constexpr EventId getEventId<evt::pkg::PackDone>() { return 90; }
    template<> constexpr EventId getEventId<evt::xfer::RobotReady>() { return 91; }
    template<> constexpr EventId getEventId<evt::xfer::RobotBusy>() { return 92; }
    template<> constexpr EventId getEventId<evt::xfer::RobotFault>() { return 93; }
    template<> constexpr EventId getEventId<evt::xfer::ConveyorTick>() { return 94; }
    template<> constexpr EventId getEventId<evt::xfer::LoadLockPumped>() { return 95; }
    template<> constexpr EventId getEventId<evt::xfer::LoadLockVented>() { return 96; }
    template<> constexpr EventId getEventId<evt::alarm::OverTemp>() { return 97; }
    template<> constexpr EventId getEventId<evt::alarm::UnderPressure>() { return 98; }
    template<> constexpr EventId getEventId<evt::alarm::GasLeak>() { return 99; }
    template<> constexpr EventId getEventId<evt::alarm::ParticleAlert>() { return 100; }
    template<> constexpr EventId getEventId<evt::alarm::AlarmClear>() { return 101; }

    template <typename T> constexpr EventId getTimeoutEventId() = delete;
    template<> constexpr EventId getTimeoutEventId<Timeout1>() { return 60001; }
    template<> constexpr EventId getTimeoutEventId<Timeout2>() { return 60002; }
    static_assert(getTimeoutEventId<Timeout1>().id == MinTimoutEventId.id);
}

#endif // EXAMPLE1_ANONYS_EVENTID_H
