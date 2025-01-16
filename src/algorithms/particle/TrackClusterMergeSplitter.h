// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

#pragma once

#include <DD4hep/Detector.h>
#include <algorithms/algorithm.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/EDM4eicVersion.h>
#if EDM4EIC_VERSION_MAJOR >= 8
#include <edm4eic/TrackClusterMatchCollection.h>
#endif
#include <edm4eic/Track.h>
#include <edm4eic/TrackPoint.h>
#include <edm4eic/TrackSegmentCollection.h>
#include <edm4hep/Vector3f.h>
#include <podio/ObjectID.h>
#include <algorithm>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "PFTools.h"
#include "TrackClusterMergeSplitterConfig.h"
#include "algorithms/interfaces/WithPodConfig.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Algorithm input/output
  // --------------------------------------------------------------------------
  using TrackClusterMergeSplitterAlgorithm = algorithms::Algorithm<
    algorithms::Input<
      edm4eic::ClusterCollection,
      edm4eic::TrackSegmentCollection
    >,
    algorithms::Output<
#if EDM4EIC_VERSION_MAJOR >= 8
      edm4eic::ClusterCollection,
      edm4eic::TrackClusterMatchCollection
#else
      edm4eic::ClusterCollection
#endif
    >
  >;



  // --------------------------------------------------------------------------
  //! Track-Based Cluster Merger/Splitter
  // --------------------------------------------------------------------------
  /*! An algorithm which takes a collection of proto-clusters, matches
   *  track projections, and then decides to merge or split those proto-
   *  clusters based on average E/p from simulations.
   *
   *  Heavily inspired by Eur. Phys. J. C (2017) 77:466
   */
  class TrackClusterMergeSplitter :
    public TrackClusterMergeSplitterAlgorithm,
    public WithPodConfig<TrackClusterMergeSplitterConfig>
  {

    public:

      // ctor
      TrackClusterMergeSplitter(std::string_view name) :
        TrackClusterMergeSplitterAlgorithm {
          name,
          {"InputProtoClusterCollection", "InputTrackProjections"},
#if EDM4EIC_VERSION_MAJOR >= 8
          {"OutputProtoClusterCollection", "OutputTrackClusterMatches"},
#else
          {"OutputProtoClusterCollection"},
#endif
          "Merges or splits clusters based on tracks projected to them."
        } {}

      // public methods
      void init(const dd4hep::Detector* detector);
      void process (const Input&, const Output&) const final;

    private:

      // private methods
      void get_projections(
        const edm4eic::TrackSegmentCollection* projections,
        PFTools::VecProj& relevant_projects,
        PFTools::VecTrk& relevant_trks
      ) const;
      void match_clusters_to_tracks(
        const edm4eic::ClusterCollection* clusters,
        const PFTools::VecProj& projections,
        const PFTools::VecTrk& tracks,
        PFTools::MapToVecProj& matched_projects,
        PFTools::MapToVecTrk& matched_tracks
      ) const;
      void merge_and_split_clusters(
        const PFTools::VecClust& to_merge,
        const PFTools::VecProj& to_split,
        std::vector<edm4eic::MutableCluster>& new_clusters
      ) const;
      void make_cluster(
        const PFTools::VecClust& old_clusts,
        edm4eic::MutableCluster& new_clust,
        std::optional<PFTools::MatrixF> split_weights = std::nullopt
      ) const;

      // calorimeter id
      int m_idCalo {0};

  };  // end TrackClusterMergeSplitter

}  // end eicrecon namespace
