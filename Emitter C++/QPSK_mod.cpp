  
#include "QPSK_mod.hpp"

QPSK_mod::QPSK_mod(complex<double> _QPSK_00, complex<double> _QPSK_01, complex<double> _QPSK_11, complex<double> _QPSK_10)
{
    QPSK_00 = _QPSK_00;
    QPSK_01 = _QPSK_01;
    QPSK_11 = _QPSK_11;
    QPSK_10 = _QPSK_10;
}


QPSK_mod::~QPSK_mod()
{	
}


void QPSK_mod::execute(vector<uint8_t>& ibuffer)
{
    obuffer.resize(ibuffer.size()/2);
    const uint32_t ll = obuffer.size();

    for(uint32_t i = 0 ; i < ll; i += 1)
    {
        if (ibuffer[2*i] == 0 && ibuffer[2*i+ 1] == 0){  obuffer[i] = QPSK_00;}
        else if (ibuffer[2*i] == 0 && ibuffer[2*i + 1] == 1){  obuffer[i] = QPSK_01; }
        else if (ibuffer[2*i] == 1 && ibuffer[2*i + 1] == 1){ obuffer[i] = QPSK_11;; }
        else if  (ibuffer[2*i] == 1 && ibuffer[2*i + 1] == 0){  obuffer[i] = QPSK_10;; } 
        
    }


  

}
