#include<stdio.h>
#include<stdbool.h>
 
bool isprime(int n)
{
    if(n<=1)
    {
        return false;
    }
    else if(n==2)
    {
        return true;
    }
    else if(n%2==0)
    {
        return false;
    }
    else
    {
        for(int i =3;i*i<=n;i+=2)
        {
            if(n%i == 0)
            {
                return false;
            }
        }
    }
    return true;
}
 
int main()
{
    int N;
    printf("enter the range: \n");
    scanf("%d",&N);
 
    for(int j=1;j<=N;j++)
    {
        if(isprime(j))
        {
            printf("%d\t",j);
        }
    }
    return 0;
}