#include "fblib.h"

#include <stdio.h>
#include <time.h>
#include <signal.h>

#define Die(Format, ...) \
	{ \
		fprintf (stderr, "%s:%u " Format, __FILE__, __LINE__,  __VA_ARGS__); \
		exit(-1); \
	}
	
uint frames = 0;
FILE *output = NULL;
int time_start;

void interrupt(int signum) {
	int time_end = time(NULL);

	printf ("FPS: %.2f\n", (float)0x100 / (time_end-time_start));
	exit(0);
}

FILE *choose_output (Strings args) {
	if (args.count == 1)
		return stdout;

	
	FILE *f = fopen (args.vals[1], "w");

	if (f == NULL)
		Die ("can't write file: %s\n", args.vals[1]);

	return f;
}

int fb_main (Screen s, Strings args) {
	FILE *output = choose_output(args);
	signal (SIGINT, interrupt);

	time_start = time (NULL);
	fwrite (&s, sizeof(s), 1, output);
	while (fwrite (s.buffer, s.size, 1, output) >= 1);

	if (output != stdout) fclose (output);
	interrupt(0);
	return 0;
}
