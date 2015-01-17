
#ifndef _TYPES_H_
#define _TYPES_H_

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char cbool;
typedef unsigned char byte;

#define FALSE 0
#define TRUE  1u

#define MY_PI 3.141592654

#define ALLOC(_ptr, _num, _type) 												                \
{																				                \
	_ptr = (_type *)malloc((_num) * sizeof(_type));								                \
	if (_ptr == NULL)															                \
	{																			                \
		fprintf(stderr, __FUNCTION__ ": malloc failed for %s pieces of %s\n", #_num, #_type);	\
		exit(EXIT_FAILURE);														                \
	}																			                \
}	

#define FREE(_ptr)																                \
{																				                \
	free(_ptr);																	                \
	_ptr = NULL;																                \
}

#define ERR(x)																	                \
{																				                \
	fprintf(stderr, __FUNCTION__ ": %s\n", x);							                        \
	exit(EXIT_FAILURE);															                \
}

#define INFO(x) fprintf(stderr, __FUNCTION__ ": %s\n", x)

#endif

