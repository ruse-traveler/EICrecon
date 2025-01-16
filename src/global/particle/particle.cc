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

        using namespace eicrecon;

        InitJANAPlugin(app);

        // ====================================================================
        // PFAlpha: our baseline PF implementation
        // ====================================================================

        // --------------------------------------------------------------------
        // PFA (0a) connection: match tracks-to-clusters
        // --------------------------------------------------------------------

        /* TODO add here */

        // --------------------------------------------------------------------
        // PFA (0b) connection: split/merge clusters accordingly
        // --------------------------------------------------------------------

        // backward -----------------------------------------------------------

        app->Add(
          new JOmniFactoryGeneratorT<TrackClusterMergeSplitter_factory>(
            "EcalEndcapNSplitMergeClusters",
            {"EcalEndcapNClustersWithoutPID",
             "CalorimeterTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
            {"EcalEndcapNSplitMergeClusters",
             "EcalEndcapNTrackSplitMergeClusterMatches"},
#else
            {"EcalEndcapNSplitMergeClusters"},
#endif
            {
              .idCalo = "EcalEndcapN_ID",
              .minSigCut = -1.0,
              .avgEP = 1.0,
              .sigEP = 0.10,
              .drAdd = 0.08,
              .sampFrac = 1.0,
              .transverseEnergyProfileScale = 1.0
            },
            app   // TODO: remove me once fixed
          )
        );

        app->Add(
          new JOmniFactoryGeneratorT<TrackClusterMergeSplitter_factory>(
            "HcalEndcapNSplitMergeClusters",
            {"HcalEndcapNClusters",
             "CalorimeterTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
            {"HcalEndcapNSplitMergeClusters",
             "HcalEndcapNTrackSplitMergeClusterMatches"},
#else
            {"HcalEndcapNSplitMergeClusters"},
#endif
            {
              .idCalo = "HcalEndcapN_ID",
              .minSigCut = -2.0,
              .avgEP = 0.60,
              .sigEP = 0.40,
              .drAdd = 0.40,
              .sampFrac = 1.0,
              .transverseEnergyProfileScale = 1.0
            },
            app   // TODO: remove me once fixed
          )
        );

        // central ------------------------------------------------------------

        app->Add(
          new JOmniFactoryGeneratorT<TrackClusterMergeSplitter_factory>(
            "HcalBarrelSplitMergeClusters",
            {"HcalBarrelClusters",
             "CalorimeterTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
            {"HcalBarrelSplitMergeClusters",
             "HcalBarrelTrackSplitMergeClusterMatches"},
#else
            {"HcalBarrelSplitMergeClusters"},
#endif
            {
              .idCalo = "HcalBarrel_ID",
              .minSigCut = -2.0,
              .avgEP = 0.50,
              .sigEP = 0.25,
              .drAdd = 0.40,
              .sampFrac = 1.0,
              .transverseEnergyProfileScale = 1.0
            },
            app   // TODO: remove me once fixed
          )
        );

        // forward ------------------------------------------------------------

        app->Add(
          new JOmniFactoryGeneratorT<TrackClusterMergeSplitter_factory>(
            "EcalEndcapPSplitMergeClusters",
            {"EcalEndcapPClusters",
             "CalorimeterTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
            {"EcalEndcapPSplitMergeClusters",
             "EcalEndcapPTrackSplitMergeClusterMatches"},
#else
            {"EcalEndcapPSplitMergeClusters"},
#endif
            {
              .idCalo = "EcalEndcapP_ID",
              .minSigCut = -2.0,
              .avgEP = 1.0,
              .sigEP = 0.10,
              .drAdd = 0.30,
              .sampFrac = 1.0,
              .transverseEnergyProfileScale = 1.0
            },
            app   // TODO: remove me once fixed
          )
        );

        app->Add(
          new JOmniFactoryGeneratorT<TrackClusterMergeSplitter_factory>(
            "LFHCALSplitMergeClusters",
            {"LFHCALClusters",
             "CalorimeterTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
            {"LFHCALSplitMergeClusters",
             "LFHCALTrackSplitMergeClusterMatches"},
#else
            {"LFHCALSplitMergeClusters"},
#endif
            {
              .idCalo = "LFHCAL_ID",
              .minSigCut = -2.0,
              .avgEP = 0.50,
              .sigEP = 0.25,
              .drAdd = 0.30,
              .sampFrac = 1.0,
              .transverseEnergyProfileScale = 1.0
            },
            app   // TODO: remove me once fixed
          )
        );

        // --------------------------------------------------------------------
        // PFA (1a) arbitration: apply track correction to clusters
        // --------------------------------------------------------------------

        /* TODO add here */

        // --------------------------------------------------------------------
        // PFA (1b) arbitration: form charged candidates
        // --------------------------------------------------------------------

        /* TODO add here */

        // --------------------------------------------------------------------
        // PFA (2) arbitration: combine remnants, form neutral candidates
        // --------------------------------------------------------------------

        /* TODO add here */

        // --------------------------------------------------------------------
        // PFA (3) regression: convert candidates to reco particles
        // --------------------------------------------------------------------

        /* TODO add here */

    }
}
