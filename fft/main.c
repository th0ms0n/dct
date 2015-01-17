#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"
#include "snd.h"

#define SAMPLES 500000u
#define WINDOW    2048u
#define STEP       100u

int main(int argc, char **argv)
{
    double data[SAMPLES],           
           spec1[WINDOW],
           nmax1[WINDOW],
           spec2[WINDOW],
           nmax2[WINDOW],
           diff[WINDOW];                       
    uint k, N;
    FILE *f = NULL;
       
    N = readSoundFile("engine2.wav", data, SAMPLES);    
    maximumSpectrum(data, N, spec1, WINDOW, STEP);
    nonMaximumSuppression(spec1, spec2, WINDOW);
        
    f = fopen("engine2.txt", "w");
    for (k = 0; k < WINDOW / 2u + 1u; ++k)
    {              
        fprintf(f, "%f\n", spec2[k]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
