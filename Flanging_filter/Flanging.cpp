#include "Flanging.h"


#include <math.h>
#include <iostream>
#include <stdlib.h>

Flanging::Flanging() 
{}


Flanging::Flanging(std::string fileIn_name, int number_bits, double Fs, float g, int delay_max) : Filter(fileIn_name, number_bits), m_sampling_frequence(Fs), m_g(g), m_delay_max(delay_max)
{}

Flanging::~Flanging() 
{}


void Flanging::set_fileOut_name()
{
    std::string s;
    s.append("Output/flanging_");
    s.append(std::to_string(m_number_bits));
    s.append("bits");
    m_fileOut_name = s;
}


void Flanging::apply()
{
    if (m_delay_max <0) {fputs ("delay_max value", stderr); exit (1);}

    set_fileOut_name();
    open_fileIn();
    open_fileOut();
    set_sample_size();
    set_size_in_bytes();
    set_size_in_samples();
    set_fileOut_name();

    m_bufferIn = (char*) malloc(sizeof(char)*m_size_in_bytes);
    m_bufferOut = (char*) malloc(sizeof(char)*m_size_in_bytes);
    char* new_bufferIn_8;
    char* new_bufferOut_8;
    int16_t* new_bufferIn_16;
    int16_t* new_bufferOut_16;

    rewind (m_fileIn);
    float delay;
    int p;
    double m;

    switch (m_sample_size)
    {
    case 1:
        new_bufferIn_8 = (char*) (m_bufferIn);
        new_bufferOut_8 = (char*) (m_bufferOut);

        fread (new_bufferIn_8, m_sample_size, m_size_in_samples, m_fileIn);

        for (int i=m_delay_max; i < m_size_in_samples ; i++)
        {
            delay = abs(m_delay_max*cos(i*2.0*M_PI*10./m_sampling_frequence));
            m = floor(delay);
            p =  delay - (int)delay;
            new_bufferOut_8[i] = (new_bufferIn_8[i] + m_g*((1 - p)*new_bufferIn_8[i-(int)m] + p*new_bufferIn_8[i-(int)m-1]))/2;
        } 

        fwrite(new_bufferOut_8,  sizeof(char), m_size_in_samples, m_fileOut);

        break;

    case 2:
        new_bufferIn_16 = (int16_t*) (m_bufferIn);
        new_bufferOut_16 = (int16_t*) (m_bufferOut);

        fread (new_bufferIn_16, m_sample_size, m_size_in_samples, m_fileIn);

        for (int i=m_delay_max; i < m_size_in_samples ; i++)
        {
            delay = abs(m_delay_max*cos(i*2.0*M_PI*10./m_sampling_frequence));
            m = floor(delay);
            p =  delay - (int)delay;
            new_bufferOut_16[i] = (new_bufferIn_16[i] + m_g*((1 - p)*new_bufferIn_16[i-(int)m] + p*new_bufferIn_16[i-(int)m-1]))/2;
        } 

        fwrite(new_bufferOut_16,  sizeof(int16_t), m_size_in_samples, m_fileOut);

        break;

    default:
        fputs ("number of bits must be 8 or 16", stderr); exit (1);
    }

    fclose (m_fileIn);
    fclose (m_fileOut);
    free (m_bufferIn);
    free (m_bufferOut);
}

