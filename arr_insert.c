#include<stdio.h>
int main()
{
    const int capacity =10;
    int a[capacity] ;
    int size, value,pos;

    printf("enter number of elements(max is 9):");
    scanf("%d", &size);

    if(size < 0 || size >= capacity)
        return 0;
    for(int i = 0; i<size; i++)
    {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    printf("enter element to insert:");
    scanf("%d", &value);

    printf("enter position (0 to %d): ", size);
    scanf("%d", &pos);

    if(pos < 0 || pos > size)
    {
        return 0;
    }

    for(int i = size-1; i>= pos; i--)
        a[i+1] = a[i];
    
    a[pos] = value;
    size++;

    printf("array after insertion:\n");

    for(int i =0; i<size; i++)
        printf("%d\t", a[i]);

    return 0;
}

