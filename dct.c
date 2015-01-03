#include "dct.h"
#include <math.h>
#include <string.h>


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
        sum += fabs(data[i]);    
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


/**********************************
* abs signal
**********************************/
void absSignal(double *data, uint samples)
{
    uint i;
    #pragma omp parallel for
    for (i = 0; i < samples; ++i)
    {
        if (data[i] < 0.0)
        {
            data[i] *= -1.0;
        }
    }    
}


/**********************************
* windowed spectrum computation
**********************************/
void maximumSpectrum(double *data, uint samples, double *out, uint window_size, uint step_size)
{
    double *tmp = NULL;    
    uint i, k, limit;
    memset(out, 0, window_size * sizeof(double));
    tmp = malloc(window_size * sizeof(double));

    limit = samples - window_size + 1u;
    for (i = 0; i < limit; i += step_size)
    {
        dct(&data[i], tmp, window_size);
        absSignal(tmp, window_size);
        
        for (k = 0; k < window_size; ++k)
        {
            if (tmp[k] > out[k])
            {
                out[k] = tmp[k];
            }
        }
    }
    free(tmp);
}


/**********************************
* windowed spectrum computation
**********************************/
void nonMaximumSuppression(double *in, double *out, uint samples)
{
    uint i, limit = samples - 1u;
    memset(out, 0, samples * sizeof(double));
    #pragma omp parallel for
    for (i = 1u; i < limit; ++i)
    {
        if (in[i] > in[i - 1u] && in[i] > in[i + 1u])
        {
            out[i] = in[i];
        }
    }
}
