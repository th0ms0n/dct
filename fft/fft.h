#ifndef _FFT_H_
#define _FFT_H_


#include "types.h"


/**********************************
* some definitions and typedefs
**********************************/
#define DCT_PI 3.141592654


/**********************************
* prototypes
**********************************/
void fft(double *in, double *out, uint samples);
void ifft(double *in, double *out, uint samples);
void normalizeSignal(double *data, uint samples);
void dumpSignal(double *data, uint samples);
void absSignal(double *data, uint samples);
void maximumSpectrum(double *data, uint samples, double *out, uint window_size, uint step_size);
void nonMaximumSuppression(double *in, double *out, uint samples);
int  bestShift(double *sig1, double *sig2, uint samples);
void shiftSignal(double *in, double *out, uint samples, int shift);
void diffSignal(double *sig1, double *sig2, double *out, uint samples);
void window(double *in, double *out, uint samples);

#endif
