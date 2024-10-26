#include <stdio.h>

// Pass by value
// Pointer value is changed but wont be reflected outside
void fun(int* b)
{
    int c = 20;
    b = &c;
}

// Pass by pointer
// The "value that the pointer points to" changes here. So reflected outside
void fun2(int* b)
{
    int c = 20;
    *b = c;
}

// Pass by pointer of pointer
// The pointer to pointer value is changed here. Made as address value of var c.
// The value is reflected outside. 
void fun3(int** b)
{
    int c = 20;
    *b = &c;
}

int main()
{
    int a = 10;
    int *ptr = &a;
    
    // Pass by value example - prints 10
    fun(ptr);
    printf("%d\n", *ptr);

    // Pass by pointer example - prints 20
    fun2(ptr);  
    printf("%d\n", *ptr);

    // Pass by pointer example - prints 20
    // But can produce undefined behaviour
    fun3(&ptr);  
    printf("%d\n", *ptr);

    return 0;
}
