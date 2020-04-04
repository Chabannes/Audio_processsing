#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sstream>
#include <bitset>
#include <string.h>
#include <iostream>
#include <stdlib.h>

 
void speed_up(std::string file_name);
void speed_up_16(std::string file_name);
void modulation(std::string file_name, double sampling_frequency, float f);
void modulation_16(std::string file_name, double sampling_frequency, float f);
void random_MSB(std::string file_name, int msb_amount);
void random_LSB(std::string file_name, int lsb_amount);
void reverse(std::string file_name);
void phase_shifter(std::string file_name, float g, int m);
void echo(std::string file_name, double sampling_frequency, float echo_dt, float echo_fading);
void flanging(std::string file_name, double Fs, float g, int delay_max);
void random_MSB_16(std::string file_name, int msb_amount);



int main()
{
    double Fs = 44100;

    //  // for 8 digits
    // speed_up("europa_8.raw");
    // modulation("europa_8.raw", Fs, 5);
    // random_MSB("europa_8.raw", 1);
    // random_LSB("europa_8.raw", 3);
    // reverse("europa_8.raw");
    // phase_shifter("europa_8.raw", -1, 1000);
    // echo("europa_8.raw", Fs, 2, 0.7);
    // flanging("europa_8.raw", Fs, 0.80, 90);


    // // for 16 digits
    // speed_up_16("smokeotw_16.raw");
    // modulation_16("smokeotw_16.raw", Fs, 10);

    //  ne marche pas
    random_MSB_16("smokeotw_16.raw", 2);

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

    int count = 0;void modulation_16(std::string file_name, double sampling_frequency, float f);

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


void modulation(std::string file_name, double Fs, float f)
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
            buffer[i] = buffer[i] * sin(i*f*2.0*M_PI/Fs);
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


void reverse(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;
    char * buffer_reverse;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer = (char*) malloc (sizeof(char)*lSize);
    buffer_reverse = (char*) malloc (sizeof(char)*lSize);

    fread (buffer, 1, lSize, fileIn);

    for (int i=0; i < sizeof(char)*lSize ; i++)
    {
        buffer_reverse[lSize-i] = buffer[i];
    }

    fwrite(buffer_reverse,  sizeof(char), lSize, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
    free (buffer_reverse);
}


void phase_shifter(std::string file_name, float g, int m)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer_in;
    char * buffer_out;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer_in = (char*) malloc (sizeof(char)*lSize);
    buffer_out = (char*) malloc (sizeof(char)*lSize);

    fread (buffer_in, 1, lSize, fileIn);

    for (int i=m; i < sizeof(char)*lSize ; i++)
    {
        buffer_out[i] = -g*buffer_in[i] + buffer_in[i-m] + g*buffer_out[i-m];
    }

    fwrite(buffer_out,  sizeof(char), lSize, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);
}


void echo(std::string file_name, double Fs, float echo_dt, float echo_fading)
{
    if ((echo_fading < -1 )|(echo_fading > 1)) {fputs ("error in echo fading value", stderr); exit (1);}
    if (echo_dt <=0) {fputs ("error in echo time value", stderr); exit (1);}


    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer_in;
    char * buffer_out;
    int window = Fs*echo_dt;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer_in = (char*) malloc (sizeof(char)*lSize);
    buffer_out = (char*) malloc (sizeof(char)*lSize);

    fread (buffer_in, 1, lSize, fileIn);

    for (int i=0; i < sizeof(char)*lSize ; i++)
    {
        if (i < 2*window)
        {
            buffer_out[i] = buffer_in[i];
        }
        else
        {
            buffer_out[i] = (buffer_in[i] + echo_fading*buffer_in[i-window] + echo_fading/2*buffer_in[i-window*2])/3;
        }
    }

    fwrite(buffer_out,  sizeof(char), lSize, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);
}


void flanging(std::string file_name, double Fs, float g, int delay_max)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer_in;
    char * buffer_out;
    double * delay;
    double m;
    int p;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    buffer_in = (char*) malloc (sizeof(char)*lSize);
    buffer_out = (char*) malloc (sizeof(char)*lSize);
    delay = (double*) malloc (sizeof(double)*lSize);


    fread (buffer_in, 1, lSize, fileIn);

    for (int i=delay_max; i < sizeof(char)*lSize ; i++)
    {
        delay[i] = abs(delay_max*cos(i*2.0*M_PI*10./Fs));
        m = floor(delay[i]);
        p =  delay[i] - (int)delay[i];
        buffer_out[i] = (buffer_in[i] + g*((1 - p)*buffer_in[i-(int)m] + p*buffer_in[i-(int)m-1]))/5;
    }

    fwrite(buffer_out,  sizeof(char), lSize, fileOut);

    fclose (fileIn);
    fclose (fileOut);
    free (buffer_in);
    free (buffer_out);   
}


void speed_up_16(std::string file_name)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

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


void random_MSB_16(std::string file_name, int msb_amount)
{
    FILE* fileIn = fopen(file_name.c_str(), "rb");
    FILE* fileOut = fopen("output", "wb");

    int16_t * buffer;
    int sample_size = 2;
    unsigned long a;
    unsigned char c;

    if (fileIn==NULL) {fputs ("File error", stderr); exit (1);}

    fseek (fileIn , 0 , SEEK_END);
    int size_in_bytes = ftell (fileIn);
    int size_in_samples = size_in_bytes / sample_size;
    rewind (fileIn);

    buffer = (int16_t*) malloc (sizeof(char)*sample_size);

    fread (buffer, 2, sample_size, fileIn);

    for  (int i=0; i < sample_size ; i++)
    {
        std::bitset<16> b(buffer[i]);

        for (int j=0; j <= msb_amount ; j++)
        {
            b[16-j] = rand() % 2;
        }

        a = b.to_ulong();
        c = static_cast<unsigned char>( a ); 
        buffer[i] = c;
    }
    
    fwrite(buffer,  2, sample_size, fileOut);
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);
}
