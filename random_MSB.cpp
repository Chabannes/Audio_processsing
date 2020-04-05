#include <math.h>
#include <bitset>
#include <iostream>
#include "random_MSB.h"




void random_MSB(std::string file_name, int msb_amount)
{


    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

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

        for (int j=0; j <= msb_amount ; j++)
        {
            b[8-j] = rand() % 2;
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


void random_MSB_16(std::string file_name, int msb_amount)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    int16_t* buffer;
    int sample_size = 2;

    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size; 

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    rewind (fileIn);

    buffer = (int16_t*) malloc (sizeof(char)*size_in_bytes);

    fread (buffer, 2, size_in_samples, fileIn);

    for  (int i=0; i < size_in_samples ; i++)
    {
        std::bitset<8> b(buffer[i]);

        for (int j=0; j <= msb_amount ; j++)
        {
            b[8-j] = rand() % 2;
        }

        a = b.to_ulong();
        c = static_cast<unsigned char>( a ); 
        buffer[i] = c;
    }
    
    fwrite(buffer,  sizeof(int16_t), size_in_samples, fileOut);
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}
