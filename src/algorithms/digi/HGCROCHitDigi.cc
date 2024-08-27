// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2024 Derek Anderson

// edm4hep types
#include <edm4hep/RawTimeSeries.h>
// edm4eic types
#include <edm4eic/RawHGCROCHit.h>

// algorithm definition
#include "HGCROCHitDigi.h"



namespace eicrecon {

  // --------------------------------------------------------------------------
  //! Initialize algorithm
  // --------------------------------------------------------------------------
  void HGCROCHitDigi::init() {

    /* TODO fill in */

  }  // end 'init()'



  // --------------------------------------------------------------------------
  //! Process inputs
  // --------------------------------------------------------------------------
  void HGCROCHitDigi::process(
    const HGCROCHitDigi::Input& input,
    const HGCROCHitDigi::Output& output
  ) const {

    // grab inputs/outputs
    const auto [in_waveforms] = input;
    auto [out_rawhits] = output;

  }  // end 'process(Input&, Output&)'

}  // end eicrecon namespace
