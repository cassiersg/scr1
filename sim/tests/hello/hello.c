#include "sc_print.h"

#include "tv.c"

#define TV tv1

#define NB (sizeof(TV)/4)

unsigned int result[NB];

int main()
{
    //volatile unsigned int *s1 = (unsigned int *) 0x900000;
    //*s1 = 0xdeadbeef;
    //unsigned int a = *s1;
    volatile unsigned int *spook_fifo = (unsigned int *) 0x920000;
    volatile unsigned int *spook_csr = (unsigned int *) 0x920004;
    volatile unsigned int *spook_d1 = (unsigned int *) 0x920008;
    volatile unsigned int *spook_d2 = (unsigned int *) 0x92000c;
    int i;
    for (i=0; i < sizeof(NB)/4; i++) {
        *spook_fifo = TV[i];
    }
    *spook_csr = 0x00000008;
    while ((*spook_csr & 0x00000002)) ;
    *spook_csr = 0x00000000; // needed ?
    int nb_outputs = (*spook_csr >> 14) & 0x1FF;
    for (i=0; i < nb_outputs; i++) {
        result[i] = *spook_fifo;
    }
    sc_printf("nb_outputs: %d\n", nb_outputs);
    for (i=0; i < nb_outputs; i++) {
        sc_printf("0x%x\n", result[i]);
    }
    //sc_printf("Hello from SCR1!, %x, %x, %x\n", *spook_csr, *spook_d1, *spook_d2);
    return 0;
}
