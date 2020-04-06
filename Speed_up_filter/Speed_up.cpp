#include "Speed_up.h"

// #include <stdio.h>
// #include <stdint.h>
// #include <math.h>
// #include <sstream>
// #include <bitset>
// #include <string.h>
// #include <iostream>
// #include <stdlib.h>

Speed_up::Speed_up() 
{}


Speed_up::Speed_up(std::string fileIn_name, int number_bits) : Filter(fileIn_name, number_bits)
{}


Speed_up::~Speed_up() 
{}


void Speed_up::set_fileOut_name()
{
    std::string s;
    s.append("Output/speed_up_");
    s.append(std::to_string(m_number_bits));
    s.append("bits");
    m_fileOut_name = s;
}


void Speed_up::apply()
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
                new_bufferOut_8[count] = new_bufferIn_8[i];
                count++;
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
                new_bufferOut_16[count] = new_bufferIn_16[i];
                count++;
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

