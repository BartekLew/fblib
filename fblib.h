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

typedef struct {
    uint	count;
    char	**vals;
} Strings;

static inline void dot_rgb (Screen s, uint x, uint y, uint r, uint g, uint b) {
    uint pix_offset = x * s.bytes_per_pixel + y * s.bytes_per_line;
    s.buffer[pix_offset + s.red] = r;
    s.buffer[pix_offset + s.green] = g;
    s.buffer[pix_offset + s.blue] = b;
}

// This is the entry point of your application:
extern int fb_main(Screen s, Strings args);

#endif
