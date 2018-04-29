/* fbrec: record frame buffer state

   (c) Lev, 2018, MIT licence
*/

#include "fblib.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>

#define Die(Format, ...) \
	{ \
		fprintf (stderr, "%s:%u " Format, __FILE__, __LINE__,  __VA_ARGS__); \
		return -1; \
	}
	
uint frames = 0;
FILE *output = NULL;
int time_start;

void interrupt(int signum) {
	int time_end = time(NULL);


	printf ("FPS: %.2f\n", (float)0x100 / (time_end-time_start));

}

int fb_main (Screen s, Strings args) {
	if (args.count < 2)
		Die ("lacking parameters: %s\n", "name");
	
	FILE *output = fopen (args.vals[1], "w");
	if (output == NULL)
		Die ("can't write file: %s\n", args.vals[1]);
	
	signal (SIGINT, interrupt);
	time_start = time (NULL);

	printf ("rs=%u\n", s.size);
	fwrite (&s, sizeof(s), 1, output);
	for (uint i = 0; i < 0x100; i++)
		fwrite (s.buffer, s.size, 1, output);

	fclose (output);
	interrupt(0);
	return 0;
}
