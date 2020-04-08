#!/bin/bash

c=0

rm /tmp/comb.log outputs/plot*.png

while read mG tauG Gtot Bgnu Bznu Bwele Bwmuo Bwtau Bgnu3b
do
  echo $mG $tauG $Gtot $Bgnu $Bznu $Bwele $Bwmuo $Bwtau $Bgnu3b
  sed 's/mG/'${mG}'/g' MakePlots.C.temp > MakePlots.C
  sed -i 's/tauW/'${Bwtau}'/g' MakePlots.C
  sed -i 's/eW/'${Bwele}'/g' MakePlots.C
  sed -i 's/muW/'${Bwmuo}'/g' MakePlots.C
  sed -i 's/nuZ/'${Bznu}'/g' MakePlots.C
  sed -i 's/Gnu/'${Bgnu}'/g' MakePlots.C
  sed -i 's/G3bnu/'${Bgnu3b}'/g' MakePlots.C
  sed -i 's/tauG/'$tauG'/g' MakePlots.C

  root.exe -q MakePlots.C+g >> /tmp/comb.log

  #cp MakePlots.C MakePlots.C.$mG
  c=`expr $c + 1`
  echo $c
done < BRg.0.dat
