#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>

int main()
{
    void* ptr = mmap(NULL, 5 * sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1,0);

    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }



int* array = (int*) ptr;
for(int i = 0; i< 5; i++)
{
    array[i] = i+1;
}

printf("values using mmap: ");

for(int i = 0; i< 5; i++)
{
    printf("%d ", array[i]);
}

printf("\n");

munmap(ptr, 5 * sizeof(int));
return 0;
}
