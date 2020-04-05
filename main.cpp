#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sstream>
#include <bitset>
#include <string.h>
#include <iostream>
#include <stdlib.h>

#include "speed_up.h"
#include "reverse.h"
#include "echo.h"
#include "modulation.h"
#include "phase_shifter.h"
#include "random_LSB.h"
#include "random_MSB.h"
#include "flanging.h"



int main()
{
    double Fs = 44100;

    //  // for 8 digits
    // speed_up("europa_8.raw");
    // modulation("europa_8.raw", Fs, 5);
    // random_MSB("europa_8.raw", 1);
    // random_LSB("europa_8.raw", 3);
    // reverse("europa_8.raw");
    // phase_shifter("europa_8.raw", -1, 1000);
    // echo("europa_8.raw", Fs, 2, 0.5);
    // flanging("europa_8.raw", Fs, 0.80, 90);


    // // for 16 digits
    // speed_up_16("smokeotw_16le.raw");
    // modulation_16("smokeotw_16le.raw", Fs, 10);

    //  ne marche pas
    random_MSB_16("smokeotw_16le.raw", 2);

}


