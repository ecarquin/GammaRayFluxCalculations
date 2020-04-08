#!/bin/bash

c=0

while read mG tauG Gtot Bgnu Bznu Bwele Bwmuo Bwtau Bgnu3b
do
  echo $mG $tauG $Gtot $Bgnu $Bznu $Bwele $Bwmuo $Bwtau $Bgnu3b
  sed 's/mG/'${mG}'/g' main07.cmnd.temp > main07.cmnd.temp.1

  make main07

  #Run G->Hnu decay generation
  sed '/Hnu/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  ./main07.exe | tee /tmp/hnu_${mG}.log
  mv out.root outputs/Hnu_${mG}.root
  cat main07.cmnd > Hnu.log

  #Run G->Wtau decay generation
  sed '/Wtau/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  ./main07.exe | tee /tmp/wt_${mG}.log
  mv out.root outputs/Wtau_${mG}.root
  cat main07.cmnd > Wtau.log

  #Run G->Wmu decay generation
  sed '/Wmu/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  ./main07.exe | tee /tmp/wm_${mG}.log
  mv out.root outputs/Wmu_${mG}.root
  cat main07.cmnd > Wmu.log

  #Run G->We decay generation
  sed '/We/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  ./main07.exe | tee /tmp/we_${mG}.log
  mv out.root outputs/We_${mG}.root
  cat main07.cmnd > We.log

  #Run G->Znu decay generation
  sed '/WeakZ0\:gmZmode\=2/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  sed -i '/Znu/s/\!\!//g' main07.cmnd
  ./main07.exe | tee /tmp/znu_${mG}.log
  mv out.root outputs/Znu_${mG}.root
  cat main07.cmnd > Znu.log

  cp main07.cc main07.cc.bkup

  #Run G->g*nu decay generation
  sed '/WeakZ0\:gmZmode\=1/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  sed -i '/gammanu/s/\!\!//g' main07.cmnd
  sed -i '/TimeShower\:mMaxGamma/s/\!\!//g' main07.cmnd
  sed -i 's/0\.001/'${mG}'/g' main07.cmnd
  sed -i '/numberOfEvents/s/2000000/5000000/g' main07.cmnd
  sed '/checkVirtualg/s/false/true/g' main07.cc.bkup > main07.cc
  #sed -i '/23\:mMin/s/\!\!//g' main07.cmnd
  #sed -i '/23\:offIfAny/s/\!\!//g' main07.cmnd
  make main07
  ./main07.exe | tee /tmp/znuprime_${mG}.log
  mv out.root outputs/GammaOffnu_${mG}.root
  cat main07.cmnd > gammanuprime.log
  cat main07.cc >> gammanuprime.log

  cp main07.cc.bkup main07.cc

  make main07

  #Run G->gnu decay generation  
  sed '/gammanu/s/\!\!//g' main07.cmnd.temp.1 > main07.cmnd
  sed -i '/TimeShower\:mMaxGamma/s/\!\!//g' main07.cmnd
  cat main07.cmnd > gammanu.log
  ./main07.exe | tee /tmp/gnu_${mG}.log
  mv out.root outputs/Gammanu_${mG}.root
  c=`expr $c + 1`
  echo $c
done < BRg.0.dat

rm main07.cmnd.temp.1 
