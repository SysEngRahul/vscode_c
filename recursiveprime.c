#include<stdio.h>
#include<stdbool.h>
bool isprimerecursive(int n, int i)
{
    if(n<= 2)
    {
        return (n==2);
    }
    else if(n%i==0)
    {
        return false;
    }
    else if(i*i>n)
    {
        return true;
    }
    else
    {
        return isprimerecursive(n,i+1);
    }

}

int main()
{
    int n;
    printf("enter a  number:");
    scanf("%d",&n);
    if(isprimerecursive(n,2))
    {
        printf("%d\t is a prime number\n",n);
    }
    return 0;
}