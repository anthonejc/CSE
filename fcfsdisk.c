#include<stdio.h>

void main()
{
    int i,j,n,t[20],h,total;
    printf("enter the no: of tracks:");
    scanf("%d",&n);
    printf("enter the head:");
    scanf("%d",&h);
    t[0]=h;
    n+=1;
    printf("enter the sequence:");
    for(i=1;i<n;i++)
    {
        scanf("%d",&t[i]);
    }
    for(i=0;i<n;i++)
    {
        total+=abs(t[i]-t[i+1]);
    }
    
    printf("%d",&h);
    for(i=0;i<n;i++)
    {
        printf("%d",t[i]);
    }
    printf("total head movement:%d",total);
}
