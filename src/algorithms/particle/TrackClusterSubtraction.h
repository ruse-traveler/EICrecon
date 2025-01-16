// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Derek Anderson

#pragma once

#include <DD4hep/Detector.h>
#include <algorithms/algorithm.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/TrackPoint.h>
#include <edm4eic/TrackSegmentCollection.h>
#include <edm4hep/Vector3f.h>
#include <podio/ObjectID.h>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

// for algorithm configuration
#include "TrackClusterSubtractionConfig.h"
#include "algorithms/interfaces/WithPodConfig.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Algorithm input/output
  // --------------------------------------------------------------------------
  using TrackClusterSubtractionAlgorithm = algorithms::Algorithm<
    algorithms::Input<
      edm4eic::ClusterCollection,
      edm4eic::ClusterCollection,
      edm4eic::TrackSegmentCollection
    >,
    algorithms::Output<
      edm4eic::ClusterCollection,
      edm4eic::ClusterCollection
    >
  >;



  // --------------------------------------------------------------------------
  //! Track-Cluster Subtraction
  // --------------------------------------------------------------------------
  /*! An algorithm which takes collections of EM and HCal clusters, matches
   *  track projections, subtracts the sum of the energy the projections
   *  to the clusters, and returns the remnants of the subtracted clusters.
   */
  class TrackClusterSubtraction :
    public TrackClusterSubtractionAlgorithm,
    public WithPodConfig<TrackClusterSubtractionConfig>
  {

    public:

      // ctor
      TrackClusterSubtraction(std::string_view name) :
        TrackClusterSubtractionAlgorithm {
          name,
          {
            "InputEMCalClusterCollection",
            "InputHCalClusterCollection",
            "InputTrackProjections"
          },
          {"OutputClusterCollection"},
          "Subtracts energy of tracks pointing to clusters."
        } {}

      // public methods
      void init(const dd4hep::Detector* detector);
      void process (const Input&, const Output&) const final;

    private:

      // private methods
      /* TODO fill in */

      // calorimeter id
      int m_idCalo {0};

  };  // end TrackClusterSubtraction

}  // end eicrecon namespace
