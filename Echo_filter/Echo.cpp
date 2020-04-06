#include "Echo.h"


#include <math.h>
#include <iostream>
#include <stdlib.h>

Echo::Echo() 
{}


Echo::Echo(std::string fileIn_name, int number_bits, double Fs, float echo_fading, float echo_dt) : Filter(fileIn_name, number_bits), m_sampling_frequence(Fs), m_echo_fading(echo_fading), m_echo_dt(echo_dt)
{}


Echo::~Echo() 
{}


void Echo::set_fileOut_name()
{
    std::string s;
    s.append("Output/echo_");
    s.append(std::to_string(m_number_bits));
    s.append("bits");
    m_fileOut_name = s;
}


void Echo::apply()
{
    if ((m_echo_fading < -1 )|(m_echo_fading > 1)) {fputs ("error in echo fading value", stderr); exit (1);}
    if (m_echo_dt <=0) {fputs ("error in echo time value", stderr); exit (1);}

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
    int window = m_sampling_frequence*m_echo_dt;

    rewind (m_fileIn);

    switch (m_sample_size)
    {
    case 1:
        new_bufferIn_8 = (char*) (m_bufferIn);
        new_bufferOut_8 = (char*) (m_bufferOut);

        fread (new_bufferIn_8, m_sample_size, m_size_in_samples, m_fileIn);

        for (int i=0; i < m_size_in_samples ; i++)
        {
        if (i < window)
            {
                new_bufferOut_8[i] = new_bufferIn_8[i];
            }
        if ((i < 2*window)&(i > window))
            {
                new_bufferOut_8[i] = (new_bufferIn_8[i] + m_echo_fading*new_bufferIn_8[i-window])/2;
            }
        if (i >= 2*window)
            {
                new_bufferOut_8[i] = (new_bufferIn_8[i] + m_echo_fading*new_bufferIn_8[i-window] + m_echo_fading/2*new_bufferIn_8[i-window*2])/3;
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
        if (i < window)
            {
                new_bufferOut_16[i] = new_bufferIn_16[i];
            }
        if ((i < 2*window)&(i > window))
            {
                new_bufferOut_16[i] = (new_bufferIn_16[i] + m_echo_fading*new_bufferIn_16[i-window])/2;
            }
        if (i >= 2*window)
            {
                new_bufferOut_16[i] = (new_bufferIn_16[i] + m_echo_fading*new_bufferIn_16[i-window] + m_echo_fading/2*new_bufferIn_16[i-window*2])/3;
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

