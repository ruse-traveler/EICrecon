#!/usr/bin/env ruby
# -----------------------------------------------------------------------------
# 'RunNPSim.rb'
# Derek Anderson
# 10.30.2023
#
# Run a certain number events in npsim based on
# specified steering and compact files.
# -----------------------------------------------------------------------------

# output file
out_file = "testRawHGCROCHit.e10pim_central.d19m8y2024.edm4hep.root"

# simulation parameters
numevts = 1000
steerer = "./central.forClusterMergeTests_e10pim.py"
compact = "$DETECTOR_PATH/epic.xml"

# run ddsim
exec("npsim --steeringFile #{steerer} --compactFile #{compact} -G -N #{numevts} --outputFile #{out_file}")

# end -------------------------------------------------------------------------
