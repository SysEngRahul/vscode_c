#include<stdio.h>
int main()
{
    long long binary;
    int dec =0;
    int base=1, rem;
    printf("enter a binary number:");
    scanf("%lld",&binary);

    while(binary > 0)
    {
        rem = binary % 10;
        dec += rem * base;
        binary /= 10;
        base *=2;

    }
    printf("decimal : %d\n", dec);
    return 0;
    

}