#include "Recording_sequence.hpp"


Recording_sequence::Recording_sequence(vector<double> _ibuffer)
{
    len_ibuffer = _ibuffer.size();
}

Recording_sequence::~Recording_sequence()
{	
}

void Recording_sequence::execute(vector<double> ibuffer){

    FILE * pFile;
    pFile = fopen ("DQPSK_Tx.raw", "ab");
    int8_t* tab_int8_t = (int8_t*) malloc(sizeof(int8_t)*len_ibuffer);
    for (int32_t i = 0; i < len_ibuffer; i++){
        tab_int8_t[i] = int8_t(round(ibuffer[i]));

    }
    fwrite(tab_int8_t, sizeof(int8_t), len_ibuffer, pFile);
    fclose (pFile);
    free(tab_int8_t);

}
