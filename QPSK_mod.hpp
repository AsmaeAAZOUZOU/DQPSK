#ifndef _QPSK_mod_
#define _QPSK_mod_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

class QPSK_mod{
public :

    vector<complex<double>> obuffer;
    complex<double> QPSK_00;
    complex<double> QPSK_01;
    complex<double> QPSK_11;
    complex<double> QPSK_10;

    QPSK_mod(complex<double> _QPSK_00, complex<double> _QPSK_01, complex<double> _QPSK_11, complex<double> _QPSK_10);    
	~QPSK_mod();


    void execute(vector<uint8_t>& ibuffer);

};


#endif