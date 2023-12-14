#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	FILE *f1,*f2,*f3,*f4;
	int len,len1,i;
	char opcode[20],label[20],operand[20],start[20],symaddr[20],symtab[20],code[20],op[20];
	f1=fopen("inter.txt","r");
    f2=fopen("optab.txt","r");
	f3=fopen("symtab.txt","r");
	f4=fopen("len.txt","r");
    fscanf(f1,"%s\t%S\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        strcpy(start,operand);
        fscanf(f4,"%d",&len);
    }
    printf("H^%s^00%s^00%d",label,start,len);
    printf("T^00%s^00%d",start,len);
    fscanf(f1,"%s\t%S\t%s",label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        fscanf(f2,"%s\t%s",code,op);
        while (!feof(f2))
        {
            if(strcmp(opcode,code)==0)
            {
                rewind(f2);
                fscanf(f3,"%s\t%s",symtab,symaddr);
                while(!feof(f3))
                {
                    if(strcmp(operand,symtab)==0)
                    {
                        //rewind(f3);
                        printf("^%s%s",op,symaddr);
                        break;
                    }
                    fscanf(f3,"%s\t%s",symtab,symaddr);
                }
                break;
            }
            rewind(f3);
            fscanf(f2,"%s\t%s",code,op);
        }
        if(strcmp(opcode,"WORD")==0)
            printf("^00000%s",operand);
        else if(strcmp(opcode,"BYTE")==0)
        {
            len1=strlen(operand);
            printf("^");
            for(i=2;i<len1-1;i++)
                printf("%c",operand[i]);
        }
        fscanf(f1,"%s\t%S\t%s",label,opcode,operand);
    }
    printf("E^%s",start);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
}