
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Read true random bytes from /dev/urandom
unsigned char get_random_byte() {
    unsigned char byte;
    FILE *fp = fopen("/dev/urandom", "rb");
    fread(&byte, 1, 1, fp);
    fclose(fp);
    return byte;
}

// Shuffle (Fisher–Yates)
void shuffle(char *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = get_random_byte() % (i + 1);
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    int choice, length;

    printf("==========================================\n");
    printf("      ADVANCED PASSWORD GENERATOR (C)\n");
    printf("==========================================\n");
    printf("1) Safe Password (no confusing characters)\n");
    printf("2) Strong Password (must include U/L/N/S)\n");
    printf("==========================================\n");

    printf("Choose option (1 or 2): ");
    scanf("%d", &choice);

    printf("Enter password length: ");
    scanf("%d", &length);

    if (length < 4) {
        printf("Length must be at least 4.\n");
        return 1;
    }

    char password[length + 1];

    // CHARSETS
    const char *safe_charset =
        "ABCDEFGHJKLMNPQRSTUVWXYZ"
        "abcdefghijkmnopqrstuvwxyz"
        "23456789!@#$%^&*+=_-";

    const char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *lower = "abcdefghijklmnopqrstuvwxyz";
    const char *digits = "0123456789";
    const char *symbols = "!@#$%^&*()_+=<>?{}[]~";

    // OPTION 1: SAFE PASSWORD
    if (choice == 1) {
        int n = strlen(safe_charset);
        for (int i = 0; i < length; i++) {
            password[i] = safe_charset[get_random_byte() % n];
        }
        password[length] = '\0';

        printf("------------------------------------------\n");
        printf("Safe Password:\n%s\n", password);
        printf("------------------------------------------\n");
        return 0;
    }

    // OPTION 2: STRONG PASSWORD
    if (choice == 2) {

        // Ensure min requirements
        password[0] = upper[get_random_byte() % strlen(upper)];
        password[1] = lower[get_random_byte() % strlen(lower)];
        password[2] = digits[get_random_byte() % strlen(digits)];
        password[3] = symbols[get_random_byte() % strlen(symbols)];

        // Fill remaining with mixed charset
        char mixed[300];
        sprintf(mixed, "%s%s%s%s", upper, lower, digits, symbols);

        int mixed_len = strlen(mixed);

        for (int i = 4; i < length; i++) {
            password[i] = mixed[get_random_byte() % mixed_len];
        }

        password[length] = '\0';

        // Shuffle for randomness
        shuffle(password, length);

        printf("------------------------------------------\n");
        printf("Strong Password:\n%s\n", password);
        printf("------------------------------------------\n");
        return 0;
    }

    // INVALID SELECTION
    printf("Invalid choice. Select 1 or 2.\n");
    return 1;
}
