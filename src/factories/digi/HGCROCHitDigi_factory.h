// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

#pragma once

// eicrecon components
#include "extensions/jana/JOmniFactory.h"
#include "services/algorithms_init/AlgorithmsInit_service.h"
#include "algorithms/digi/HGCROCHitDigi.h"

namespace eicrecon {

  // --------------------------------------------------------------------------
  //! HGCROCHit Raw Hit factory
  // --------------------------------------------------------------------------
  /*! Generic factory to run the HGCROCHitDigi algorithm.
   */ 
  class HGCROCHitDigi_factory : public JOmniFactory<HGCROCHitDigi_factory, HGCROCHitDigiConfig> {

    public:

      using AlgoT = eicrecon::HGCROCHitDigi;

    private:

      // algorithm to run
      std::unique_ptr<AlgoT> m_algo;

      // input collections
      PodioInput<edm4hep::RawTimeSeries> m_rawtimeseries_input {this};

      // output collections
      PodioOutput<edm4eic::RawHGCROCHit> m_rawhits_output {this};

      // parameters
      /* TODO fill in */

      // services
      Service<AlgorithmsInit_service> m_algoInitSvc {this};

    public:

      void Configure() {
        m_algo = std::make_unique<AlgoT>(GetPrefix());
        m_algo -> applyConfig( config() );
        m_algo -> init();
      }

      void ChangeRun(int64_t run_number) {
        /* nothing to do here */
      }

      void Process(int64_t run_number, uint64_t event_number) {
        m_algo -> process(
          {m_rawtimeseries_input()},
          {m_rawhits_output().get()}
        );
      }

  };  // end HGCROCHitDigi_factory

}  // end eicrecon namespace
