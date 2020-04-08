#!/bin/bash

rm outputs/photonflux*.png

while read mG tauG Gtot Bgnu Bznu Bwele Bwmuo Bwtau Bgnu3b
do
  echo $mG $tauG $Gtot $Bgnu $Bznu $Bwele $Bwmuo $Bwtau $Bgnu3b

  sed 's/mG/'${mG}'/g' getFlux.C.temp > getFlux.C
  sed -i 's/Gnu/'${Bgnu}'/g' getFlux.C
  sed -i 's/tau\_G/'${tauG}'/g' getFlux.C

  root.exe -q getFlux.C+g >> /tmp/comb.log
  rm getFlux.C getFlux_C.so
done < BRgF0.dat

