/* fbd: display image

   (c) Lev, 2018, MIT licence
*/

#include "fblib.h"

#include <stdio.h>
#include <time.h>

#define Die(Format, ...) \
	{ \
		fprintf (stderr, "%s:%u " Format, __FILE__, __LINE__,  __VA_ARGS__); \
		return -1; \
	}
	

int fb_main (Screen s, Strings args) {
	if (args.count < 2)
		Die ("lacking parameters: %s\n", "name");
	
	FILE *input = fopen (args.vals[1], "r");
	if (input == NULL)
		Die ("no file to read: %s\n", args.vals[1]);
	
	Screen header;
	if (fread (&header, sizeof(Screen), 1, input) < 1)
		Die ("can't read %s\n", "header");

	if (header.size != s.size)
		Die ("%s\n", "wrong format");

	int time_start = time (NULL);

	for (uint i = 0; i < 0x100; i++) {
		if (fread (s.buffer, s.size, 1, input) < 1)
			Die ("%s\n", "end of input");
	}

	int time_end = time(NULL);

	fclose (input);

	printf ("FPS: %.2f\n", (float)0x100 / (time_end-time_start));

	return 0;
}
