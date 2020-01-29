#include <stdio.h>

int main() {
    unsigned char u = 0xF;
    unsigned char l = 0x1;
    unsigned char exp = 0xF1;

    unsigned char in[3];

    in[0] = u;
    in[1] = l;

    in[0] = '.';
    in[1] = '.';

    unsigned char hex = in[0] * 16 + in[1];

    printf("---> %x %x %x %x\n", in[0], in[1], exp, hex);

    return 0;

}