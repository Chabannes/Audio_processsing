#include <math.h>
#include <iostream>
#include "modulation.h"




void modulation(std::string file_name, double Fs, float f)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    char * buffer;
    int sample_size = 1;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size; 
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*size_in_bytes);

    fread (buffer, 1, size_in_samples, fileIn);

    int count = 0;
    for (int i=0; i < size_in_samples ; i++)
    {
        if (i%2 == 0)
        {
            buffer[i] = buffer[i] * sin(i*f*2.0*M_PI/Fs);
        }
    }

    fwrite(buffer,  sizeof(char), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}


void modulation_16(std::string file_name, double Fs, float f)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    int sample_size = 2;
    int16_t * buffer;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size;
    rewind (fileIn);

    buffer = (int16_t*) malloc (sizeof(char)*size_in_bytes);

    fread (buffer, sizeof(int16_t), size_in_samples, fileIn);

    int count = 0;
    for (int i=0; i < size_in_samples ; i++)
    {
        if (i%2 == 0)
        {
            buffer[i] = buffer[i] * sin(i*f*2.0*M_PI/Fs);
        }
    }
 
    fwrite(buffer,  sizeof(int16_t), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}