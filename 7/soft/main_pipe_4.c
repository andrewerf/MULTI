
#include "stdio.h"

#define NPIXEL 256
#define NLINE  256
#define NPROC  4


void build_buffer( register unsigned char* buffer, register int step )
{
    register int pid = procid();
    register int from_line = pid * ( NLINE / NPROC );
    register int to_line = (pid + 1) * ( NLINE / NPROC );

    for (register int pixel = 0; pixel < NPIXEL; pixel += 1) {
        for (register int line = from_line ; line < to_line ; line += 1) {
            if (( (pixel>>step & 0x1) && !(line>>step & 0x1)) ||
                (!(pixel>>step & 0x1) &&  (line>>step & 0x1))) {
                buffer[NPIXEL * line + pixel] = 0xFF;
            }
            else {
                buffer[NPIXEL * line + pixel] = 0x0;
            }
        }
    }
    tty_printf(" - build   OK at cycle %d by proc %d\n", proctime(), pid);
    barrier_wait( 0 );
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

unsigned char BUF1[NPIXEL * NLINE];
unsigned char BUF2[NPIXEL * NLINE];

__attribute__ ((constructor)) void main() {
    barrier_init( 0, NPROC );
    unsigned char* buffers[2] = {
            BUF1, BUF2
    };

    build_buffer( buffers[0], 1 );
    for (int step = 2; step < 6; step += 1) {
        tty_printf("\n*** damier %d ***\n\n", step);
        if ( procid() == 0 )
            display_buffer( buffers[step % 2] );
        build_buffer( buffers[( step + 1 ) % 2], step );
    }
    if ( procid() == 0 )
    {
        display_buffer( buffers[0] );
        if (fb_completed() != 0) {
            tty_printf("\n!!! error in fb_completed syscall !!!\n");
            exit();
        }
    }

    tty_printf("\nFin du programme au cycle = %d\n\n", proctime());
    exit();
} // end main
