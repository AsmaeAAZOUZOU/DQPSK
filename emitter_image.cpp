#include "BitGenerator.hpp"
#include "QPSK_mod.hpp"
#include "EncoderDiff.hpp"
#include "UpSampling.hpp"
#include "Filter.hpp"
#include "Insertion_preambule.hpp"
#include "Recording_sequence.hpp"
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>

int main(){

    clock_t tStart = clock();
    int32_t nb = 2 ;                                //Nombre de bits par symbole
    int32_t M = pow(2, nb);                         //Nombre de symboles de la constellation 
    int32_t Fse = 6;                               //Facteur de sous-echantillonnage
    int32_t Nb_paquets = 64;                         //Nombre de paquets à considérer dans le signal
    complex<double> QPSK_00(sqrt(2)/2, sqrt(2)/2);
    complex<double> QPSK_01(-sqrt(2)/2, sqrt(2)/2);
    complex<double> QPSK_11(-sqrt(2)/2, -sqrt(2)/2);
    complex<double> QPSK_10(sqrt(2)/2, -sqrt(2)/2);
    int32_t len_pream = 142;                        //longueur de préambule
    int32_t len_filter = 49;
    
    
 

    //////////////////////////////////////Bit Generator////////////////////////////////////////////////

    BitGenerator* b = new BitGenerator();
    b->execute(getenv("IMAGE"));
    //b->execute("background600_400.jpg");
    

    int32_t length_signal = (b->vec).size();
    //cout << "nombre de bits émis " << length_signal << endl;
    int32_t length_paquet = length_signal/Nb_paquets;
    int32_t length_after_upsampling = (((length_signal+Nb_paquets*8)/2/Nb_paquets)+3)*Fse;
    vector<double> vect_sl;

    QPSK_mod* q = new QPSK_mod(QPSK_00,QPSK_01, QPSK_11, QPSK_10);
    EncoderDiff* en = new EncoderDiff(QPSK_00,QPSK_00);
    UpSampling* up = new UpSampling(Fse);
    Filter* f = new Filter(length_after_upsampling, M, Fse);
    f->kernel_many = (float32x4_t*)(alloca(16 * len_filter));
    int i;
	for (i = 0; i < len_filter; i++) {
		f->kernel_many[i] = vdupq_n_f32((f->filter)[i]); // broadcast
	}
    Insertion_preambule* In = new Insertion_preambule(len_pream,length_after_upsampling +len_filter-1);        
    In->insert_preambule("/home/pi/Desktop/Stage_asma/preambule.txt");
     
    
    for (int32_t j = 1; j <= length_signal/length_paquet; j++){

        cout << j << endl;  
        vector<uint8_t> vect{(b->vec).begin()+(j-1)*length_paquet, (b->vec).begin() +length_paquet+(j-1)*length_paquet};
        vector<uint8_t> vect_check{1, 0, 1, 0, 1, 0, 1, 0};         //Octet de vérification '0xAA'
        vect_check.insert(vect_check.end(), vect.begin(), vect.end());
        
        //////////////////////////////////////QPSK mod////////////////////////////////////////////////
        q->execute(vect_check);
        //////////////////////////////////////EncoderDiff/////////////////////////////////////////////     
	     en->execute(q->obuffer);
        //////////////////////////////////////UpSamling///////////////////////////////////////////////
	    up->execute((en->SSD));
        //////////////////////////////////////Filter////////////////////////////////////////////////
        //tStart = clock();
	    f->execute(up->obuffer);
        //printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        //////////////////////////////////////Insertion_preambule////////////////////////////////////////////////      
        In->insert_conv(f->obuffer_real, f->obuffer_imag, f->lenY_conv);  
        //tStart = clock();
        vect_sl.insert(vect_sl.end(), In->obuffer.begin(), In->obuffer.end());
        //printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        free(f->obuffer_real);
        free(f->obuffer_imag);  
        Recording_sequence* Rec = new Recording_sequence(In->obuffer);
        Rec->execute(In->obuffer);

    } 
       
    system("hackrf_transfer -t DQPSK_Tx.raw -f 1278000000 -s 3000000 -x 47 -p 1 -a 1 -d 000000000000000075b068dc317bae07");
    //system("hackrf_transfer -t ./DQPSK_Tx.raw -f 1255000000 -s 3000000 -x 47 -p 1 -a 1 -d 000000000000000075b068dc317bae07");
    remove("DQPSK_Tx.raw");

}
