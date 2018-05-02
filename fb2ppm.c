#include <stdio.h>
#include "fblib.h"

typedef unsigned char u8;
#define _u (unsigned int)

int main (int argc, char **argv) {
	Screen s;
	if (fread (&s, sizeof(s), 1, stdin) != 1) return 1;

	char buffer[s.size];
	s.buffer = buffer;
	uint frame = 0;

	while (fread (buffer, s.size, 1, stdin) == 1) {
		char oname[12];
		snprintf (oname, 12, "%.6u.ppm", _u ++frame);
		printf ("processing frame %u.\r", _u frame);

		FILE *out = fopen (oname, "wb");
		fprintf (out, "P6\n%u %u\n255\n",
			_u s.width, _u s.height
		); // PPM header, then comes raw data:

		for (uint y = 0; y < s.height; y++) {
			for (uint x = 0; x < s.width; x++) {
				Color c = get_rgb (s, x, y);
				u8 v[3] = { (u8)c.r, (u8)c.g, (u8)c.b };
				fwrite (v, 3, 1, out);
			}
		}

		fclose (out);
	}

	printf ("\n");
}
