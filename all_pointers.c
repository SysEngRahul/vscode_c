#include <stdio.h>

/* function prototypes */
void funcPointerDemo();
void functionExample(int x);

int main()
{
    /* 1. NULL Pointer */
    int *ptr1 = NULL;

    /* 2. Simple Pointer */
    int a = 10;
    int *ptr2 = &a;

    /* 3. Pointer to Pointer */
    int **ptr3 = &ptr2;

    /* 4. Void Pointer */
    void *ptr4;
    ptr4 = &a;

    /* 5. Array Pointer */
    int arr[3] = {1,2,3};
    int *ptr5 = arr;

    /* 6. Pointer to Array */
    int (*ptr6)[3] = &arr;

    /* 7. Function Pointer */
    void (*ptr7)(int) = functionExample;

    /* 8. Constant Pointer */
    int b = 20;
    int *const ptr8 = &b;

    /* 9. Pointer to Constant */
    const int *ptr9 = &a;

    /* 10. Double Pointer (another example) */
    int **ptr10 = &ptr2;

    printf("Simple pointer value: %d\n", *ptr2);
    printf("Pointer to pointer value: %d\n", **ptr3);

    printf("Void pointer value: %d\n", *(int*)ptr4);

    printf("Array using pointer: %d %d %d\n", ptr5[0], ptr5[1], ptr5[2]);

    printf("Pointer to array: %d\n", (*ptr6)[1]);

    ptr7(50);   // function pointer call

    printf("Constant pointer value: %d\n", *ptr8);

    printf("Pointer to constant value: %d\n", *ptr9);

    printf("Double pointer again: %d\n", **ptr10);

    funcPointerDemo();

    return 0;
}

void functionExample(int x)
{
    printf("Function pointer called with value %d\n", x);
}

void funcPointerDemo()
{
    int (*operation)(int, int);

    int add(int a, int b)
    {
        return a + b;
    }

    operation = add;

    printf("Function pointer addition result: %d\n", operation(5,3));
}
