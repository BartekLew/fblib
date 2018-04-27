/* fbgrad: draw gradient using framebuffer.
   run in console, X11 would overwrite everything immediatelly.

   (c) Lev, 2018, MIT licence
*/

#include "fblib.h"

#include <stdio.h>
#include <time.h>

void fb_main (Screen s) {
    int time_start = time (NULL);

    for (uint t = 0; t < 256; t++) {
         for (uint y = 0; y < s.height; y++) {
             for (uint x = 0; x < s.width; x++) {
                 uint pix_offset = x * s.bytes_per_pixel + y * s.bytes_per_line;
                 s.buffer[pix_offset + s.red] = x * 255 / s.width;
                 s.buffer[pix_offset + s.green] = y * 255 / s.height;
                 s.buffer[pix_offset + s.blue] = t;
             }
         }
    }

    int time_end = time(NULL);

    printf ("FPS: %.2f.\n", 255.0 / (time_end - time_start));
}
