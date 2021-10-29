#include "UpSampling.hpp"


UpSampling::UpSampling(const uint32_t mScale)
{
    scale = mScale;
}


UpSampling::~UpSampling()
{
	
}

void UpSampling::execute(vector<complex<double>>& ibuffer)
{
    obuffer.resize(scale * ibuffer.size());
    const uint32_t ll = ibuffer.size();
    for(uint32_t i = 0 ; i < ll; i += 1)
    {
        const complex<double> value = ibuffer[i];
        const complex<double> zero_00(0, 0);
        obuffer[scale * i ] =  value;

        
        for(uint32_t j = 1 ; j < scale ; j += 1)
        {
            obuffer[scale * i + j] = zero_00;
            
        }
    }
}
   
