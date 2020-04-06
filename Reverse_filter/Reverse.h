#ifndef DEF_REVERSE
#define DEF_REVERSE

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>



class Reverse : public Filter
{
    public :

    Reverse(); 
    Reverse(std::string fileIn_name, int number_bits);
    ~Reverse();
    void set_fileOut_name();
    void apply();

    protected:
    


};

#endif