#include "Insertion_preambule.hpp"


Insertion_preambule :: Insertion_preambule(int32_t _len_pream, int32_t _len_ibuffers)
{
    len_preambule = 2*_len_pream ;
    len_ibuffers  = 2*_len_ibuffers;
    len_obuffer = len_preambule + len_ibuffers;

}


Insertion_preambule::~Insertion_preambule()
{	
}

//the function : max(abs) of a complex table (A real part, B imaginary part)
float Insertion_preambule:: max_absolue(float* A, float* B, int32_t l){

    float _max = 0;
    for(int32_t i=0; i<l; i++){
    _max = (_max>((A[i]*A[i]+B[i]*B[i]))?_max:((A[i]*A[i]+B[i]*B[i])));
    }
    return sqrt(_max);
}


//save the complex coefficients of the preamble in a table of real coefficients
void Insertion_preambule:: insert_preambule(string filename){
    obuffer.resize(len_obuffer);
    string line;
    string mot;
    int32_t i = 0;
    ifstream infile;
    infile.open(filename);     
    while(!infile.eof()){
        getline(infile,line);  //takes a line of the file
        istringstream iss(line);
        while (getline( iss, mot, ',' ) ){

          
          obuffer[2*i]=100*stod(mot);
          obuffer[2*i+1]=0;
          i++;
          
        }
    }
    infile.close();

}

void Insertion_preambule:: insert_conv(float* tab_real, float* tab_imag, int32_t length_tab){
    float coeff = (127/max_absolue(tab_real, tab_imag, length_tab));
   //cout << "coeff " << coeff << endl;
    for (int32_t i = len_preambule/2; i < (len_preambule+len_ibuffers)/2; i++){
        obuffer[2*i] = (double) (coeff*tab_real[i-len_preambule/2]);
        obuffer[2*i+1] = (double) (coeff*tab_imag[i-len_preambule/2]);
    }

}


