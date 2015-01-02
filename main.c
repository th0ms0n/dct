#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "dct.h"
#include "snd.h"

#define SAMPLES 100000u

int main(int argc, char **argv)
{
    double data[SAMPLES],
           spec[SAMPLES];
    uint i, N;
    FILE *f = NULL;
    
    N = readSoundFile("trans2.wav", data, SAMPLES);
    dct(data, spec, N);
    
    f = fopen("trans2.txt", "w");
    for (i = 0; i < N; ++i)
    {
        fprintf(f, "%f\n", spec[i]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
