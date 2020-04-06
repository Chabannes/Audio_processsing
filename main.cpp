#include "Reverse_filter/Reverse.h"
#include "Speed_up_filter/Speed_up.h"
#include "Modulation_filter/Modulation.h"
#include "Phase_shifter_filter/Phase_shifter.h"
#include "Echo_filter/Echo.h"
#include "Flanging_filter/Flanging.h"
#include "Random_MSB_filter/Random_MSB.h"
#include "Random_LSB_filter/Random_LSB.h"


int main()
{
    double Fs = 44100;  // sampling frequency


    Reverse reverse_filter("data/europa_8.raw", 8);
    reverse_filter.apply();

    Speed_up speed_up_filter("data/europa_16le.raw", 16);
    speed_up_filter.apply();
    
    Modulation modulation_filter("data/europa_8.raw", 8, Fs, 5);
    modulation_filter.apply();

    Phase_shifter phase_shifter_filter("data/europa_16le.raw", 16, -0.95, 500);
    phase_shifter_filter.apply();

    Echo echo_filter("data/europa_8.raw", 8, Fs, 0.5, 2);
    echo_filter.apply();

    Flanging flanging_filter("data/europa_16le.raw", 16, Fs, 0.80, 90);
    flanging_filter.apply();

    Random_MSB random_msb_filter("data/europa_8.raw", 8, 1);
    random_msb_filter.apply();

    Random_LSB random_lsb_filter("data/europa_8.raw", 8, 2);
    random_lsb_filter.apply();

}


