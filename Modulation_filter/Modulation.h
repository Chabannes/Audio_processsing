#ifndef DEF_MODULATION
#define DEF_MODULATION

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>

class Modulation : public Filter
{
    public :

    Modulation(); 
    Modulation(std::string fileIn_name, int number_bits, double Fs, float f);
    ~Modulation();
    void set_fileOut_name();
    void apply();

    protected:
    float m_frequence;
    double m_sampling_frequence;
    


};

#endif