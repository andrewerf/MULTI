
#include "stdio.h"

#define NPIXEL 256
#define NLINE  256


void build_buffer( register unsigned char* buffer, register int step )
{
    for (register int pixel = 0; pixel < NPIXEL; pixel += 1) {
        for (register int line = 0 ; line < NLINE ; line += 1) {
            if (( (pixel>>step & 0x1) && !(line>>step & 0x1)) ||
                (!(pixel>>step & 0x1) &&  (line>>step & 0x1))) {
                buffer[NPIXEL * line + pixel] = 0xFF;
            }
            else {
                buffer[NPIXEL * line + pixel] = 0x0;
            }
        }
    }
    tty_printf(" - build   OK at cycle %d\n", proctime());
}

void display_buffer( unsigned char* buffer )
{
    if (fb_completed() != 0) {
        tty_printf("\n!!! error in fb_completed syscall !!!\n");
        exit();
    }
    tty_printf(" - display OK at cycle %d\n", proctime());

    if (fb_write(0, buffer, NLINE * NPIXEL)!= 0) {
        tty_printf("\n!!! error in fb_write syscall !!!\n");
        exit();
    }
}

__attribute__ ((constructor)) void main() {
    unsigned char BUF1[NPIXEL * NLINE];
    unsigned char BUF2[NPIXEL * NLINE];

    unsigned char* buffers[2] = {
            BUF1, BUF2
    };

    build_buffer( buffers[0], 1 );
    for (int step = 2; step < 6; step += 1) {
        tty_printf("\n*** damier %d ***\n\n", step);
        display_buffer( buffers[step % 2] );
        build_buffer( buffers[( step + 1 ) % 2], step );
    }
    display_buffer( buffers[0] );
    if (fb_completed() != 0) {
        tty_printf("\n!!! error in fb_completed syscall !!!\n");
        exit();
    }
    tty_printf(" - display OK at cycle %d\n", proctime());


    tty_printf("\nFin du programme au cycle = %d\n\n", proctime());
    exit();
} // end main
