# -*- coding: utf-8 -*-
"""
Created on Wed Apr 21 15:05:17 2021

@author: garre
"""

def triangle(length, amplitude):
     section = length // 4
     for i in range(section):
         yield int(i * (amplitude / section) * 1)
     for i in range(section):
         yield int((amplitude - (i * (amplitude / section))) * 1)
             


y = list(triangle(200, 4096))

import numpy as np
from scipy.io import wavfile

fs = 100

f = 0.5
t = 0.5

samples = np.linspace(0, t, int(fs*t), endpoint=False)


signal = np.sin(2 * np.pi * f * samples)

signal *= 100

signal = np.int16(signal)

