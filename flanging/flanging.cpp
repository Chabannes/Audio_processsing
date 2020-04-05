#include <math.h>
#include <sstream>
#include <string.h>
#include "flanging.h"
#include <iostream>




void flanging(std::string file_name, double Fs, float g, int delay_max)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/flanging_8", "wb");

    double m;
    int p;

    char * buffer_in;
    char * buffer_out;
    int sample_size = 1;
    float delay;


    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size; 

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    rewind (fileIn);

    buffer_in = (char*) malloc (sizeof(char)*size_in_bytes);
    buffer_out = (char*) malloc (sizeof(char)*size_in_bytes);


    fread (buffer_in, 1, size_in_samples, fileIn);


    for (int i=delay_max; i < size_in_samples ; i++)
    {
        delay = abs(delay_max*cos(i*2.0*M_PI*10./Fs));
        m = floor(delay);
        p =  delay - (int)delay;
        buffer_out[i] = (buffer_in[i] + g*((1 - p)*buffer_in[i-(int)m] + p*buffer_in[i-(int)m-1]))/2;
    }

    fwrite(buffer_out,  sizeof(char), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);   
}