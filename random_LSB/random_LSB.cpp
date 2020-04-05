#include <math.h>
#include <bitset>
#include <iostream>
#include "random_LSB.h"


void random_LSB(std::string file_name, int lsb_amount)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("Output/random_LSB_8", "wb");

    char * buffer;
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

    fread (buffer, 1, size_in_samples, fileIn);

    for  (int i=0; i < size_in_samples ; i++)
    {
        std::bitset<8> b(buffer[i]);

        for (int j=0; j <= lsb_amount ; j++)
        {
            b[j] = rand() % 2;
        }
        a = b.to_ulong();
        c = static_cast<unsigned char>( a ); 
        buffer[i] = c;
    }
    
    fwrite(buffer,  sizeof(char), size_in_samples, fileOut);
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}
