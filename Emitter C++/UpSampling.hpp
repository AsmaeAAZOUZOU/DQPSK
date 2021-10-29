#ifndef _UpSampling_
#define _UpSampling_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

class UpSampling{
protected :
	uint32_t scale;

public :
	vector<complex<double>> obuffer;

	UpSampling(const uint32_t mScale);

	~UpSampling();

    void execute(vector<complex<double>>& ibuffer);
};

#endif
