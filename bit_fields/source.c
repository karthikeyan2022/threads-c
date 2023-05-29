#include <stdio.h>
// mask should be UNSIGNED
// This mask is 32-bit 
#define MASK(x) ((unsigned int) (1 << x))
void printBinary(unsigned int x) {

    // 32-bit
    printf("Binary of %u is : ", x);
    for(int i = 31; i >= 0; i--){

        if(x & MASK(i))
            printf("%d ", 1);
        else
            printf("%d ", 0);
    }
    printf("\n");

}

/////////////////////////////////////////////////////////
//////////////// BIT FIELDS //////////////////////////

typedef union { 
    unsigned int ppn;
    struct {
        unsigned int page : 16;
        unsigned int block : 15;
        unsigned int valid : 1;        
    } phy_info; 
} phyaddr;

int main() {

    phyaddr temp;

    temp.phy_info.page = 10;
    temp.phy_info.block = 1;
    temp.phy_info.valid = 1;

    printBinary(temp.ppn);
    printBinary(temp.phy_info.page);
    
    printf("Block is valid? %d \n", (temp.ppn & MASK(31) ? 1 : 0));

    phyaddr temp2;
    temp2 = temp;
    temp2.phy_info.valid = 0;
    printf("Block is valid? %d \n", (temp2.ppn & MASK(31) ? 1 : 0));
}