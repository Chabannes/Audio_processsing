#ifndef DEF_SPEED_UP
#define DEF_SPEED_UP

#include "/home/francois/Documents/C++/AudioProcessing/Filter/Filter.h"

#include <string>



class Speed_up : public Filter
{
    public :

    Speed_up(); 
    Speed_up(std::string fileIn_name, int number_bits);
    ~Speed_up();
    void set_fileOut_name();
    void apply();

    protected:
    


};

#endif