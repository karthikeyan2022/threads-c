#include "stdio.h"
#include "../common/common.h"

void manage_port_B(int reg) {
    int temp;
    temp = reg;
    printBinary(temp);

    // set bits 2 and 5,
    temp = temp | (MASK(2)|MASK(5));
    printBinary(temp);

    // clear bits 0, 3 and 7
    temp = temp & ~(MASK(0)|MASK(3)|MASK(7));
    printBinary(temp);

    // check and invert: if bit 4 is high, then invert bit 1
    if(temp & MASK(4)) {
        temp = temp ^ MASK(1);
    }

    printBinary(temp);
    reg = temp; // commit changes to reg
}

int main()
{
    // Learning #1
    // Learn about masking macro - check bit
    printBinary(MASK(5) | MASK(4));
    printBinary((1 << 5) - 1);
    printBinary(31);


    // Learning #2 - Set/clear bit, check bit and invert bit
    manage_port_B(MASK(3)|MASK(7)|MASK(4)); // any number

}