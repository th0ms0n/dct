#ifndef _DCT_H_
#define _DCT_H_


/**********************************
* some definitions and typedefs
**********************************/
typedef unsigned int uint;
#define DCT_PI 3.141592654


/**********************************
* prototypes
**********************************/
void dct(double *in, double *out, uint samples);
void idct(double *in, double *out, uint samples);
void normalize(double *data, uint samples);

#endif
