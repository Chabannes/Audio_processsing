#ifndef DEF_RANDOM_MSB
#define DEF_RANDOM_MSB

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>


class Random_MSB : public Filter
{
    public :

    Random_MSB(); 
    Random_MSB(std::string fileIn_name, int number_bits, int msb_amount);
    ~Random_MSB();
    void set_fileOut_name();
    void apply();

    protected:
    int m_msb_amount;
};

#endif