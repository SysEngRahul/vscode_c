#include<stdio.h>
#define MAX_CAPACITY 20

void printArray(int arr[], int size)
{
    for(int i =0; i<size; i++)
    {
        printf("%d ", arr[i]);

    }
    printf("\n");


}

int main()
{
    int a[MAX_CAPACITY];
    int size = 0;
    int choice,value,pos;

    printf("enter initial number of elements (max %d): ", MAX_CAPACITY);
    scanf("%d", &size);

    if(size < 0 || size > MAX_CAPACITY)
    {
        printf("invalid size!");
        return 1;
    }

    for(int i = 0; i< size; i++)
    {
        printf("a[%d] = " , i);
        scanf("%d", &a[i]);
    }

    printf("\n --- Multiple insertions ----\n");

    while(1)
    {
        printf("\n current array: ");
        printArray(a, size);

        printf("\n1. insert elements\n");
        printf("2. exit\n");
        printf("enter choices: ");
        scanf("%d", &choice);

        if(choice == 2)
            break;
        if(choice != 1)
        {
            printf("invalid choice!\n");
            continue;
        }

        if(size >= MAX_CAPACITY)
        {
            printf("array is  full! cannot insert more\n");
            continue;
        
        }

        printf("enter elements to insert: ");
        scanf("%d" , &value);

        printf("enter position (0 to %d): ", size);
        scanf("%d", &pos);

        if(pos < 0 || pos > size)
        {
            printf("error: invalid position!\n");
            continue;
        }

        for(int i = size -1; i>= pos; i--)
        {
            a[i+1] = a[i];
        }

        a[pos] = value;
        size++;

        printf("element inserted succesfully");

       

        

    }

    printf("final array: ");
    printArray(a,size);

    return 0;
}
