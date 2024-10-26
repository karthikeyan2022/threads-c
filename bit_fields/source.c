/*
Bit fields
*/

#include "stdio.h"
#include "../common/common.h"

typedef union { 
    unsigned int ppn;
    struct {
        unsigned int page : 16;
        unsigned int block : 15;
        unsigned int valid : 1;        
    } phy_info; 
} PHY_ADDR;

int main() {

    PHY_ADDR temp;

    temp.phy_info.page = 10;
    temp.phy_info.block = 1;
    temp.phy_info.valid = 1;

    printBinary(temp.ppn);
    printBinary(temp.phy_info.page);
    
    printf("Block is valid? %d \n", (temp.ppn & MASK(31) ? 1 : 0));

    PHY_ADDR temp2;
    temp2 = temp;
    temp2.phy_info.valid = 0;
    printf("Block is valid? %d \n", (temp2.ppn & MASK(31) ? 1 : 0));
}