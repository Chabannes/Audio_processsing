#ifndef DEF_ECHO
#define DEF_ECHO

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>


class Echo : public Filter
{
    public :

    Echo(); 
    Echo(std::string fileIn_name, int number_bits, double Fs, float echo_fading, float echo_dt);
    ~Echo();
    void set_fileOut_name();
    void apply();

    protected:
    double m_sampling_frequence;
    float m_echo_fading;
    float m_echo_dt;
};

#endif