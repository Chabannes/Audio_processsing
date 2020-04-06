#ifndef DEF_PHASE_SHIFTER
#define DEF_PHASE_SHIFTER

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>


class Phase_shifter : public Filter
{
    public :

    Phase_shifter(); 
    Phase_shifter(std::string fileIn_name, int number_bits, float g, int m);
    ~Phase_shifter();
    void set_fileOut_name();
    void apply();

    protected:
    float m_g;
    int m_m;
};

#endif