#include "Modulation.h"


#include <math.h>
#include <iostream>
#include <stdlib.h>

Modulation::Modulation() 
{}


Modulation::Modulation(std::string fileIn_name, int number_bits, double Fs, float f) : Filter(fileIn_name, number_bits), m_sampling_frequence(Fs), m_frequence(f)
{}


Modulation::~Modulation() 
{}


void Modulation::set_fileOut_name()
{
    std::string s;
    s.append("Output/modulation_");
    s.append(std::to_string(m_number_bits));
    s.append("bits");
    m_fileOut_name = s;
}


void Modulation::apply()
{
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
    int count = 0;

    switch (m_sample_size)
    {
    case 1:
        new_bufferIn_8 = (char*) (m_bufferIn);
        new_bufferOut_8 = (char*) (m_bufferOut);

        fread (new_bufferIn_8, m_sample_size, m_size_in_samples, m_fileIn);

        for (int i=0; i < m_size_in_samples ; i++)
        {
        if (i%2 == 0)
            {
            new_bufferOut_8[i] = new_bufferIn_8[i] * sin(i*m_frequence*2.0*M_PI/m_sampling_frequence);
            } 
        }     

        fwrite(new_bufferOut_8,  sizeof(char), m_size_in_samples, m_fileOut);

        break;

    case 2:
        new_bufferIn_16 = (int16_t*) (m_bufferIn);
        new_bufferOut_16 = (int16_t*) (m_bufferOut);

        fread (new_bufferIn_16, m_sample_size, m_size_in_samples, m_fileIn);

        for (int i=0; i < m_size_in_samples ; i++)
        {
        if (i%2 == 0)
            {
            new_bufferOut_16[i] = new_bufferIn_16[i] * sin(i*m_frequence*2.0*M_PI/m_sampling_frequence);
            } 
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

