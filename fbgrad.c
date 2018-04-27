/* fbgrad: draw gradient using framebuffer.
   run in console, X11 would overwrite everything immediatelly.

   (c) Lev, 2018, MIT licence
*/

#include "fblib.h"

#include <stdio.h>
#include <time.h>

int fb_main (Screen s, Strings args) {
    int time_start = time (NULL);

    for (uint t = 0; t < 256; t++) {
         for (uint y = 0; y < s.height; y++) {
             for (uint x = 0; x < s.width; x++) {
		 dot_rgb (s, x, y,
			x * 255 / s.width,
			y * 255 / s.height,
			t );
             }
         }
    }

    int time_end = time(NULL);

    printf ("FPS: %.2f.\n", 255.0 / (time_end - time_start));
    return 0;
}
