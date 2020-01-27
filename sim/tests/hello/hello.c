#include "sc_print.h"

int main()
{
    volatile unsigned int *s1 = (unsigned int *) 0x900000;
    *s1 = 0xdeadbeef;
    unsigned int a = *s1;
    volatile unsigned int *s2 = (unsigned int *) 0x920000;
    *s2 = 0xbadc0ffe;
    s2[4] = 0xdecaf101;
    //unsigned int a = *s1;
    sc_printf("Hello from SCR1!, %x, %x, %x\n", a, *s2, s2[4]);
    return 0;
}
