#include<stdio.h>
int main()
{
    int num, count =0;
    int started = 0;
    printf("enter a number: ");
    scanf("%d",&num);
    printf("binary representation:");
    for(int i = ((sizeof(int)*8)-1); i>=0; i--)
    {
        int bit = (num>>i) & 1;
        if(bit ==1)
        {
            started =1;
        }
        if(started)
        {
            printf("%d\t",bit);
            if(bit ==1)
            {
                count++;
            }
        }
    }
    if(!started)
    {
        printf("0");
    }
    printf("no of 1's is: %d", count);
    return 0;
}