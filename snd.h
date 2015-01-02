#ifndef _SND_H_
#define _SND_H_


#include <sndfile.h>
#include "types.h"


/**********************************
* prototypes
**********************************/
uint readSoundFile(const char *path, double *buf, uint samples);


#endif
