#include<stdio.h>
#include<string.h>

struct process{
    char name[50];
    int at,bt,ct,tt,wt;
}p[50];
int temp;

struct gantt{
    char name[50];
    int ct;
}g[50];

void main()
{
    int n,i,j,k;
    float avgtt=0,avgwt=0;
    printf("enter the no: of process:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter p name:");
        scanf("%s",&p[i].name);
        printf("enter the at:");
        scanf("%d",&p[i].at);
        printf("enter the bt:");
        scanf("%d",&p[i].bt);
    }
    printf("PROCESS\n");
    printf("PID\tARRIVAL TIME\t\tBURST TIME");
    for(i=0;i<n;i++)
    {
        printf("\n%s\t%d\t%d",p[i].name,p[i].at,p[i].bt);
    }
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if (p[j].at>p[j+1].at)
            {
                temp=p[j].at;
                p[j].at=p[j+1].at;
                p[j+1].at=temp;
            }
        }
    }
    i=0,j=0,k=0;
    int idle=0,time=0;
    while (i<n)
    {
        if(p[i].at<=time)
        {
            strcpy(g[j].name,p[i].name);
            p[i].ct=time+p[i].bt;
            g[j].ct=p[i].ct;
            time=p[i].ct;
            p[i].tt=p[i].ct-p[i].at;
            p[i].wt=p[i].tt-p[i].bt;
            avgtt+=p[i].tt;
            avgwt+=p[i].wt;
            i++;
            j++;
        }
        else if(p[i].at>time)
        {
            strcpy(g[j].name,"idle");
            g[j].ct=p[i].at;
            time=p[i].at;
            j++;
        }
        
    }
    
    printf("\nROCESS TABLE\n");
    printf("NAME\tAT\tBT\tTT\tWT");
    for(i=0;i<n;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d",p[i].name,p[i].at,p[i].bt,p[i].tt,p[i].wt);
    }
    printf("\ngantt chart");
    printf("-------------------------------------------------------------------\n");
    printf("|");
    for(i=0;i<j;i++)
    {
        printf("%s\t|",g[i].name);
    }
    printf("\n-------------------------------------------------------------------\n");
    printf("0");
    for(i=0;i<j;i++)
    {
        printf("\t%d",g[i].ct);
    }
    printf("\naverage turn around time:%f",(avgtt/n));
    printf("\naverage waiting time:%f",(avgwt/n));
}
