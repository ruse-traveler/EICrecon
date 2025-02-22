// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Derek Anderson

#pragma once

#include <string>

namespace eicrecon {

  struct TrackClusterSubtractorConfig {

    // FIXME might not be needed
    std::string idCalo = "HcalBarrel_ID";  // id of calorimeter to match to

    double fracEnergyToSub = 1.0;  // fraction of energy to subtract

  };  // end TrackClusterSubtractorConfig

}  // end eicrecon namespace
