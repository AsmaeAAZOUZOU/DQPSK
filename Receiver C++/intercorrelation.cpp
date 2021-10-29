#include "intercorrelation.hpp"
#include <numeric>
#include <cstring>
#include <fstream>
#include <sstream> 

using namespace std;

Intercorrelation::Intercorrelation(double _norm)
{
	preambule_fliplr = read_preambule_fliplr("preambule_fliplr.txt",478);
	norm = _norm;
}


Intercorrelation::~Intercorrelation()
{
}



double* Intercorrelation::read_preambule_fliplr(string filename, int len_preambule){

    double* y = (double*) malloc(sizeof(double)*len_preambule);
    string line;
    string mot;
    int32_t i = 0;
    ifstream infile;
    infile.open(filename);     
    while(!infile.eof()){
        getline(infile,line);  //takes a line of the file
        istringstream iss(line);
        while (getline( iss, mot, ',' ) ){

          //cout << mot << endl;
          preambule_fliplr[i++]=stod(mot);
          
          
          
        }
    }
    infile.close();
	return y;

}


vector<double> Intercorrelation::filter(vector<double> in, double* kernel, int kernel_length){

    rho.resize(in.size());
	int i =	0;
	for (int i = 0; i < in.size(); i++) {

		rho[i] = 0.0;
		int startk =0;
		int endk = i < kernel_length ? i : kernel_length - 1;
		for (int k = startk; k <= endk; k++) {
			rho[i] += in[i - k] * kernel[k]/norm;
		}
	}
	cout << in.size()<< endl;
    cout << "done" << endl;

	return rho;
}


