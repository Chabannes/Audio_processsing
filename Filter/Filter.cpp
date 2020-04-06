#include "Filter.h"


#include <iostream>
#include <string>



Filter::Filter() 
{}


Filter::Filter(std::string fileIn_name, int number_bits) : m_fileIn_name(fileIn_name), m_number_bits(number_bits)
{}


Filter::~Filter() 
{}


void Filter::open_fileIn()
{
    m_fileIn = fopen(m_fileIn_name.c_str(), "rb");
    if (m_fileIn==NULL) {fputs ("File error",stderr); exit (1);}
}


void Filter::open_fileOut()
{
    m_fileOut = fopen(m_fileOut_name.c_str(), "wb");
}


void Filter::set_sample_size()
{
    switch (m_number_bits)
    {
    case 8:
       m_sample_size = 1;
       break;

    case 16:
       m_sample_size = 2;
       break;
   default:
       fputs ("number of bits must be 8 or 16", stderr); exit (1);
    }
}


void Filter::set_size_in_bytes()
{
    fseek (m_fileIn , 0 , SEEK_END);
    m_size_in_bytes = ftell (m_fileIn);
}


void Filter::set_size_in_samples()
{
    m_size_in_samples = m_size_in_bytes / m_sample_size; 
}
