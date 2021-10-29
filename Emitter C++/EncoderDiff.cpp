#include "EncoderDiff.hpp"



EncoderDiff::EncoderDiff(complex<double> _S_phase, complex<double> _SSD_1)
{
    S_phase = _S_phase;
    SSD.push_back(_SSD_1);


}



EncoderDiff::EncoderDiff()
{
}


EncoderDiff::~EncoderDiff()
{	
}

void EncoderDiff::execute(vector<complex<double>>& ibuffer){


    SSD.resize(ibuffer.size()+2);
    
    
    const uint32_t l = ibuffer.size();
    for(uint32_t i = 0 ; i < l; i += 1){
        SSD[i+1] = ibuffer[i]*SSD[i];        
    }   

    SSD.insert(SSD.begin(),S_phase);


}
