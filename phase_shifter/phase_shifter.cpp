#include <math.h>
#include <iostream>
#include "phase_shifter.h"



void phase_shifter(std::string file_name, float g, int m)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/phase_shifter_8", "wb");

    char * buffer_in;
    char * buffer_out;
    int sample_size = 1;

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

    for (int i=m; i < size_in_samples ; i++)
    {
        buffer_out[i] = -g*buffer_in[i] + buffer_in[i-m] + g*buffer_out[i-m];
    }

    fwrite(buffer_out,  sizeof(char), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);
}