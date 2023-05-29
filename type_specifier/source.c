#include "stdio.h"


int main()
{
    // Learning #1 - constant variable example
    const double pi = 3.141;
    //pi = pi/2; //--> error: assignment of read-only variable 'pi'
    printf("%f\n", pi);

    // Learning #2 - pointer pointing to a constant int value
    const int* ptr; // ptr points to a const int variable a
    const int carr[2] = {0, 10};
    ptr = carr;
    
    //*ptr = *ptr + 2; // error: assignment of read-only location '*ptr'
    // (*ptr)++;       // same error as above : this will expand to *ptr = *ptr + 1
    *ptr++;             // This will compile since this will expand to ptr = ptr + 1 i.e, carr[1]
    printf("Value of *ptr is %d \n", *ptr);


    // Learning #3 - constant pointer whose pointer addr value cant be changed..
    int arr[2] = {0, 10};
    int arr2[2] = {3, 1};
    int * const ptr2 = arr;
    
    //ptr2 = arr; //  error: assignment of read-only variable 'ptr2'
    //ptr2 = arr2; //  error: assignment of read-only variable 'ptr2'
    //*ptr2++;        // error : same as above since it expands to ptr2 = ptr2 + 1 
    (*ptr2)++;   // compiles.. since it expands to *ptr2 = *ptr2 + 1.. i.e., arr[0]++;
    printf("Value of *ptr2 is %d \n", *ptr2);
}