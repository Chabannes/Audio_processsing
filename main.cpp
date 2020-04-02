#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <iostream>

 
int main()
{

    FILE* fileIn = fopen("europa.raw", "rb");
    FILE* fileOut = fopen("output", "wb");

    long lSize;
    char * buffer;
    size_t result1;
    size_t result2;

    if (fileIn==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (fileIn , 0 , SEEK_END);
    lSize = ftell (fileIn);
    rewind (fileIn);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    std::cout << sizeof(*buffer) << " " << sizeof(char)*lSize << std::endl;
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result1 = fread (buffer, 1, lSize, fileIn);
    if (result1 != lSize) {fputs ("Reading error",stderr); exit (3);}

    std::cout << "\n\n" << result1 << "\n\n";

    // copy the buffer in out.raw
    result2 = fwrite(buffer,  sizeof(char), lSize, fileOut);
    std::cout << result2 << std::endl;
    if (result2 != lSize) {fputs ("Writing error",stderr); exit (4);}


    // terminate
    fclose (fileIn);
    fclose (fileOut);
    free (buffer);

}