#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sstream>
#include <bitset>
#include <iostream>

 
void speed_up(std::string file_name);
void flapping(std::string file_name, double sampling_frequency);
void random_MSB(std::string file_name, int msb_amount);
void random_LSB(std::string file_name, int lsb_amount);



int main()
{
    double Fs = 44100 ;std::string file_name;
    // speed_up("europa.raw");
    // flapping("europa.raw", Fs);
    // random_MSB("europa.raw", 1);
    random_LSB("europa.raw", 3);



}


void speed_up(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;
    char * buffer_fast;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*lSize);
    buffer_fast = (char*) malloc (sizeof(char)*lSize/2);

    fread (buffer, 1, lSize, fileIn);

    int count = 0;
    for (int i=0; i < sizeof(char)*lSize ; i++)
    {
        if (i%2 == 0)
        {
            buffer_fast[count] = buffer[i];
            count++;
        }
    }

    fwrite(buffer_fast,  sizeof(char), lSize/2, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
    free (buffer_fast);
}

void flapping(std::string file_name, double Fs)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*lSize);

    fread (buffer, 1, lSize, fileIn);

    int count = 0;
    for (int i=0; i < sizeof(char)*lSize ; i++)
    {
        if (i%2 == 0)
        {
            buffer[i] = buffer[i] * (0.2 + sin(i*2.0*M_PI/Fs)) ;
        }
    }

    fwrite(buffer,  sizeof(char), lSize, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}


void random_MSB(std::string file_name, int msb_amount)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;
    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*lSize);

    fread (buffer, 1, lSize, fileIn);

    for  (int i=0; i < sizeof(char)*lSize ; i++)
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
    
    fwrite(buffer,  sizeof(char), lSize, fileOut);
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}



void random_LSB(std::string file_name, int lsb_amount)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;
    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*lSize);

    fread (buffer, 1, lSize, fileIn);

    for  (int i=0; i < sizeof(char)*lSize ; i++)
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
    
    fwrite(buffer,  sizeof(char), lSize, fileOut);
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}
