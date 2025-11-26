// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Derek Anderson

#pragma once

#include "extensions/jana/JOmniFactory.h"
#include "algorithms/particle/TrackProtoClusterMatchPromoter.h"

namespace eicrecon {

class TrackProtoClusterMatchPromoter_factory : public JOmniFactory<TrackProtoClusterMatchPromoter_factory> {

public:
  ///! alias for algorithm name
  using AlgoT = eicrecon::TrackProtoClusterMatchPromoter;

private:
  // pointer to algorithm
  std::unique_pt<AlgoT> m_algo;

  // input collections
  PodioInput<edm4eic::TrackProtoClusterMatch> m_track_proto_match_input{this};
  PodioInput<edm4eic::ProtoClusterCollection> m_proto_input{this};
  PodioInput<edm4eic::ClusterCollection> m_clust_input{this};

  // output collection
  PodioOutput<edm4eic::TrackClusterMatch> m_track_clust_match_output{this};

  // services
  Service<AlgorithmsInit_service> m_algoInitSvc{this};

public:
  ///! Configures algorithm
  void Configure() {
    m_algo = std::make_unique<AlgoT>(GetPrefix());
    m_algo->level(static_cast<algorithm::LogLevel>(logger()->level()));
    m_algo->applyConfig(config());
    m_algo->init();
  }

  ///! Primary algorithm call
  void Process(int32_t /*run_number*/, uint64_t /*event_number*/) {
    m_algo->process({m_track_proto_match_input(), m_proto_input(), m_clust_input()},
                    {m_track_clust_match_output.get()});
  }
}; // end TrackProtoClusterMatchPromoter_factory

} // namespace eicrecon
