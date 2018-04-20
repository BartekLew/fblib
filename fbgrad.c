/* fbgrad: draw gradient using framebuffer.
   run in console, X11 would overwrite everything immediatelly.

   (c) Lev, 2018, MIT licence
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#define fbdev "/dev/fb0"
#define ttydev "/dev/tty"

typedef uint_fast16_t uint;

typedef struct {
    uint_fast8_t    r, g, b, a;
} Color;

#define Die(Msg, ...) { \
    fprintf (stderr, "fbgrad: " Msg ".\n", __VA_ARGS__); \
    exit(1); \
}\

#define Assumption(Cond, Msg) \
    if (!(Cond)) { \
        fprintf (stderr, "fbgrad: failed assumption: %s\n", Msg);\
        exit(2);\
    }

int main (int argc, char **argv) {
    int ttyfd = open (ttydev, O_RDWR);
    if (ttyfd < 0)
        Die ("cannot open \"%s\"", ttydev);

    if (ioctl (ttyfd, KDSETMODE, KD_GRAPHICS) == -1)
        Die ("cannot set tty into graphics mode on \"%s\"", ttydev);

    int fbfd = open (fbdev, O_RDWR);
    if (fbfd < 0)
        Die ("cannot open \"%s\"", fbdev);

    struct fb_var_screeninfo vinf;
    struct fb_fix_screeninfo finf;

    if (ioctl (fbfd, FBIOGET_FSCREENINFO, &finf) == -1)
        Die ("cannot open fixed screen info for \"%s\"", fbdev);

    if (ioctl (fbfd, FBIOGET_VSCREENINFO, &vinf) == -1)
        Die ("cannot open variable screen info for \"%s\"", fbdev);

    Assumption ((vinf.red.offset%8) == 0 && (vinf.red.length == 8) &&
                (vinf.green.offset%8) == 0 && (vinf.green.length == 8) &&
                (vinf.blue.offset%8) == 0 && (vinf.blue.length == 8) &&
                (vinf.transp.offset) == 0 && (vinf.transp.length == 0) &&
                vinf.red.msb_right == 0 &&
                vinf.green.msb_right == 0 &&
                vinf.blue.msb_right == 0,
                "Color masks are 8bit, byte aligned, little endian, no transparency."
    );

    size_t screen_size = finf.line_length * vinf.yres;
    size_t bytes_per_pixel = vinf.bits_per_pixel / 8;
    char *screen = mmap (0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (screen == MAP_FAILED)
        Die ("cannot map frame buffer \"%s\"", fbdev);

    int time_start = time (NULL);

    for (uint t = 0; t < 255; t++) {
        for (uint y = 0; y < vinf.yres; y++) {
            for (uint x = 0; x < vinf.xres; x++) {
                uint pix_offset = x * bytes_per_pixel + y * finf.line_length;
                screen[pix_offset + vinf.red.offset/8] = x * 255 / vinf.xres;
                screen[pix_offset + vinf.green.offset/8] = y * 255 / vinf.yres;
                screen[pix_offset + vinf.blue.offset/8] = t;
            }
        }
    }

    int time_end = time(NULL);

    munmap (screen, screen_size);

    if (ioctl (ttyfd, KDSETMODE, KD_TEXT) == -1)
        Die ("cannot set tty into text mode on \"%s\"", ttydev);

    close (fbfd);
    close (ttyfd);

    printf ("FPS: %.2f.\n", 255.0 / (time_end - time_start));

    return EXIT_SUCCESS;
}
