#ifndef _Read_data_
#define _Read_data_

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

class Read_data {
public:
    vector <double> tab_double;
    vector<double> abs_tab_double;
    vector<double> abs_tab_double_carre;
    vector<double> tab_reel;
    vector<double> tab_imag;
    double norm;
    Read_data();
    ~Read_data();

    void read_file(string filename);


};


#endif 
