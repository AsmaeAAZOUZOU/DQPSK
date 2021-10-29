#ifndef _EncoderDiff_
#define _EncoderDiff_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

class EncoderDiff{
public :

    complex<double> S_phase;
    vector<complex<double>> SSD;
    vector<complex<double>> obuffer;
   
    EncoderDiff(complex<double> _S_phase, complex<double> _SSD_1);
	EncoderDiff();
	~EncoderDiff();

    void execute(vector<complex<double>>& ibuffer);
};

#endif