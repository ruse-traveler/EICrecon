// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

#ifndef EICRECON_HGCROCHITDIGI_H
#define EICRECON_HGCROCHITDIGI_H

#include <algorithm>
#include <algorithms/algorithm.h>
#include <string_view>
// edm4hep types
#include <edm4hep/RawTimeSeriesCollection.h>
// edm4eic types
#include <edm4eic/RawHGCROCHitCollection.h>

// for algorithm configuration
#include "HGCROCHitDigiConfig.h"
#include "algorithms/interfaces/WithPodConfig.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Algorithm input/output
  // --------------------------------------------------------------------------
  // TODO fill in raw-to-sim assocations
  using HGCROCHitDigiAlgorithm = algorithms::Algorithm<
    algorithms::Input<
      edm4hep::RawTimeSeriesCollection
    >,
    algorithms::Output<
      edm4eic::RawHGCROCHitCollection
    >
  >;



  // --------------------------------------------------------------------------
  //! HGCROC Hit Digitization
  // --------------------------------------------------------------------------
  /*! An algorithm which takes a collection of waveforms (edm4hep::RawTimeSeries)
   *  and digitizes them to produce HGCROC hits (edm4eic::RawHGCROCHit), which
   *  record the amplitude, time-over-threshold, and time-of arrival.
   */
  class HGCROCHitDigi :
    public HGCROCHitDigiAlgorithm,
    public WithPodConfig<HGCROCHitDigiConfig>
  {

    public:

      // ctor
      HGCROCHitDigi(std::string_view name) :
        HGCROCHitDigiAlgorithm {
          name,
          {"InputRawTimeSeriesCollection"},
          {"OutputRawHGCROCHitCollection"},
          "Digitizes input waveforms into raw HGCROC hits."
        } {}

      // public methods
      void init();
      void process(const Input&, const Output&) const final;

  };  // end HGCROCHitDigi

}  // end eicrecon namespace

#endif
