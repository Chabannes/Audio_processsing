#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sstream>
#include <bitset>
#include <string.h>
#include "speed_up.h"
#include <iostream>
#include <stdlib.h>



void speed_up(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/speed_up_8", "wb");

    long lSize;
    char * buffer;
    char * buffer_fast;
    int sample_size = 1;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size;    
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*size_in_bytes);
    buffer_fast = (char*) malloc (sizeof(char)*size_in_bytes/2);

    fread (buffer, 1, size_in_samples, fileIn);

    int count = 0;

    for (int i=0; i < size_in_samples ; i++)
    {
        if (i%2 == 0)
        {
            buffer_fast[count] = buffer[i];
            count++;
        }
    }

    fwrite(buffer_fast,  sizeof(char), size_in_samples/2, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
    free (buffer_fast);
}


void speed_up_16(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/speed_up_16", "wb");

    int sample_size = 2;
    int16_t * buffer;
    int16_t * buffer_fast;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size;
    rewind (fileIn);

    buffer = (int16_t*) malloc (sizeof(char)*size_in_bytes);
    buffer_fast = (int16_t*) malloc (sizeof(char)*size_in_bytes/2);

    fread (buffer, sizeof(int16_t), size_in_samples, fileIn);

    int count = 0;
    for (int i=0; i < size_in_samples ; i++)
    {
        if (i%2 == 0)
        {
            buffer_fast[count] = buffer[i];
            count++;
        }
    }

    fwrite(buffer_fast,  sizeof(int16_t), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}