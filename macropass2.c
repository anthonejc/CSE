#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    FILE *finp,*fnam,*fdef,*farg,*fexp;
    char label[10],opc[10],oprnd[10],name[10],opc1[10],oprnd1[10],arg[10];
    int len,flag=0,i;
    finp = fopen("minp2.txt", "r");
    fnam = fopen("ntab2.txt", "r");
    fdef = fopen("dtab2.txt", "r");
    farg = fopen("atab2.txt", "w+");
    fexp = fopen("op2.txt", "w");
    fscanf(finp,"%s%s%s",label,opc,oprnd);
    while (strcmp(opc,"END")!=0)
    {
        if(strcmp(opc,"MACRO")==0)
        {
            fscanf(finp,"%s%s%s",label,opc,oprnd);
            while(strcmp(opc,"MEND")!=0)
                fscanf(finp,"%s%s%s",label,opc,oprnd);
        }
        else
        {
            rewind(fnam);
            fscanf(fnam,"%s",name);
            while(!feof(fnam))
            {
                if(strcmp(label,name)==0)
                {
                    flag=1;
                    freopen("atab2.txt","w+",farg);
                    len=strlen(oprnd);
                    for(i=0;i<len;i++)
                    {
                        if(oprnd[i]!=",")
                            fprintf(farg,"%c\n",oprnd[i]);
                    }
                    rewind(fnam);
                    rewind(farg);
                    rewind(fdef);
                    while(fscanf(fdef,"%s%s",opc1,oprnd1)!=EOF)
                    {
                        if(strcmp(name,opc1)==0)
                        {
                            fscanf(fdef,"%s%s",opc1,oprnd1);
                            while(strcmp(opc1,"MEND")!=0)
                            {
                                if(oprnd1[0]=="&")
                                {
                                    fscanf(farg, "%s", arg);
                                    fprintf(fexp, "-\t%s\t%s\n", opc1, arg);
                                }
                                else
                                    fprintf(fexp, "-\t%s\t%s\n", opc1, oprnd1);
                                fscanf(fdef,"%s%s",opc1,oprnd1);
                            }
                        }
                        fscanf(fnam,"%s",name);
                    }
                }
                if (flag==0)
                    fprintf(fexp, "%s\t%s\t%s\n", label, opc, oprnd);
                flag=0;
            }
        }
        fscanf(finp,"%s%s%s",label,opc,oprnd);
    }
    fprintf(fexp, "%s\t%s\t%s", label, opc, oprnd);
    fclose(finp);
    fclose(fnam);
    fclose(fdef);
    fclose(farg);
    fclose(fexp);
    printf("Pass 2 is successful\n");
}
