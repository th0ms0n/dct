#include "dct.h"
#include <math.h>


/**********************************
* discrete cosine transform
**********************************/
void dct(double *in, double *out, uint samples)
{
    uint i, k;
    double sum, coeff = DCT_PI / samples; 
    
    #pragma omp parallel for   
    for (i = 0; i < samples; ++i)
    {
        sum = 0.0;        
        for (k = 0; k < samples; ++k)
        {
            sum += in[k] * cos(coeff * (k + 0.5) * i);
        }
        out[i] = sum; 
    }
}


/**********************************
* inverse dct
**********************************/
void idct(double *in, double *out, uint samples)
{
    uint i, k;
    double sum, coeff = DCT_PI / samples,
           init = 0.5 * in[0],
           scale = 2.0 / samples; 
           
    #pragma omp parallel for
    for (i = 0; i < samples; ++i)
    {
        sum = init;        
        for (k = 1u; k < samples; ++k)
        {
            sum += in[k] * cos(coeff * k * (i + 0.5));
        }
        out[i] = scale * sum; 
    }
}


/**********************************
* normalize spectrum
**********************************/
void normalizeSignal(double *data, uint samples)
{
    uint i;
    double sum = 0.0;
    for (i = 0; i < samples; ++i)
    {
        sum += data[i];    
    }
    for (i = 0; i < samples; ++i)
    {
        data[i] /= sum; 
    }
}


/**********************************
* dump signal
**********************************/
void dumpSignal(double *data, uint samples)
{
    uint i;
    for (i = 0; i < samples; ++i)
    {
        fprintf(stdout, "%.2f ", data[i]);
    }
    fprintf(stdout, "\n");
}
