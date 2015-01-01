#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "dct.h"


int main(int argc, char **argv)
{
    double samples[] = {2.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    uint i, N = sizeof(samples) / sizeof(double);
    
    double *out = malloc(sizeof(samples));
    
    dct(samples, out, N);    
    for (i = 0; i < N; ++i)
    {
        printf("%f\n", out[i]);    
    }    
    
    printf("*** back ***\n");
    idct(out, samples, N);
    for (i = 0; i < N; ++i)
    {
        printf("%f\n", samples[i]);    
    }    
    
    printf("*** normalized ***\n");
    normalize(out, N);
    for (i = 0; i < N; ++i)
    {
        printf("%f\n", out[i]);    
    }    
    
    free(out); 
    return EXIT_SUCCESS;
}
