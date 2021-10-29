#include "BitGenerator.hpp"
#include <bitset>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

BitGenerator::BitGenerator()
{
}


BitGenerator::~BitGenerator()
{
}





void BitGenerator:: toBinary(uint8_t n){    

  for (int i = 7; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            vec.push_back(1);
        else
            vec.push_back(0);
    }

}

void BitGenerator::execute(string filename)
{
   Mat img;
   img=imread(filename, IMREAD_COLOR);
   cout << img.cols << endl;
   cout << img.rows << endl;
   Mat img_t; 
   transpose(img,img_t);
   uchar* pr = img_t.ptr<uchar>(0);

    for( int i =0; i < img.cols*img.rows; i++)
        {
            toBinary(pr[3*i+2]);     //r     
            toBinary(pr[3*i+1]);     //g
            toBinary(pr[3*i]);       //b
        }

}

