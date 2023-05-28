#include "stdio.h"


int main()
{
    const int* ptr;

    int a = 1;
    ptr = &a;

    //const *int ptr2;
    int b = 2;
    //ptr2 = &a;
    //ptr2 = &b;
    printf("The value of a is %d \n", *ptr);
}