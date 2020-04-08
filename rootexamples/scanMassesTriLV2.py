#!/bin/bash

import os

mG = 1000
Channels = ["MuAMuNue","EAENue","TauATauNue","TauAMuNue","ATauMuNue","EATauNue","AETauNue","EAMuNue","AEMuNue"]

for i in range (0,1):
  mG = 3500 + 500*i
  if mG == 2500:
     continue
  print "Gravitino mass: ",mG," ",str(mG)
  os.system('sed \'s/mG/'+str(mG)+'/g\' main07.cmnd.temp > main07.cmnd.temp.1')
  for i in range (0,9):
    if i <= 3:
       continue
    print "Channel: ", Channels[i]
    os.system('sed \'/'+Channels[i]+'/s/\!\!//g\' main07.cmnd.temp.1 > main07.cmnd')
    os.system('./main07.exe > /tmp/'+Channels[i]+'_'+str(mG)+'.log 2>&1')
    os.system('mv out.root outputs/'+Channels[i]+'_'+str(mG)+'.root')
    os.system('sed \'s/mG/'+str(mG)+'/g\' MakePlotsTriLV2.C.temp > MakePlots.C.temp.1')
    os.system('sed \'s/Channel/'+Channels[i]+'/g\' MakePlots.C.temp.1 > MakePlots.C')
    os.system('root.exe -q MakePlots.C+g >> /tmp/root.log')
