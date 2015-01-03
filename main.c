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
           spec1[SAMPLES],
           nmax1[SAMPLES],
           spec2[SAMPLES],
           nmax2[SAMPLES],
           diff[SAMPLES],
           out[SAMPLES];              
    uint k, N;
    FILE *f = NULL;
       
    N = readSoundFile("busy.wav", data, SAMPLES);    
    maximumSpectrum(data, N, spec1, WINDOW, STEP);
    nonMaximumSuppression(spec1, nmax1, WINDOW);
    
    N = readSoundFile("busytick.wav", data, SAMPLES);    
    maximumSpectrum(data, N, spec2, WINDOW, STEP);
    nonMaximumSuppression(spec2, nmax2, WINDOW);
    
    diffSignal(spec1, spec2, diff, WINDOW);
    idct(diff, out, WINDOW);
    writeSoundFile("out.wav", out, WINDOW, 8000, 10);
     
    f = fopen("diff.txt", "w");
    for (k = 0; k < WINDOW; ++k)
    {              
        fprintf(f, "%f\n", diff[k]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
