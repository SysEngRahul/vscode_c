#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for an array of 5 integers
    int* ptr = (int*)malloc(5 * sizeof(int));
    if (ptr == NULL) {
        perror("malloc");
        return 1;
    }
    
    // Initialize array elements
    for (int i = 0; i < 5; i++) {
        ptr[i] = i * 10;
    }
    
    // Print array elements
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
    }
    
    // Free allocated memory
    free(ptr);
    
    return 0;
}

