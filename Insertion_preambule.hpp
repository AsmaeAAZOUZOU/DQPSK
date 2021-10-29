#ifndef _Insertion_preambule_
#define _Insertion_preambule_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>
#include <fstream>

using namespace std;

class Insertion_preambule{
public :

	
	int32_t len_preambule; 	 
	int32_t len_ibuffers;
	int32_t len_obuffer;
	vector<double> obuffer;
	
	

	Insertion_preambule(int32_t _len_pream, int32_t _len_ibuffers);
	~Insertion_preambule();

	void insert_preambule(string filename);
	float max_absolue(float* A, float* B, int32_t l);
	void insert_conv(float* tab_real, float* tab_imag, int32_t length_tab);
	
    
};

#endif