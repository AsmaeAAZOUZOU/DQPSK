#ifndef _Intercorrelation_
#define _Intercorrelation_


#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <immintrin.h>

using namespace std;



class Intercorrelation {
public:

    double* preambule_fliplr;
    double norm;
    vector<double> out1;
    vector<double> out2;
    vector<double> rho;
    Intercorrelation(double _norm);
    ~Intercorrelation();

    double* read_preambule_fliplr(string filename, int len_preambule);
    vector<double> filter(vector<double> in, double* kernel, int kernel_length);
    

};


#endif 