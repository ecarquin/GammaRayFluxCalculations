#!/bin/bash

mG = 1000
Channels = ["MuAMuNue","EAENue","TauATauNue","TauAMuNue","ATauMuNue","EATauNue","AETauNue","EAMuNue","AEMuNue"]

for i in range (0,7)
  mG = mG + 500*i
  print "Gravitino mass: ",mG
  os.system('sed 's/mG/'+mG+'/g' main07.cmnd.temp > main07.cmnd.temp.1')
  for i in range (0,9)
    os.system('sed 's/Channel/'+Channels[i]+'/g' main07.cmnd.temp.1 > main07.cmnd')
    
