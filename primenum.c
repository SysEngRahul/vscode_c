#include<stdio.h>
int main()
{
    int n,i;
    printf("enter the number:");
    scanf("%d",&n);
    if(n<=1)
    {
        printf("not prime",n);
    }
    else if(n==2)
    {
        printf("prime number:");
    }
    else if(n%2==0)
    {
        printf("not prime",n);
    }
    else
    {
        for(i =3;i*i<=n;i+=2)
        {
            if(n%i==0)
            {
                printf("not prime",n);
                return 0;
            }
        

             
        }
        printf("prime ",n);
    }
    return 0;
}