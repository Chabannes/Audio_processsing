#ifndef DEF_RANDOM_LSB
#define DEF_RANDOM_LSB

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>


class Random_LSB : public Filter
{
    public :

    Random_LSB(); 
    Random_LSB(std::string fileIn_name, int number_bits, int lsb_amount);
    ~Random_LSB();
    void set_fileOut_name();
    void apply();

    protected:
    int m_lsb_amount;
};

#endif