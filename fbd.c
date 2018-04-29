/* fbd: display image

   (c) Lev, 2018, MIT licence
*/

#include "fblib.h"

#include <stdio.h>
#include <time.h>

#define Die(Format, ...) \
	{ \
		fprintf (stderr, "%s:%u " Format, __FILE__, __LINE__,  __VA_ARGS__); \
		exit(-1); \
	}
	
FILE *choose_input (Strings args) {
	if (args.count == 1)
		return stdin;

	FILE *result = fopen (args.vals[1], "r");
	if (result == NULL)
		Die ("no file to read: %s\n", args.vals[1]);

	return result;
}

int fb_main (Screen s, Strings args) {
	FILE *input = choose_input(args);
	
	Screen header;
	if (fread (&header, sizeof(Screen), 1, input) < 1)
		Die ("can't read %s\n", "header");

	if (header.size != s.size)
		Die ("%s\n", "wrong format");

	int time_start = time (NULL);
	uint frames = 0;

	while (fread (s.buffer, s.size, 1, input) >= 1) frames++;

	int time_end = time(NULL);

	fclose (input);

	printf ("FPS: %.2f\n", (float)frames / (time_end-time_start));

	return 0;
}
