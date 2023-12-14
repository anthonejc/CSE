#include<stdio.h>

void main()
{
    int f,p,i,j,frame[50],ref[50],flag,next,pf;
    printf("enter the no:of frames:");
    scanf("%d",&f);
    for (i = 0; i < f; i++)
        frame[i] = -1;
    printf("enter the no:of pages:");
    scanf("%d",&p);
    for (i = 0; i < p; i++)
        {
            printf("enter the pages:");
            scanf("%d",&ref[i]);
        }
    next=0,pf=0;
    for (i = 0; i < p; i++)
    {
        flag=0;
        for(j = 0; j < f; j++)
        {
            if(frame[j]==ref[i])
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            frame[next]=ref[i];
            next=(next+1)%f;
            pf++;
        }
        printf("pageno ->");
        for(j = 0; j < f; j++)
        {
            if(frame[j]!=-1)
            {
                printf("%d  ",frame[j]);
            }
        }
        printf("\n");
    }
    printf("page fault: %d",pf);
}