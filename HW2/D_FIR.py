# -*- coding: utf-8 -*-
"""
Created on Tue Apr  6 19:36:36 2021

@author: garre
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Apr  5 20:27:36 2021

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
x =[
    0.002519950945123121,
    0.003200555561023921,
    0.003965279177753558,
    0.004814153895085516,
    0.005745924142896251,
    0.006757989235817686,
    0.007846369256314174,
    0.009005695843324084,
    0.010229228970274864,
    0.011508900265511456,
    0.012835382871426267,
    0.014198187268322619,
    0.015585781918437234,
    0.016985737028058990,
    0.018384889194727038,
    0.019769524215066392,
    0.021125574889150081,
    0.022438830280488247,
    0.023695152586563791,
    0.024880697551324688,
    0.025982134214395533,
    0.026986859746124612,
    0.027883205164918178,
    0.028660627873392911,
    0.029309887180230018,
    0.029823199290609313,
    0.030194368643030371,
    0.030418892935587451,
    0.030494039710043420,
    0.030418892935587451,
    0.030194368643030371,
    0.029823199290609302,
    0.029309887180230018,
    0.028660627873392911,
    0.027883205164918178,
    0.026986859746124612,
    0.025982134214395530,
    0.024880697551324688,
    0.023695152586563791,
    0.022438830280488247,
    0.021125574889150081,
    0.019769524215066402,
    0.018384889194727038,
    0.016985737028058990,
    0.015585781918437234,
    0.014198187268322619,
    0.012835382871426267,
    0.011508900265511456,
    0.010229228970274864,
    0.009005695843324084,
    0.007846369256314170,
    0.006757989235817686,
    0.005745924142896251,
    0.004814153895085517,
    0.003965279177753558,
    0.003200555561023923,
    0.002519950945123121,
]

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column


for i in range(len(t)):
   #print the data to verify it was read
  # print(str(t[i]) + ", " + str(data1[i]))
   if i > (len(x)-1):
       average = 0
    
       for ii in range(len(x)):
           average = average + x[ii] * data1[i - ii - 1]
           
           
       filtered.append(float( average ))
       
       
   
   

Fs = len(t)/t[-1] # sample rate
print(Fs)
Ts = 1.0/Fs; # sampling interval
print(Fs)
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

nn = len(filtered)
kf = np.arange(nn)
Tf = nn/Fs
frqf = kf/Tf # two sides frequency range
frqf = frq[range(int(nn/2))] # one side frequency range
Y_filt = np.fft.fft(filtered)/nn
Y_filt = Y_filt[range(int(nn/2))]
fig, (ax1, ax2) = plt.subplots(2, 1)

ax1.plot(t,y,'k')
ax1.plot(t[len(x):n],filtered,'r')
ax1.set_title('D FIR: Too many to list' )#+ str(x))
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k') # plotting the fft
ax2.loglog(frqf,abs(Y_filt),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|D(freq)|')
plt.show()