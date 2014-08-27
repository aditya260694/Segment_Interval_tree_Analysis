import matplotlib.pyplot as plt
from pylab import figure, show
import numpy as np
x=[]
y=[]
f=open('t_brute.txt','r')
for i in f:
	i=i.split(' ')
	x.append(i[0])
	i[1]=i[1].split('\n')
	print i[1][0]
	y.append(i[1][0])
for i in range(len(x)):
	x[i]=int(x[i])/1000000
for i in range(len(y)):
	y[i]=int(y[i])

plt.plot(x,y)
plt.axis([0,600,0,1000])
plt.xlabel('Number of queries( x 1million)')
plt.ylabel('Time taken(seconds)')
plt.title('Time vs Number of queries for Brute-Force method')
plt.show()
