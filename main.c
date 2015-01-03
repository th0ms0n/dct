#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dct.h"
#include "snd.h"

#define SAMPLES 100000u
#define WINDOW     200u
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
       
    N = readSoundFile("app.wav", data, SAMPLES);    
    maximumSpectrum(data, N, spec1, WINDOW, STEP);  
    N = readSoundFile("applow.wav", data, SAMPLES);    
    maximumSpectrum(data, N, spec2, WINDOW, STEP);    
       
    diffSignal(spec1, spec2, diff, WINDOW);
    nonMaximumSuppression(diff, nmax1, WINDOW);
        
    f = fopen("diff.txt", "w");
    for (k = 0; k < WINDOW; ++k)
    {              
        fprintf(f, "%f\n", nmax1[k]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
