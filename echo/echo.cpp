#include <math.h>
#include <iostream>
#include "echo.h"



void echo(std::string file_name, double Fs, float echo_dt, float echo_fading)
{
    if ((echo_fading < -1 )|(echo_fading > 1)) {fputs ("error in echo fading value", stderr); exit (1);}
    if (echo_dt <=0) {fputs ("error in echo time value", stderr); exit (1);}


    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/echo_8", "wb");

    char * buffer_in;
    char * buffer_out;
    int sample_size = 1;
    int window = Fs*echo_dt;

    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size; 

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    rewind (fileIn);

    buffer_in = (char*) malloc (sizeof(char)*size_in_bytes);
    buffer_out = (char*) malloc (sizeof(char)*size_in_bytes);

    fread (buffer_in, 1, size_in_samples, fileIn);

    for (int i=0; i < size_in_samples; i++)
    {
        if (i < window)
        {
            buffer_out[i] = buffer_in[i];
        }
        if ((i < 2*window)&(i > window))
        {
            buffer_out[i] = (buffer_in[i] + echo_fading*buffer_in[i-window])/2;
        }
        if (i >= 2*window)
        {
            buffer_out[i] = (buffer_in[i] + echo_fading*buffer_in[i-window] + echo_fading/2*buffer_in[i-window*2])/3;
        }
    }

    fwrite(buffer_out,  sizeof(char), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);
}

