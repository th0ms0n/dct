#ifndef _DCT_H_
#define _DCT_H_


#include "types.h"


/**********************************
* some definitions and typedefs
**********************************/
#define DCT_PI 3.141592654


/**********************************
* prototypes
**********************************/
void dct(double *in, double *out, uint samples);
void idct(double *in, double *out, uint samples);
void normalizeSignal(double *data, uint samples);
void dumpSignal(double *data, uint samples);
void absSignal(double *data, uint samples);
void maximumSpectrum(double *data, uint samples, double *out, uint window_size, uint step_size);
void nonMaximumSuppression(double *in, double *out, uint samples);


#endif
