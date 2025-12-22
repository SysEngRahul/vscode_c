#include<stdio.h>
#include<string.h>
int main()
{
    char binary[65];
    int dec = 0;
    printf("enter a binary number:");
    scanf("%s", binary);
    for(int i=0; binary[i] != '\0'; i++)
    {
        dec = (dec*2) + (binary[i] - '0');
    }

    printf("decimal : %d " , dec);
    return 0;
}