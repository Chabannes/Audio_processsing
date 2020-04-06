#include "Random_MSB.h"


#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <bitset>


Random_MSB::Random_MSB() 
{}


Random_MSB::Random_MSB(std::string fileIn_name, int number_bits, int msb_amount) : Filter(fileIn_name, number_bits), m_msb_amount(msb_amount)
{}

Random_MSB::~Random_MSB() 
{}


void Random_MSB::set_fileOut_name()
{
    std::string s;
    s.append("Output/random_MSB_");
    s.append(std::to_string(m_number_bits));
    s.append("bits");
    m_fileOut_name = s;
}


void Random_MSB::apply()
{
    if (m_msb_amount <0) {fputs ("(msb_amount value can't be negative", stderr); exit (1);}

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
    unsigned long a;
    unsigned char c;

    switch (m_sample_size)
    {
    case 1:
        new_bufferIn_8 = (char*) (m_bufferIn);
        new_bufferOut_8 = (char*) (m_bufferOut);

        fread (new_bufferIn_8, m_sample_size, m_size_in_samples, m_fileIn);

        for  (int i=0; i < m_size_in_samples ; i++)
        {
            std::bitset<8> b(new_bufferIn_8[i]);

            for (int j=0; j <= m_msb_amount ; j++)
            {
                b[8-j] = rand() % 2;
            }

            a = b.to_ulong();
            c = static_cast<unsigned char>( a ); 
            new_bufferOut_8[i] = c;
        }

        fwrite(new_bufferOut_8,  sizeof(char), m_size_in_samples, m_fileOut);

        break;

    case 2:
        new_bufferIn_16 = (int16_t*) (m_bufferIn);
        new_bufferOut_16 = (int16_t*) (m_bufferOut);

        fread (new_bufferIn_16, m_sample_size, m_size_in_samples, m_fileIn);

        for  (int i=0; i < m_size_in_samples ; i++)
        {
            std::bitset<16> b(new_bufferIn_16[i]);

            for (int j=0; j <= m_msb_amount ; j++)
            {
                b[16-j] = rand() % 2;
            }

            a = b.to_ulong();
            c = static_cast<unsigned char>( a ); 
            new_bufferOut_16[i] = c;
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

