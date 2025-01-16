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

#include "TrackClusterSubtraction.h"
#include "algorithms/particle/TrackClusterSubtractionConfig.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Initialize algorithm
  // --------------------------------------------------------------------------
  void TrackClusterSubtraction::init(const dd4hep::Detector* detector) {

    // grab detector id
    m_idCalo = detector -> constant<int>(m_cfg.idCalo);
    debug("Collecting projections to detector with system id {}", m_idCalo);

  }  // end 'init(dd4hep::Detector*)'



  // --------------------------------------------------------------------------
  //! Process inputs
  // --------------------------------------------------------------------------
  /*! Subtract energy of matched tracks
   */
  void TrackClusterSubtraction::process(
    const TrackClusterSubtraction::Input& input,
    const TrackClusterSubtraction::Output& output
  ) const {

    // grab inputs/outputs
    const auto [in_clusters, in_matches, in_projections] = input;
    auto [out_clusters, out_matches] = output;

    // exit if no clusters in collection
    if (in_clusters->size() == 0) {
      debug("No clusters in input collection.");
      return;
    }

    // exit if no matched tracks in collection
    if (in_matches->size() == 0) {
      debug("No matched tracks in collection.");
      return;
    }

    /* TODO
     *   - build map of cluster onto tracks
     *   - grab associated track point of each track
     *   - sum momentum
     *   - subtract
     *   - write output
     *     - remnant clusters
     *     - remnant-track matches
     */

  }  // end 'get_projections(edm4eic::CalorimeterHit&, edm4eic::TrackSegmentCollection&, VecTrkPoint&)'

}  // end eicrecon namespace
