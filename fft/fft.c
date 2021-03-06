#include "fft.h"
#include <math.h>
#include <string.h>
#include <float.h>
#include <fftw3.h>


/**********************************
* fft
**********************************/
void fft(double *in, double *out, uint samples)
{
    uint i, n = samples / 2u + 1u;
    double a, b;

    fftw_complex *com = fftw_malloc(n * sizeof(fftw_complex)); 
    fftw_plan plan = fftw_plan_dft_r2c_1d(samples, in, com, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan); 
            
    /* fill out with amplitude */
    memset(out, 0, samples * sizeof(double));
    for (i = 0; i < n; ++i)
    {
        a = com[i][0];
        b = com[i][1];    
        out[i] = sqrt(a * a + b * b);    
    }
    
    fftw_free(com);    
}


/**********************************
* inverse fft
**********************************/
void ifft(double *in, double *out, uint samples)
{
    
}


/**********************************
* window function
**********************************/
void window(double *in, double *out, uint samples)
{
    uint i;
    double ham;
    for (i = 0; i < samples; ++i)
    {
        ham = 0.54 - 0.46 * cos((2.0 * MY_PI * i) / (samples - 1u));
        out[i] = ham * in[i];    
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
    double *tmp = NULL, *windowed = NULL;    
    uint i, k, limit;
    
    memset(out, 0, window_size * sizeof(double));    
    tmp = malloc(window_size * sizeof(double));
    windowed = malloc(window_size * sizeof(double));

    limit = samples - window_size + 1u;
    for (i = 0; i < limit; i += step_size)
    {
        window(&data[i], windowed, window_size);
        fft(windowed, tmp, window_size);
        for (k = 0; k < window_size; ++k)
        {
            if (tmp[k] > out[k])
            {
                out[k] = tmp[k];
            }
        }
    }
    free(tmp);
    free(windowed);
}


/**********************************
* windowed spectrum computation
**********************************/
void nonMaximumSuppression(double *in, double *out, uint samples)
{
    uint i, limit = samples - 1u;    
    memset(out, 0, samples * sizeof(double));
    for (i = 1u; i < limit; ++i)
    {       
        if (in[i] > in[i - 1u] && in[i] > in[i + 1u])
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
        out[i] = fabs(sig2[i] - sig1[i]);    
    }
}
