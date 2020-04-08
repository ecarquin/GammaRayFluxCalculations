import pylab as pl
import numpy as np

data = np.random.uniform(1e-4,1e+5,size=100000)
pl.hist(data, bins=np.logspace(-4, 0, 120))
pl.gca().set_xscale("log")
pl.gca().set_yscale("log")
bins = np.logspace(-4,0,120)
print bins
#pl.show()
