#include<stdio.h>
#include<string.h>

struct process{
    char name[50];
    int at,bt,ct,tt,wt,pr;
}p[50],temp;

struct gantt{
    char name[50];
    int ct;
}g[50];

void main()
{
    int i,j,n;
    float avgtt,avgwt;
    printf("enter the no: of process:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter the name of the process:");
        scanf("%s",&p[i].name);
        printf("enter the arrival time:");
        scanf("%d",&p[i].at);
        printf("enter the burst time:");
        scanf("%d",&p[i].bt);
        printf("enter the prioity:");
        scanf("%d",&p[i].pr);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j+1].at<p[j].at)
            {
                temp=p[j];
                p[j+1]=p[j];
                p[j]=temp;
            }
        }
    }
    i=0,j=0;
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
            avgtt+=p[i].tt;
            avgwt+=p[i].wt;
            i++,j++;
            int a,b;
            for(a=i;a<n;a++)
            {
                for(b=i;b<n-a;b++)
                {
                    if((p[b+1].pr<p[b].pr)&&(p[b+1].at<=time))
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
            idle=0;
        }
    }

    printf("\nPROCESS TABLE");
    printf("NAME\tPR\tAT\tBT\tTT\tWT");
    for(i=0;i<n;i++)
    {
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].pr,p[i].at,p[i].bt,p[i].tt,p[i].wt);
    }
    printf("\ngantt chart");
    printf("--------------------------------------------------------------------\n");
    printf("|");
    for(i=0;i<j;i++)
    {
        printf("%s\t|",g[i].name);
    }
    printf("--------------------------------------------------------------------\n");
    for(i=0;i<j;i++)
    {
        printf("\t%d",g[j].ct);
    }

    printf("\naverage turn around time:%f",(avgtt/n));
    printf("\naverage waiting time:%f",(avgwt/n));

}