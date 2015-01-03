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
           spec1[WINDOW],
           spec2[WINDOW],
           shifted[WINDOW];
    uint k, N;
    FILE *f = NULL;
    int shift;
    
    N = readSoundFile("car.wav", data, SAMPLES);
    maximumSpectrum(data, N, spec1, WINDOW, STEP);       
    
    N = readSoundFile("carpitch.wav", data, SAMPLES);
    maximumSpectrum(data, N, spec2, WINDOW, STEP);
    
    printf("shift: %i\n", shift = bestShift(spec1, spec2, WINDOW));
    shiftSignal(spec2, shifted, WINDOW, shift);
    
    printf("shift: %i\n", bestShift(spec1, shifted, WINDOW));
    
    
    
    f = fopen("carpitch.txt", "w");
    for (k = 0; k < WINDOW; ++k)
    {        
        fprintf(f, "%f\n", shifted[k]);    
    }    
    fclose(f);
    
    return EXIT_SUCCESS;
}
