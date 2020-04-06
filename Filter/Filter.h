#ifndef DEF_FILTER
#define DEF_FILTER

#include <string>



class Filter
{
    public :

    Filter(); 
    Filter(std::string fileIn_name, int number_bits);
    virtual ~Filter();
    void open_fileIn();
    void open_fileOut();
    void set_sample_size();
    void set_size_in_bytes();
    void set_size_in_samples();


    protected:

    int m_number_bits;
    int m_sample_size;
    int m_size_in_bytes;
    int m_size_in_samples;
    std::string m_fileIn_name;
    std::string m_fileOut_name;
    FILE* m_fileIn;
    FILE* m_fileOut;
    void* m_bufferIn;
    void* m_bufferOut;

};

#endif