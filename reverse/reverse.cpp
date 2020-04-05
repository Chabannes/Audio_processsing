#include <math.h>
#include <iostream>
#include "reverse.h"



void reverse(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/reverse_8", "wb");

    char * buffer;
    char * buffer_reverse;

    int sample_size = 1;

    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size; 

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*size_in_bytes);
    buffer_reverse = (char*) malloc (sizeof(char)*size_in_bytes);

    fread (buffer, 1, size_in_samples, fileIn);

    for (int i=0; i < size_in_samples ; i++)
    {
        buffer_reverse[size_in_samples-i] = buffer[i];
    }

    fwrite(buffer_reverse,  sizeof(char), size_in_samples, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
    free (buffer_reverse);
}
