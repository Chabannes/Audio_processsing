#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sstream>
#include <bitset>
#include <string.h>
#include <iostream>
#include <stdlib.h>

#include "speed_up/speed_up.h"
#include "reverse/reverse.h"
#include "echo/echo.h"
#include "modulation/modulation.h"
#include "phase_shifter/phase_shifter.h"
#include "random_LSB/random_LSB.h"
#include "random_MSB/random_MSB.h"
#include "flanging/flanging.h"



int main()
{
    double Fs = 44100;

    //  // for 8 digits
    speed_up("data/europa_8.raw");
    modulation("data/europa_8.raw", Fs, 5);
    random_MSB("data/europa_8.raw", 1);
    random_LSB("data/europa_8.raw", 3);
    reverse("data/europa_8.raw");
    phase_shifter("data/europa_8.raw", -1, 1000);
    echo("data/europa_8.raw", Fs, 2, 0.5);
    flanging("data/europa_8.raw", Fs, 0.80, 90);


    // // for 16 digits
    speed_up_16("data/smokeotw_16le.raw");
    modulation_16("data/smokeotw_16le.raw", Fs, 10);

    //  not working yet
    random_MSB_16("data/smokeotw_16le.raw", 2);

}


