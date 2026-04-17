#include<stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[],  int low, int high)
{
    int pivot = arr[high];
    int i = low-1;

    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[high]);
    return i+1;
}

/* quick sort recursie function */
void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void printArray(int arr[], int size)
{
    for(int i = 0; i<size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90,88,73};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("original array: ");
    printArray(arr,n);

    quickSort(arr, 0, n-1);

    printf("sorted array: ");
    printArray(arr, n);

    return 0;

}
