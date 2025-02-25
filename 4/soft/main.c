/********************************************************
 *      This simple program computes the sum
 *      of the NMAX first integers, stores the result 
 *      in a table, and displays this result on the
 *      TTY terminal. It uses a recursive function,
 *      in order to use the stack.
 ********************************************************/

#define NMAX 30

#include "stdio.h"

int sum(int n) {
    if (n == 0) {
        return n;
    }
    else {
        return n + sum(n - 1);
    }
}


__attribute__ ((constructor)) void main() {
    int tab[NMAX];

    for (int i = 0; i < NMAX; i += 1) {
        tab[i] = sum(i);
        tty_printf("tab[%d] = %d \n", i, tab[i]);
    }
   
    tty_printf("\ncycle = %d \n", proctime());
    exit();
}

