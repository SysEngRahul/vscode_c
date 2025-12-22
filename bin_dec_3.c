#include <stdio.h>

int main()
{
    int binary[32];
    int size = 0;
    int decimal = 0;
    int base = 1;
    int num;

    printf("Enter a binary number: ");
    scanf("%d", &num);

    if (num == 0)
    {
        printf("Decimal: 0\n");
        return 0;
    }

    while (num > 0)
    {
        binary[size] = num % 10;   // store last digit
        num = num / 10;
        size++;
    }

    for (int i = 0; i < size; i++)
    {
        decimal = decimal + binary[i] * base;
        base = base * 2;
    }

    printf("Decimal: %d\n", decimal);

    return 0;
}
