import csv
from os import getenv, path

import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from matplotlib.ticker import FormatStrFormatter, LinearLocator
from mpl_toolkits.mplot3d import Axes3D

# get results for plotting
HOME = getenv('HOME')
file_path = path.join(HOME, 'src/cpp_src/kl1p_dev/test_results/without_noise/MSEMean_OMP.csv')
runtime_mean = np.array(list(csv.reader(open(file_path, "r"), delimiter=','))).astype('float')

fig = plt.figure()
ax = fig.gca(projection='3d')

# init X and Y
X = np.arange(1, 126, 1)
Y = np.arange(1, 126, 1)
X, Y = np.meshgrid(X, Y)

# init Z
Z = runtime_mean

# plot 3d-surface
surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

# config Z axis
#  ax.set_zlim(0, 1)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

fig.colorbar(surf, shrink=0.5, aspect=5)

plt.savefig('./surface_3d.png', dpi=500)
