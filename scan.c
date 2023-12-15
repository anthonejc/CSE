#include<stdio.h>
#include<math.h>

void main()
{
    int i,j,n,h,t[20],d[20],c,temp,l,k,total;
    printf("enter the no: of tracks:");
    scanf("%d",&n);
    printf("enter the head:");
    scanf("%d",&h);
    t[0]=0;
    t[1]=h;
    printf("enter the total no: of cylinders:");
    scanf("%d",&c);
    t[2]=c-1;
    n+=3;
    printf("enter the track sequences:");
    for(i=2;i<n;i++)
    {
        scanf("%d  ",&t[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(t[j]>t[j+1])
            {
                temp=t[j];
                t[j]=t[j+1];
                t[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(t[i]==h)
            k=i;
    }
    if((h-t[0])<(t[n]-h))
    {
        l=0;
        for(i=k;i>=0;i--)
        {
            d[l]=t[i];
            l++;
        }
        for(i=k+1;i<n-1;i++)
        {
            d[l]=t[i];
            l++;
        }
    }
    else
    {
        l=0;
        for(i=k;i<n-1;i++)
        {
            d[l]=t[i];
            l++;
        }
        for(i=k-1;i>=0;i--)
        {
            d[l]=t[i];
            l++;
        }
    }
    printf("tracks traversed:");
    for(i=0;i<l-1;i++)
    {
        printf("%d",&d[i]);
    }
    for(i=0;i<l-1;i++)
    {
        total+=abs(t[i]-t[i+1]);
    }
    printf("total head movements:%d",&total);
}
