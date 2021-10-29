#ifndef _BitGenerator_
#define _BitGenerator_

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <algorithm>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


using namespace std;

class BitGenerator{
public:
    vector<uint8_t> vec;
    BitGenerator();
    ~BitGenerator();

    void toBinary(uint8_t n);
    void execute(string filename);


};


#endif 
