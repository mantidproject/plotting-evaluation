import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
from matplotlib.collections import PatchCollection
import numpy as np
import time

# Load 2D test data
X_BINS = np.loadtxt('raggeddata-x.txt')
Y_PTS = np.loadtxt('raggeddata-y.txt')
Z_VALUES = np.loadtxt('raggeddata-signal.txt')

# Convert data to expected layout
NY_PTS = Y_PTS.shape[0]
Y_BINS = np.zeros(NY_PTS + 1)
for i in range(NY_PTS - 1):
    Y_BINS[i+1] = 0.5*(Y_PTS[i+1] + Y_PTS[i])
# Ends
Y_BINS[0] = Y_PTS[0] - (Y_BINS[1] - Y_PTS[0])
Y_BINS[-1] = Y_PTS[NY_PTS - 1] + (Y_PTS[NY_PTS-1] - Y_BINS[NY_PTS - 1])

patches = []
colours = []
nx_pts, ny_pts = X_BINS.shape[1] - 1, Y_PTS.shape[0]

start = time.time()
for i in range(ny_pts):
    y_i, y_ip1 = Y_BINS[i], Y_BINS[i+1]
    x_y = X_BINS[i]
    c_y = Z_VALUES[i]
    for j in range(nx_pts):
        vertices = [(x_y[j], y_i), (x_y[j+1], y_i),
                    (x_y[j+1], y_ip1), (x_y[j], y_ip1)]
        polygon = Polygon(vertices)
        patches.append(polygon)
        colours.append(c_y[j])
print "Time to construct vertices", (time.time() - start), 's'

start = time.time()
fig, ax = plt.subplots()
p = PatchCollection(patches, cmap='viridis', linewidths=(0.,))
p.set_array(np.array(colours))
mesh = ax.add_collection(p)
plt.colorbar(p)
mesh.set_clim(0, 200)
plt.ylim(0, 10)
plt.xlim(0, 60)
print "Time to create plot", (time.time() - start), 's'
plt.show()
