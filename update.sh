#!/bin/bash

rm -rv src/algorithms/particle/
rm -rv src/factories/particle/
rm -rv src/global/particle/
cp -rv ../development/ForParticleFlow/mark2/new/algorithms/particle/ ./src/algorithms/
cp -rv ../development/ForParticleFlow/mark2/new/factories/particle/ ./src/factories/
cp -rv ../development/ForParticleFlow/mark2/new/global/particle/ ./src/global/
