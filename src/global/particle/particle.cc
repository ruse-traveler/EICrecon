// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

#include <edm4eic/EDM4eicVersion.h>
#include <Evaluator/DD4hepUnits.h>
#include <JANA/JApplication.h>
#include <memory>

#include "extensions/jana/JOmniFactoryGeneratorT.h"
#include "factories/particle/TrackClusterMergeSplitter_factory.h"
#include "factories/particle/TrackClusterSubtraction_factory.h"

extern "C" {

    void InitPlugin(JApplication *app) {

    }
}

