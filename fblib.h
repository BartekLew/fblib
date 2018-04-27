#ifndef _FBLIB_H_
#define _FBLIB_H_

#define fbdev "/dev/fb0"
#define ttydev "/dev/tty"


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

typedef struct {
    uint_fast8_t    r, g, b, a;
} Color;


// This is the entry point of your application:
extern void fb_main(Screen s);

#endif
