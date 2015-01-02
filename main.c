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
    uint N;
    
    N = readSoundFile("busy.wav", data, SAMPLES);
    dct(data, spec, N);
    dumpSignal(spec, 100u);
    
    return EXIT_SUCCESS;
}
