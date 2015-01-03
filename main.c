#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dct.h"
#include "snd.h"

#define SAMPLES 100000u
#define WINDOW     500u
#define STEP       250u

int main(int argc, char **argv)
{
    double data[SAMPLES],
           spec[WINDOW],
           nmax[WINDOW];
    uint k, N;
    FILE *f = NULL;  
    
    N = readSoundFile("busy2.wav", data, SAMPLES);
    maximumSpectrum(data, N, spec, WINDOW, STEP);
    nonMaximumSuppression(spec, nmax, WINDOW);    
    
    f = fopen("freq.txt", "w");
    for (k = 0; k < WINDOW; ++k)
    {
        fprintf(f, "%f\n", nmax[k]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
