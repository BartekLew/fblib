#ifndef _FBLIB_H_
#define _FBLIB_H_

#include <stdint.h>
#include <stdlib.h>

typedef uint_fast16_t uint;

typedef struct {
    char    *buffer;
    size_t  size,
            bytes_per_pixel, bytes_per_line,
            width, height;
    uint    red, green, blue;
} Screen;


#endif
