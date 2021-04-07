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
x = [
    0.001867519746044820,
    0.002275293677911463,
    0.002692845467883248,
    0.003119400211540369,
    0.003554151391578438,
    0.003996262853518041,
    0.004444870878876082,
    0.004899086349965267,
    0.005357997000181999,
    0.005820669743355830,
    0.006286153075466025,
    0.006753479541784039,
    0.007221668262275161,
    0.007689727507889525,
    0.008156657320192495,
    0.008621452166627776,
    0.009083103623574271,
    0.009540603079249766,
    0.009992944448431896,
    0.010439126890909214,
    0.010878157525543523,
    0.011309054131818317,
    0.011730847830767882,
    0.012142585737226980,
    0.012543333575412086,
    0.012932178249941664,
    0.013308230364524597,
    0.013670626680692492,
    0.014018532509122373,
    0.014351144026291085,
    0.014667690509420725,
    0.014967436482914990,
    0.015249683769748768,
    0.015513773441556675,
    0.015759087661469738,
    0.015985051414072162,
    0.016191134117190663,
    0.016376851110586923,
    0.016541765016997088,
    0.016685486971350718,
    0.016807677714403370,
    0.016908048547430839,
    0.016986362145057821,
    0.017042433223728004,
    0.017076129063764694,
    0.017087369883420026,
    0.017076129063764694,
    0.017042433223728004,
    0.016986362145057821,
    0.016908048547430839,
    0.016807677714403370,
    0.016685486971350718,
    0.016541765016997088,
    0.016376851110586923,
    0.016191134117190663,
    0.015985051414072162,
    0.015759087661469738,
    0.015513773441556675,
    0.015249683769748768,
    0.014967436482914990,
    0.014667690509420725,
    0.014351144026291085,
    0.014018532509122373,
    0.013670626680692492,
    0.013308230364524597,
    0.012932178249941664,
    0.012543333575412086,
    0.012142585737226980,
    0.011730847830767882,
    0.011309054131818317,
    0.010878157525543523,
    0.010439126890909214,
    0.009992944448431896,
    0.009540603079249766,
    0.009083103623574271,
    0.008621452166627776,
    0.008156657320192495,
    0.007689727507889525,
    0.007221668262275161,
    0.006753479541784039,
    0.006286153075466025,
    0.005820669743355830,
    0.005357997000181999,
    0.004899086349965267,
    0.004444870878876082,
    0.003996262853518041,
    0.003554151391578438,
    0.003119400211540369,
    0.002692845467883248,
    0.002275293677911463,
    0.001867519746044820,
]

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
   if i > (len(x)-1):
       average = 0
    
       for ii in range(len(x)):
           average = average + x[ii] * data1[i - ii - 1]
           
           
       filtered.append(float( average ))
       
       
   
   

Fs = len(t)/t[-1] # sample rate
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
ax1.set_title('A FIR: Too many to list' )#+ str(x))
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k') # plotting the fft
ax2.loglog(frqf,abs(Y_filt),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|A(freq)|')
plt.show()