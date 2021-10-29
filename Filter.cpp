#include "Filter.hpp"
#include <time.h>
//#include<immintrin.h>



Filter::Filter(int32_t _n, int32_t _M, int32_t _Fse)
{
    n = _n;
    M = _M;
    Fse = _Fse;
    filter = fichier_to_table("filter49.txt", M, Fse); 

}


Filter::~Filter()
{	
}

//save the filter coefficients in a table of floats
float* Filter::fichier_to_table(string filename,int32_t M,int32_t Fse){
    string line;
    string mot;
    int32_t n_filter =2*M*Fse+1 ;
    (*(&lenY_f)) = n_filter ;
    float *y = (float*) calloc(n_filter, sizeof(float));
    int32_t i = 0;
    ifstream infile;
    infile.open(filename);     
    while(!infile.eof()){
        getline(infile,line);  //takes a line of the file
        

        istringstream iss(line);
        while (getline( iss, mot, ',' ) ){

          
          y[i++] = stod(mot);
          
        }
    }
    infile.close();
    return y;
}

//extract the real and imaginary parts of a table
void Filter:: comp_to_real(vector<complex<double> > &comp){

  int n = comp.size();
  reelle = (float*) calloc(n, sizeof(float));
  imaginaire = (float*) calloc(n, sizeof(float));
  for (int i = 0; i< n;i++){
    reelle[i] = real(comp[i]);
    imaginaire[i] = imag(comp[i]);

  }

}

//convolution of the filter with the signal
float* Filter:: convolve(float* in, int input_length, int kernel_length){

   int nconv = input_length+kernel_length-1;
  (*(&lenY_conv)) = nconv;
  float *out = (float*) calloc(nconv, sizeof(float));

 float* in_padded = (float*)(alloca(sizeof(float) * (input_length + 8)));

	
	float32x4_t block;

	float32x4_t prod;
	float32x4_t acc;

	// surrounding zeroes, before and after
	vst1q_f32(in_padded, vdupq_n_f32(0));
	memcpy(&in_padded[4], in, sizeof(float) * input_length);
	vst1q_f32(in_padded + input_length + 4, vdupq_n_f32(0));

	// Repeat each kernal value across a 4-vector
	
	int i;
	for (i = 0 ; i < kernel_length - 3 ; i += 4) {

		// Zero the accumulator
		acc = vdupq_n_f32(0);

		int startk = 0;
		int endk = (i + 3);

		/* After this loop, we have computed 4 output samples
		* for the price of one.
		* */
		for (int k = startk; k <= endk; k++) {

			// Load 4-float data block. These needs to be an unaliged
			// load (_mm_loadu_ps) as we step one sample at a time.
			block = vld1q_f32(in_padded + 4 + i - k);
			prod = vmulq_f32(block, kernel_many[k]);

			// Accumulate the 4 parallel values
			acc = vaddq_f32(acc, prod);
		}
		vst1q_f32(out + i, acc);
	}
	for (i=kernel_length - 3; i < input_length ; i += 4) {

		// Zero the accumulator
		acc = vdupq_n_f32(0);

		int startk =  0;
		int endk = kernel_length - 1;

		/* After this loop, we have computed 4 output samples
		* for the price of one.
		* */
		for (int k = startk; k <= endk; k++) {

			// Load 4-float data block. These needs to be an unaliged
			// load (_mm_loadu_ps) as we step one sample at a time.
			block = vld1q_f32(in_padded + 4 + i - k);
			prod = vmulq_f32(block, kernel_many[k]);

			// Accumulate the 4 parallel values
			acc = vaddq_f32(acc, prod);
		}
		vst1q_f32(out + i, acc);
	}
	for (i = input_length ; i < input_length + kernel_length - 4; i += 4) {

		// Zero the accumulator
		acc = vdupq_n_f32(0);

		int startk = i - (input_length - 1);
		int endk =kernel_length - 1;

		/* After this loop, we have computed 4 output samples
		* for the price of one.
		* */
		for (int k = startk; k <= endk; k++) {

			// Load 4-float data block. These needs to be an unaliged
			// load (_mm_loadu_ps) as we step one sample at a time.
			block = vld1q_f32(in_padded + 4 + i - k);
			prod = vmulq_f32(block, kernel_many[k]);

			// Accumulate the 4 parallel values
			acc = vaddq_f32(acc, prod);
		}
		vst1q_f32(out + i, acc);
	}

	// Left-overs
	for (; i < input_length + kernel_length - 1; i++) {

		out[i] = 0.0;
		int startk = i >= input_length ? i - input_length + 1 : 0;
		int endk = i < kernel_length ? i : kernel_length - 1;
		for (int k = startk; k <= endk; k++) {
			out[i] += in[i - k] * filter[k];
		}
	}

  return out;
 
}


void Filter::execute(vector<complex<double>>& ibuffer){
  clock_t tStart = clock();
  comp_to_real(ibuffer);
  //printf("Time taken comp_to_real: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  tStart = clock();
  obuffer_real = convolve(reelle,n, lenY_f);
  //printf("Time taken convolve_reel: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  tStart = clock();
  obuffer_imag = convolve(imaginaire,n, lenY_f);
  //printf("Time taken convolve_imag: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  free(reelle);
  free(imaginaire);
  


    
}
