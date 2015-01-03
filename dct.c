#include "dct.h"
#include <math.h>
#include <string.h>
#include <float.h>


/**********************************
* discrete cosine transform
****************void shiftSignal(double *in, double *out, uint samples, int shift);******************/
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
        for (k = 0; k < window_size; ++k)
        {
            if (fabs(tmp[k]) > fabs(out[k]))
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
    double fabsi;
    memset(out, 0, samples * sizeof(double));
    for (i = 1u; i < limit; ++i)
    {
        fabsi = fabs(in[i]);
        if (fabsi > fabs(in[i - 1u]) && fabsi > fabs(in[i + 1u]))
        {
            out[i] = in[i];
        }
    }
}


/**********************************
* how to shift second signal
* for best correlation
**********************************/
int bestShift(double *sig1, double *sig2, uint samples)
{
    int mins = -0.5 * samples + 1,
        maxs =  0.5 * samples - 1,
        s, i, cnt, is, shift = 0;
    double sum, best;
    
    best = -DBL_MAX;
    for (s = mins; s <= maxs; ++s)
    {
        /* compute correlation */
        sum = 0.0;
        cnt = 0;
        for (i = 0; i < samples; ++i)
        {
            is = i + s;
            if (is < 0 || is >= samples) continue;           
            sum += sig1[i] * sig2[is];
            ++cnt;
        }
        sum /= cnt;        
        
        /* find highest sum */
        if (sum > best)
        {
            best = sum;
            shift = s;            
        }     
    }
    
    return shift;
}


/**********************************
* shift signal
**********************************/
void shiftSignal(double *in, double *out, uint samples, int shift)
{
    uint i, is;
    memset(out, 0, samples * sizeof(double));
    for (i = 0; i < samples; ++i)
    {
        is = i + shift;
        if (is < 0 || is >= samples) continue;
        out[i] = in[is];   
    }
}


/**********************************
* diff signals
**********************************/
void diffSignal(double *sig1, double *sig2, double *out, uint samples)
{
    uint i;   
    for (i = 0; i < samples; ++i)
    {
        out[i] = sig2[i] - sig1[i];    
    }
}
