#ifndef _Filter_
#define _Filter_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>
#include "arm_neon.h"
#include <fstream>
#include<cstring>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

using namespace std;

class Filter{
public :

	
	int32_t n; 
	int32_t M, Fse;
	int32_t lenY_f, lenY_conv;
	float* filter;	
	float* reelle; 
	float* imaginaire; 
	float* obuffer_real ;
	float* obuffer_imag;
	float32x4_t* kernel_many;
	

	Filter(int32_t _n, int32_t _M, int32_t _Fse);
	~Filter();

	float* fichier_to_table(string filename,int32_t M,int32_t Fse);
	void comp_to_real(vector<complex<double> > &comp);
	float* convolve(float* in, int input_length, int kernel_length);
    void execute(vector<complex<double>>& ibuffer);
    
};

#endif
