/* write a c code to insert an element at any given position in an array? */

#include<stdio.h>
#include<stdlib.h>

void printArray(int arr[], int size)
{
    for(int i = 0; i< size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int *a = NULL;
    int size = 0;
    int capacity = 0;
    int value,pos;

    printf("enter number of elements: ");
    scanf("%d", &size);

    if(size < 0)
    {
        printf("invalid size!\n");
        return 0;
    }

    capacity = size + 5;
    a = (int*)malloc(capacity * sizeof(int));

    if(a == NULL)
    {
        printf("memory allocation failed:\n");
        return 1;
    }

    for(int i = 0; i<size; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("enter element to insert: ");
    scanf("%d", &value);

    if(pos < 0 || pos > size)
    {
        printf("error: invalid position!\n");
        free(a);
        return 1;
    }

    if(size >= capacity)
    {
        capacity *= 2;
        int *temp = (int*)realloc(a, capacity * sizeof(int));
        if(temp == NULL)
        {
            printf("memory reallocation failed:\n");
            free(a);
            return 1;
        }

        a = temp;
    }

    //shift elements to right
    for(int i = size-1; i>= pos; i--)
    {
        a[i+1] = a[i];
    }

    a[pos] = value;
    size++;

    printf("array after insertion: ");
    printArray(a,size);

    free(a);
    return 0;
}

