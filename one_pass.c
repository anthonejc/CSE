#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    char opcode[20],label[20],operand[20],op[20],code[20],name[20],s[10],symtab[20],symtab2[20],symaddr[20],symaddr2[20],lcs[10],s2[20],m[20],obj1[20],obj2[20],mod1[20],mod2[20];
    int loc,st,len,i,j=0,k=0,prgrmlen;
    FILE *f1,*f2,*f3,*f4,*f5,*f6;
    f1=fopen("input.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("symtab1.txt","w+");
    f4=fopen("symtab2.txt","w+");
    f5=fopen("out.txt","w+");
    f6=fopen("mod.txt","w+");
    fscanf(f1,"%s%s%s",label,opcode,operand);
    
    if(strcmp(opcode,"START")==0)
    {
        strcpy(name,label);
        loc=atoi(operand);
        st=loc;
    }
    
    strcpy(s,"*");
    fscanf(f1,"%s%s%s",label,opcode,operand);
    while (strcmp(opcode,"END")!=0)
    {
        if(strcmp(label,"-")==0)
        {
            fscanf(f2,"%s%s",code,op);
            while(!feof(f2))
            {
                if(strcmp(opcode,code)==0)
                {
                    fprintf(f3,"%s%s",label,s);
                    fprintf(f5,"%s%s",label,op);
                    fprintf(f6,"%s%d",label,loc+1);
                    loc+=3;
                    break;
                }
                fscanf(f2,"%s%s",code,op);
            }
        }
        else
        {
            fscanf(f3,"%s%s",symtab,symaddr);
            while (!feof(f3))
            {
                if(strcmp(label,symtab)==0)
                {
                    sprintf(lcs,"%s",loc);
                    fprintf(f4,"%s%d",label,loc);
                    if(strcmp(opcode,"RESW")==0)
                        loc+=3*(atoi(operand));
                    else if (strcmp(opcode,"BYTE")==0)
                    {
                        len=strlen(operand);
                        for(i=2;i<len-1;i++)
                        {
                            s2[j++]=operand[i];
                        }
                        sprintf(m[k++],"%s",s2);
                        loc+=1;
                    }
                    else if (strcmp(opcode,"WORD")==0)
                    {
                        sprintf(m[k++],"%s",operand);
                        loc+=3;
                    }
                    else if(strcmp(opcode,"RESB")==0)
                        loc+=atoi(operand);
                    break;
                }
                fscanf(f3,"%s%s",symtab,symaddr);
            }
        }
        rewind(f2);
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }

    rewind(f4);
    rewind(f5);

    prgrmlen=loc-st;
    printf("H^%s^00%d^00%d",name,st,prgrmlen);
    printf("T^00%d^00%d",st,prgrmlen);
    fscanf(f5,"%s%s",obj1,obj2);
    while (!feof(f5))
    {
        fscanf(f4,"%s%s",symtab2,symaddr2);
        while(!feof(f4))
        {
            if(strcmp(obj1,symtab2)==0)
            {
                printf("^%s0000",obj2);
                break;
            }
            fscanf(f4,"%s%s",symtab2,symaddr2);
        }
        rewind(f4);
        fscanf(f5,"%s%s",obj1,obj2);
    }
    
    for(i=0;i<k;i++)
        printf("^%s",m[i]);
    rewind(f5);
    rewind(f4);
    fscanf(f5,"%s%s",obj1,obj2);
    while (!feof(f5))
    {
        fscanf(f4,"%s%s",symtab2,symaddr2);
        while(!feof(f4))
        {
            fscanf(f6,"%s%s",mod1,mod2);
            while(!feof(f6))
            {
                if((strcmp(obj1,symtab2)==0)&&(strcmp(symtab2,mod1)))
                {
                    printf("\nT^%s^02",mod2);
                    printf("^%s",lcs);
                    break;
                }
                fscanf(f6,"%s%s",mod1,mod2);
            }
            rewind(f6);
            fscanf(f4,"%s%s",symtab2,symaddr2);
        }
        rewind(f4);
        fscanf(f5,"%s%s",obj1,obj2);
    }
    printf("\nE^00%d\n",st);
}