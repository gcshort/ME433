# -*- coding: utf-8 -*-
"""
Created on Fri Apr  2 20:29:51 2021

@author: garre
"""

# -*- coding: utf-8 -*-
"""
Created on Fri Apr  2 19:45:43 2021

@author: garre
"""

import csv
import matplotlib.pyplot as plt
import numpy as np

t = [] # column 0
data1 = [] # column 1
filtered = []
new_average = []
a = .997
b = 0.003


with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column


for i in range(len(t)):
   #print the data to verify it was read
  # print(str(t[i]) + ", " + str(data1[i]))
   if i == 0:
       new_average.append(float(data1[i]))
   else:
       new_average.append(float(a*new_average[i-1] + b*data1[i]))
           
       
       
   
   

Fs = len(t)/t[-1] # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

nn = len(new_average)
kf = np.arange(nn)
Tf = nn/Fs
frqf = kf/Tf # two sides frequency range
frqf = frq[range(int(nn/2))] # one side frequency range
Y_filt = np.fft.fft(new_average)/nn
Y_filt = Y_filt[range(int(nn/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)

ax1.plot(t,y,'k')
ax1.plot(t,new_average,'r')
ax1.set_title('A with IIR A:' + str(a) + " B: " + str(b))
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k') # plotting the fft
ax2.loglog(frqf,abs(Y_filt),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|A(freq)|')
plt.show()