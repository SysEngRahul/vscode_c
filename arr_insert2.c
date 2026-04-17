#include<stdio.h>

#define MAX_CAPACITY 10

void printArray(int arr[], int size)
{
    for(int i = 0; i<size; i++)
    {
        printf("%d " , arr[i]);
    }
    printf("\n");
}

int main()
{
    int a[MAX_CAPACITY];
    int size, value, pos;

    printf("ENTER NUMBER OF ELEMENTS(max %d): ", MAX_CAPACITY -1);
    scanf("%d", &size);

    if(size < 0 || size >= MAX_CAPACITY)
    {
        printf("error: size must be between 0 and %d\n", MAX_CAPACITY -1);
        return 1;
    }

    for(int i = 0; i< size; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);

    }

    printf("enter element to insert; ");
    scanf("%d" , &value);

    printf("enter position (0 to %d); ", size);
    scanf("%d", &value);

    if(pos < 0 || pos > size)
    {
        printf("error: Invalid position!\n");
        return 1;
    }

    if(size >= MAX_CAPACITY)
    {
        printf("error: array is full! cannot insert more elements\n");
        return 1;

    }

    for(int i = size -1 ; i>= pos; i--)
    {
        a[i+1]  = a[i];
    }

    a[pos] = value;
    size++;

    printf("array after insertion:\n");
    printArray(a, size);

    return 0;




}
