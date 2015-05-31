#include <stdio.h>
#include <stdlib.h>

void set(int a[],int s,int n);
int main(void)
{
    int n;
    int *p;
    printf("要全排的数的个数为:");
    scanf("%d",&n);
    printf("请输入%d个不同的数进行全排列（eg:1 2 3）:",n);   
    p=new int [n];
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);
    printf("输入的%d个数为:",n);
    for(int j=0;j<n;j++)
        printf("%d  ",p[j]);
    putchar('\n');

    printf("全排列为:\n");
    set(p,0,n);

    return 0;
}

void set(int p[],int s,int n)
{
    int i,temp;
    if(s==n-1)
    {
        for(i=0;i<n;i++)
            printf("%d  ",p[i]);
        putchar('\n');
    }
    else
    {
        for(i=s;i<n;i++)
        {
            temp=p[s];
            p[s]=p[i];
            p[i]=temp;
            set(p,s+1,n);
            temp=p[s];
            p[s]=p[i];
            p[i]=temp;
        }
    }
} 
