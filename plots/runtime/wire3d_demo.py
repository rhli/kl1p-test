import csv

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import axes3d
from os import path, getenv

HOME = getenv('HOME')

file_path = path.join(HOME, 'src/cpp_src/kl1p_dev/test_results/without_noise/RunTimeMean_OMP.csv')

runtime_mean = np.array(list(csv.reader(open(file_path, "r"), delimiter=','))).astype('float')

#  print(runtime_mean)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
X, Y, Z = axes3d.get_test_data(0.05)

print("X is")
print(X)
print("Y is")
print(Y)
print("Z is")
print(Z)

ax.plot_wireframe(X, Y, Z, rstride=10, cstride=10)

plt.show()
