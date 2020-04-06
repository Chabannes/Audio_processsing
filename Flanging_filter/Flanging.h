#ifndef DEF_FLANGING
#define DEF_FLANGING

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>


class Flanging : public Filter
{
    public :

    Flanging(); 
    Flanging(std::string fileIn_name, int number_bits, double Fs, float g, int delay_max);
    ~Flanging();
    void set_fileOut_name();
    void apply();

    protected:
    double m_sampling_frequence;
    float m_g;
    int m_delay_max;
};

#endif