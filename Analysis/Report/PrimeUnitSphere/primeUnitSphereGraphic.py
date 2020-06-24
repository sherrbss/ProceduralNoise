from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib import rcParams
import numpy as np
from math import sin, cos, floor, pi, acos
from itertools import product, combinations
from random import seed
from random import random

seed(1)

rcParams['xtick.color'] = (0.0, 0.0, 0.0, 0.2)
rcParams['ytick.color'] = (0.0, 0.0, 0.0, 0.2)
rcParams['axes.labelcolor'] = (0.0, 0.0, 0.0, 0.2)
rcParams['axes.edgecolor'] = (0.0, 0.0, 0.0, 0.2)

fig = plt.figure(figsize=(7.5,7.5))
cm = plt.get_cmap("GnBu")


ax = fig.gca(projection='3d')

# Configure axis appearence
fig.set_facecolor('white')
ax.set_facecolor('white')

#ax.grid('off')
ax.grid(False)

ax.w_xaxis.pane.fill = False
ax.w_yaxis.pane.fill = False
ax.w_zaxis.pane.fill = False

ax.w_xaxis.set_pane_color((0.0, 0.0, 0.0, 0.2))
ax.w_yaxis.set_pane_color((0.0, 0.0, 0.0, 0.2))
ax.w_zaxis.set_pane_color((0.0, 0.0, 0.0, 0.2))

ax.xaxis.pane.set_edgecolor((0.0, 0.0, 0.0, 0.2))
ax.yaxis.pane.set_edgecolor((0.0, 0.0, 0.0, 0.2))
ax.zaxis.pane.set_edgecolor((0.0, 0.0, 0.0, 0.2))
#ax.set_axis_off()

ax.grid(False)      # Hide grid lines
ax.set_xticks([])   # Hide axes ticks
ax.set_yticks([])   # Hide axes ticks
ax.set_zticks([])   # Hide axes ticks

csfont = {'fontname':'Times New Roman'}
ax.set_xlabel('X axis', **csfont)
ax.set_ylabel('Z axis', **csfont)
ax.set_zlabel('Y axis', **csfont)

# Draw sphere
u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
x = np.cos(u)*np.sin(v)
y = np.sin(u)*np.sin(v)
z = np.cos(v)
ax.plot_wireframe(x, y, z, color="k", alpha=0.2)


# Checks if a given value is prime
def isPrime(val):
    for i in range(2, val):
        if (i*i <= val):
            if (val % i == 0):
                return False
        else:
            return True
    return True


# Generate plot points
current = 2
count = 0
numPrimes = 256

theta_ = []
phi_ = []

while(count < numPrimes):
    if(isPrime(current) or current == 2 or current == 3):
        
        theta = current**2
        phi = current**0.5
        
        u = ((phi - (phi // (2*3.14159)) * (2*3.14159)) / 3.14159) - 1
        
        tempX = ((1 - u**2)**0.5) * cos(theta)
        tempY = ((1 - u**2)**0.5) * sin(theta)
        tempZ = u
        
        # Generate depth-based colour mapping
        distX = abs(-1 - tempX)
        distY = abs(1 - tempY)
        distZ = abs(1 - tempZ)
        
        # Darker points closer to camera
        mag = 1 - (((distX * distX + distY * distY + distZ + distZ)**0.5) / (12**0.5)) * (1 - .35)
        col = cm(mag)
        
        # Plot
        ax.scatter([tempX], [tempZ], [tempY], color=col, alpha=1)
    
    
    
        '''
        theta = (current**2)
        phi = (current**0.5)
        
        theta_.append(theta - ((theta // (2*3.14159)) * (2*3.14159)))
        phi_.append(phi - ((phi // (2*3.14159)) * (2*3.14159)))
        
        tempX = sin(theta) * cos(phi)
        tempY = sin(theta) * sin(phi)
        tempZ = cos(theta)
        
        # Generate depth-based colour mapping
        distX = abs(-1 - tempX)
        distY = abs(1 - tempY)
        distZ = abs(1 - tempZ)
        
        # Darker points closer to camera
        mag = 1 - (((distX * distX + distY * distY + distZ + distZ)**0.5) / (12**0.5)) * (1 - .35)
        col = cm(mag)
        
        # Plot
        ax.scatter([tempX], [tempZ], [tempY], color=col, alpha=1)
        '''
        
        
        
        count += 1

    current += 1


# Set view
ax.view_init(20,135)

# Save/show
plt.savefig("primeUnitSphere.pdf", bbox_inches='tight')
#plt.savefig("primeUnitSphere.pdf", bbox_inches=None)
#plt.show()

'''
#print(theta_)
#print()
#print(phi_)
cm = plt.cm.get_cmap('RdYlBu')
xy = range(20)
z = xy
sc = plt.scatter(xy, xy, c=xy, vmin=0, vmax=20, s=35, cmap=cm)
'''

'''
#sc = plt.hist(theta_, bins=32, range=(0, 2621161))
#sc = plt.hist(phi_, bins=32, range=(0, 40.3))
#sc = plt.hist(theta_, bins=32, range=(0, 2*3.14159))
sc = plt.hist(phi_, bins=32, range=(0, 2*3.14159))
'''

#plt.colorbar(sc)
plt.show()
