#include "Read_data.hpp"
#include <numeric>


Read_data::Read_data()
{
}


Read_data::~Read_data()
{
}


void Read_data::read_file(string filename)
{
    FILE* pFile;
    int32_t i=0;
    int8_t c;
    pFile = fopen (filename.c_str(), "rb");   
    while(!feof(pFile))
        {
            fread(&c,sizeof(int8_t),1,pFile);
            tab_double.push_back(double(c));

    }
    //cout << tab_double.size() << endl;
    fclose(pFile);
    tab_reel.resize((tab_double.size()-1)/2);
    tab_imag.resize((tab_double.size()-1)/2);
    abs_tab_double.resize((tab_double.size()-1)/2);
    norm =0;
    while(i<=round((tab_double.size()-3)/2)){
        tab_reel[i] = tab_double[2*i];
        tab_imag[i] =tab_double[2*i+1];
        double elem = tab_double[2*i]*tab_double[2*i]+tab_double[2*i+1]*tab_double[2*i+1];
        abs_tab_double[i] = sqrt(elem);
        abs_tab_double_carre[i] = elem;
        norm = norm+elem;
        i++;
        
    }
    norm = sqrt(norm);
    //cout << norm << endl;




}



    









