#include "common.h"
#include <stdio.h>

void printBinary(unsigned int x) {

    // 32-bit
    printf("Binary of %d is : ", x);
    for(int i = 31; i >= 0; i--){

        if(x & MASK(i))
            printf("%d ", 1);
        else
            printf("%d ", 0);
    }
    printf("\n");

}