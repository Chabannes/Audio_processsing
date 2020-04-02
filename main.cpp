#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <iostream>

 
void speed_up(std::string file_name);
void flapping(std::string file_name, double sampling_frequency);


int main()
{
    double Fs = 44100 ;
    // speed_up("europa.raw");
    flapping("europa.raw", Fs);

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