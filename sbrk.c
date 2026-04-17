#include<stdio.h>
#include<unistd.h>

int main()
{
    void* ptr = sbrk(5 * sizeof(int));
    if(ptr == (void*) -1)
    {
        perror("sbrk");
        return 1;
    }

    int* array = (int*) ptr;

    for(int i = 0; i<5; i++)
    {
        array[i] = i + 1;
    }

    printf("values using sbrk: ");
    for(int  i =0; i< 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}

