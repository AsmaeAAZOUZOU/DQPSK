import numpy as np
from matplotlib.pyplot import *
import scipy as sc
import math
import sys
import matplotlib
matplotlib.use('Agg')


def energie(signal, Fe,seuil):
    sig_size = signal.size  # taille du signal reçu
    Bandwidth = 10**6         # bande de fréquence
    Nfft = 128
    Nb_windows = sig_size//Nfft
    Energie = np.empty(Nb_windows)
    for i in range(Nb_windows):
        signal_FFT = abs(np.fft.fft(signal[0+i*Nfft:Nfft+i*Nfft]))  #fft
        signal_freq = np.fft.fftfreq(Nfft,1/Fe)
        n = Bandwidth/(2*Fe)
        sig1 = signal_FFT[0:round(Nfft*n)]
        sig2 = signal_FFT[Nfft-round(Nfft*n):Nfft]
        Energie[i] = (sum(np.square(sig1))+sum(np.square(sig2)))/(len(sig1)+len(sig2))
    Energie_moyenne = sum(Energie)
    if Energie_moyenne>=seuil:
        return 1
    else:
        return 0
    print("The energy is :",Energie_moyenne)


with open("signal_ecoute.raw", 'rb') as fid:
    data_array = np.fromfile(fid, np.int8)
    data_array = data_array.astype(np.float64)
    if(data_array.size % 2 ==1):
        data_array = np.append(data_array,0)

seuil = 500000000
En = energie(data_array,1000000, seuil)
print(En)
#sys.exit(0)
