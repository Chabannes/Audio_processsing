#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <iostream>


#define N 3 * 44100
 
int main()
{


    // FILE *pfile = fopen("europa.raw", "rb");
    FILE *pipeout;
    pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - out.wav", "w");

    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;
    size_t result2;

    pFile = fopen ( "europa.raw" , "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
    /* the whole file is now loaded in the memory buffer. */

    // std::cout << "\n\n" << buffer << "\n\n";
    std::cout << "\n\n" << result << "\n\n";

    // copy the buffer in out.raw
    result2 = fwrite(buffer,  sizeof(char), sizeof(buffer), pipeout);
    std::cout << result << std::endl;


    // terminate
    fclose (pFile);
    free (buffer);

}