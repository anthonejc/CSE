#include<stdio.h>
#include<string.h>
struct process{
    char name[50];
    int at,bt,ct,tt,wt;
}p[50],temp;

struct gantt{
    char name[50];
    int st,ct;
}g[50];

void main()
{
    int n,i,j,k;
    float avgtt=0,avgwt=0;
    printf("enter the no: of process: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter the process name:");
        scanf("%s",&p[i].name);
        printf("enter the arrival time:");
        scanf("%d",&p[i].at);
        printf("enter the burst time:");
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
            if(p[j].at>p[j+1].at)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    i=0;j=0;
    int time=0,idle=0;
    while(i<n)
    {
        if(p[i].at<=time)
        {
            if(idle==1)
            {
                strcpy(g[j].name,"idle");
                g[j].ct=time;
                j++;
                idle=0;
            }
            strcpy(g[j].name,p[i].name);
            time+=p[i].bt;
            p[i].ct=time;
            g[j].ct=p[i].ct;
            p[i].tt=p[i].ct-p[i].at;
            p[i].wt=p[i].tt-p[i].bt;
            i++,j++;
            int a,b;
            for(a=i;a<n;a++)
            {
                for(b=i;b<n-i;b++)
                {
                    if((p[b+1].bt<p[b].bt)&&(p[b+1].bt<=time))
                    {
                        temp=p[b];
                        p[b]=p[b+1];
                        p[b+1]=temp;
                    }
                }
            }
        }
        else
        {
            time++;
            idle=1;
        }
    }
    printf("\nPROCESS TABLE");
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
    printf("-------------------------------------------------------------------\n");
    for(i=0;i<j;i++)
    {
        printf("\t\t%d",g[i].ct);
    }
    printf("\naverage turn around time:%f",(avgtt/n));
    printf("\naverage waiting time:%f",(avgwt/n));

}
