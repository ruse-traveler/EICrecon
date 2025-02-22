// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

#include <edm4eic/CalorimeterHit.h>
#include <edm4hep/Vector3f.h>
#include <edm4hep/utils/vector_utils.h>
#include <fmt/core.h>
#include <podio/ObjectID.h>
#include <podio/RelationRange.h>
#include <stdint.h>
#include <cmath>
#include <cstddef>
#include <gsl/pointers>

#include "TrackClusterSubtractor.h"
#include "algorithms/particle/TrackClusterSubtractorConfig.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Initialize algorithm
  // --------------------------------------------------------------------------
  void TrackClusterSubtractor::init() {

    //... nothing to do ...//

  }  // end 'init(dd4hep::Detector*)'



  // --------------------------------------------------------------------------
  //! Process inputs
  // --------------------------------------------------------------------------
  /*! Subtract energy of matched tracks via the following algorithm.
   *    1. Build a map of each cluster onto a list of matched
   *       track projections.
   *    2. For each cluster, subtract the sum of momenta of
   *       all matched tracks scaled by the specified fraction
   *       from the cluster's energy.
   *    3. If subtracted energy is greater than 0, copy cluster
   *       into output with new subtracted energy.
   */
  void TrackClusterSubtractor::process(
    const TrackClusterSubtractor::Input& input,
    const TrackClusterSubtractor::Output& output
  ) const {

    // grab inputs/outputs
    const auto [in_matches, in_projections] = input;
    auto [out_clusters, out_matches] = output;

    // exit if no matched tracks in collection
    if (in_matches->size() == 0) {
      debug("No matched tracks in collection.");
      return;
    }

    // ------------------------------------------------------------------------
    // 1. Build map of clusters onto projections
    // ------------------------------------------------------------------------
    PFTools::MapToVecProj mapClustToProj;
    for (const auto& match : *in_matches) {
      for (const auto& project : *in_projections) {

        // pick out corresponding projection from track
        if (match.getTrack() != project.getTrack()) {
          continue;
        }

        // locate relevant point to measure momentum
        bool foundPoint = false;
        for (const auto& point : project.getPoints()) {

          // pick out surface specified in configuration
          if (point.surface != m_cfg.surfaceToUse) {
            continue;
          }        

          // add to map and break 
          mapClustToProj[ match.getCluster() ].push_back(point);
          break;
        }

        // break if needed
        if (foundPoint) {
          break;
        }
      }  // end projection loop
    }  // end track-cluster match loop
    debug("Built map of clusters-onto-tracks, size = {}", mapClustToProj.size());

    // lambda to sum momenta of matched tracks
    auto sumMomenta = [](const PFTools::VecProj& projects) {
      double sum = 0.;
      for (const auto& project : projects) {
        sum += edm4hep::utils::magnitude( project.momentum );
      }
      return sum;
    };

    // ------------------------------------------------------------------------
    // 2. Do subtraction
    // ------------------------------------------------------------------------ 
    /* TODO will go here */

    /* TODO
     *   - sum momentum
     *   - subtract
     *   - write output
     *     - remnant clusters
     *     - remnant-track matches
     */

  }  // end 'get_projections(edm4eic::CalorimeterHit&, edm4eic::TrackSegmentCollection&, VecTrkPoint&)'

}  // end eicrecon namespace
