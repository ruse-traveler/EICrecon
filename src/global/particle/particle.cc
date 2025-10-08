// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Derek Anderson

#include <JANA/JApplicationFwd.h>
#include <JANA/Utils/JTypeInfo.h>
#include <edm4eic/EDM4eicVersion.h>
#include <string>
#include <vector>

#include "extensions/jana/JOmniFactoryGeneratorT.h"

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

  /* TODO add PFA1(a) EEEMCal here */
  /* TODO add PFA1(a) EHCal here */

  // central ------------------------------------------------------------

  /* TODO add PFA1(a) BEMC here */
  /* TODO add PFA1(a) BHCal here */

  // forward ------------------------------------------------------------

  /* TODO add PFA1(a) FEMC here */
  /* TODO add PFA1(a) LFHCAL here */
  /* TODO add PFA1(a) FHCal insert here */

  // --------------------------------------------------------------------
  // PFA (1b) arbitration: form charged candidates
  // --------------------------------------------------------------------

  /* TODO collect expected clusters + matched tracks here */
  /* TODO add PFA1(b) here */

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

  /* TODO collect charged + neutral candidates here */
  /* TODO add PFA3 here */

}
} // extern "C"
