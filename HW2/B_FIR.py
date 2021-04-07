# -*- coding: utf-8 -*-
"""
Created on Mon Apr  5 20:37:56 2021

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
x  = [
    0.000000000000000000,
    0.000001362373262264,
    0.000006672731031130,
    0.000017915754010629,
    0.000037314165226615,
    0.000067373453488692,
    0.000110920076223299,
    0.000171129986974283,
    0.000251544543241352,
    0.000356071190407984,
    0.000488966778523625,
    0.000654801937168897,
    0.000858405591758571,
    0.001104789430890086,
    0.001399052904149428,
    0.001746270116349268,
    0.002151360759407147,
    0.002618947958566805,
    0.003153206577703624,
    0.003757706103001320,
    0.004435252681944719,
    0.005187735215459626,
    0.006015980569538195,
    0.006919622978111987,
    0.007896992545934787,
    0.008945027429119018,
    0.010059213777774856,
    0.011233556881598801,
    0.012460586182238578,
    0.013731395927644063,
    0.015035722269383113,
    0.016362056573387476,
    0.017697793659536682,
    0.019029412638997451,
    0.020342687013707519,
    0.021622919772388026,
    0.022855198392626796,
    0.024024663966567709,
    0.025116788132328260,
    0.026117651133467555,
    0.027014214158250543,
    0.027794579136807673,
    0.028448229399072981,
    0.028966245014805742,
    0.029341487238084815,
    0.029568747245582585,
    0.029644855268510583,
    0.029568747245582585,
    0.029341487238084819,
    0.028966245014805745,
    0.028448229399072981,
    0.027794579136807673,
    0.027014214158250543,
    0.026117651133467559,
    0.025116788132328267,
    0.024024663966567703,
    0.022855198392626799,
    0.021622919772388029,
    0.020342687013707519,
    0.019029412638997458,
    0.017697793659536682,
    0.016362056573387483,
    0.015035722269383121,
    0.013731395927644056,
    0.012460586182238579,
    0.011233556881598805,
    0.010059213777774852,
    0.008945027429119023,
    0.007896992545934782,
    0.006919622978111990,
    0.006015980569538197,
    0.005187735215459625,
    0.004435252681944722,
    0.003757706103001323,
    0.003153206577703625,
    0.002618947958566804,
    0.002151360759407150,
    0.001746270116349269,
    0.001399052904149429,
    0.001104789430890086,
    0.000858405591758570,
    0.000654801937168898,
    0.000488966778523625,
    0.000356071190407983,
    0.000251544543241352,
    0.000171129986974283,
    0.000110920076223299,
    0.000067373453488692,
    0.000037314165226615,
    0.000017915754010629,
    0.000006672731031130,
    0.000001362373262264,
    0.000000000000000000,
]




with open('sigB.csv') as f:
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
           
           
       filtered.append(float( average))
       
       
   
   

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
ax1.set_title('B FIR: Too many to list(93)')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'k') # plotting the fft
ax2.loglog(frqf,abs(Y_filt),'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|B(freq)|')
plt.show()