#ifndef _Recording_sequence_
#define _Recording_sequence_

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <complex>

using namespace std;

class Recording_sequence{
public :
    int32_t len_ibuffer;
    
    Recording_sequence(vector<double> _ibuffer);
    ~Recording_sequence();
    void execute(vector<double> ibuffer);

};


#endif