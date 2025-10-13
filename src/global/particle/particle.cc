// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Derek Anderson

#include <JANA/JApplicationFwd.h>
#include <JANA/Utils/JTypeInfo.h>
#include <edm4eic/EDM4eicVersion.h>
#include <string>
#include <vector>

#include "extensions/jana/JOmniFactoryGeneratorT.h"
#include "factories/meta/CollectionCollector_factory.h"
#include "factories/particle/ChargedCandidateMaker_factory.h"
#include "factories/particle/TrackClusterSubtractor_factory.h"

extern "C" {

void InitPlugin(JApplication* app) {

  using namespace eicrecon;

  InitJANAPlugin(app);

  /* TODO move track-cluster matching here when ready */

  // ====================================================================
  // PFAlpha: baseline PF implementation
  // ====================================================================

  // --------------------------------------------------------------------
  // PFA (0) connection: split/merge clusters accordingly
  // --------------------------------------------------------------------

  /* TODO move here when ready */

  // --------------------------------------------------------------------
  // PFA (1a) arbitration: apply track correction to clusters
  // --------------------------------------------------------------------

  // backward -----------------------------------------------------------

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "EcalEndcapNRemnantClusters",
      {"EcalEndcapNTrackClusterMatches", "EcalEndcapNClusters", "CalorimeterTrackProjections"},
      {"EcalEndcapNRemnantClusters", "EcalEndcapNExpectedClusters",
       "EcalEndcapNTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "HcalEndcapNRemnantClusters",
      {"HcalEndcapNTrackClusterMatches", "HcalEndcapNClusters", "CalorimeterTrackProjections"},
      {"HcalEndcapNRemnantClusters", "HcalEndcapNExpectedClusters",
       "HcalEndcapNTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  // central ------------------------------------------------------------

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "EcalBarrelRemnantClusters",
      {"EcalBarrelTrackClusterMatches", "EcalBarrelClusters", "CalorimeterTrackProjections"},
      {"EcalBarrelRemnantClusters", "EcalBarrelExpectedClusters",
       "EcalBarrelTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "HcalBarrelRemnantClusters",
      {"HcalBarrelTrackClusterMatches", "HcalBarrelClusters", "CalorimeterTrackProjections"},
      {"HcalBarrelRemnantClusters", "HcalBarrelExpectedClusters",
       "HcalBarrelTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  // forward ------------------------------------------------------------

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "EcalEndcapPRemnantClusters",
      {"EcalEndcapPTrackClusterMatches", "EcalEndcapPClusters", "CalorimeterTrackProjections"},
      {"EcalEndcapPRemnantClusters", "EcalEndcapPExpectedClusters",
       "EcalEndcapPTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "LFHCALRemnantClusters",
      {"LFHCALTrackSplitMergeClusterMatches", "LFHCALClusters", "CalorimeterTrackProjections"},
      {"LFHCALRemnantClusters", "LFHCALExpectedClusters", "LFHCALTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  app->Add(new JOmniFactoryGeneratorT<TrackClusterSubtractor_factory>(
      "HcalEndcapPInsertRemnantClusters",
      {"HcalEndcapPInsertTrackSplitMergeClusterMatches", "HcalEndcapPInsertClusters", "CalorimeterTrackProjections"},
      {"HcalEndcapPInsertRemnantClusters", "HcalEndcapPInsertExpectedClusters", "HcalEndcapPInsertTrackExpectedClusterMatches"},
      {.fracEnergyToSub = 1.0, .defaultMassPdg = 211, .surfaceToUse = 1},
      app // TODO: remove me once fixed
      ));

  // --------------------------------------------------------------------
  // PFA (1b) arbitration: form charged candidates
  // --------------------------------------------------------------------

  // backward -----------------------------------------------------------

  app->Add(
      new JOmniFactoryGeneratorT<CollectionCollector_factory<edm4eic::TrackClusterMatch, false>>(
          "EndcapNTrackExpectedClusterMatches",
          {"EcalEndcapNTrackExpectedClusterMatches", "HcalEndcapNTrackExpectedClusterMatches"},
          {"EndcapNTrackExpectedClusterMatches"}, app));

  app->Add(new JOmniFactoryGeneratorT<ChargedCandidateMaker_factory>(
      "EndcapNChargedCandidateParticlesAlpha", {"EndcapNTrackExpectedClusterMatches"},
      {"EndcapNChargedCandidateParticlesAlpha"}, {}, app));

  // central ------------------------------------------------------------

  app->Add(
      new JOmniFactoryGeneratorT<CollectionCollector_factory<edm4eic::TrackClusterMatch, false>>(
          "BarrelTrackExpectedClusterMatches",
          {"EcalBarrelTrackExpectedClusterMatches", "HcalBarrelTrackExpectedClusterMatches"},
          {"BarrelTrackExpectedClusterMatches"}, app));

  app->Add(new JOmniFactoryGeneratorT<ChargedCandidateMaker_factory>(
      "BarrelChargedCandidateParticlesAlpha", {"BarrelTrackExpectedClusterMatches"},
      {"BarrelChargedCandidateParticlesAlpha"}, {}, app));

  // forward ------------------------------------------------------------

  app->Add(
      new JOmniFactoryGeneratorT<CollectionCollector_factory<edm4eic::TrackClusterMatch, false>>(
          "EndcapPTrackExpectedClusterMatches",
          {"EcalEndcapPTrackExpectedClusterMatches", "LFHCALTrackExpectedClusterMatches"},
          {"EndcapPTrackExpectedClusterMatches"}, app));

  app->Add(new JOmniFactoryGeneratorT<ChargedCandidateMaker_factory>(
      "EndcapPChargedCandidateParticlesAlpha", {"EndcapPTrackExpectedClusterMatches"},
      {"EndcapPChargedCandidateParticlesAlpha"}, {}, app));

  app->Add(
      new JOmniFactoryGeneratorT<CollectionCollector_factory<edm4eic::TrackClusterMatch, false>>(
          "EndcapPInsertTrackExpectedClusterMatches",
          {"EcalEndcapPTrackExpectedClusterMatches",
           "HcalEndcapPInsertTrackExpectedClusterMatches"},
          {"EndcapPInsertTrackExpectedClusterMatches"}, app));

  app->Add(new JOmniFactoryGeneratorT<ChargedCandidateMaker_factory>(
      "EndcapPInsertChargedCandidateParticlesAlpha", {"EndcapPInsertTrackExpectedClusterMatches"},
      {"EndcapPInsertChargedCandidateParticlesAlpha"}, {}, app));

  // --------------------------------------------------------------------
  // PFA (2) arbitration: combine remnants, form neutral candidates
  // --------------------------------------------------------------------

  // backward -----------------------------------------------------------

  /* TODO add PFA2 EEEMCal here */
  /* TODO add PFA2 EHCal here */

  // central ------------------------------------------------------------

  /* TODO add PFA2 BEMC here */
  /* TODO add PFA2 BHCal here */

  // forward ------------------------------------------------------------

  /* TODO add PFA2 FEMC here */
  /* TODO add PFA2 LFHCAL here */
  /* TODO add PFA2 FHCal insert here */

  // --------------------------------------------------------------------
  // PFA (3) regression: convert candidates to reco particles
  // --------------------------------------------------------------------

  // backward -----------------------------------------------------------

  /* TODO add PFA3 EEEMCal here */
  /* TODO add PFA3 EHCal here */

  // central ------------------------------------------------------------

  /* TODO add PFA3 BEMC here */
  /* TODO add PFA3 BHCal here */

  // forward ------------------------------------------------------------

  /* TODO add PFA3 FEMC here */
  /* TODO add PFA3 LFHCAL here */
  /* TODO add PFA3 FHCal insert here */

  /* TODO collect reconstructed particles here */

}
} // extern "C"
