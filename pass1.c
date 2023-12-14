#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
    char label[10],opcode[10],operand[10],code[10],mne[10];
    int locctr,start;
    FILE *f1,*f2,*f3,*f4,*f5;
    f1=open("input.txt","r");
    f2=open("optab.txt","r");
    f3=open("symtab.txt","w");
    f4=open("inter.txt","w");
    f5=open("length.txt","w");
    fscanf(f1,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        locctr=start;
    }
    else
        locctr=0;
    fprintf(f4,"**\t%s\t%s\t%s\n",label,opcode,operand);
    fscanf(f1,"%s%s%s",label,opcode,operand);
    while (strcmp(opcode,"END")!=0)
    {
        fprintf(f4,"%d\t",locctr);
        if(strcmp(label,"**")!=0)
            fprintf(f3,"%s\t%d\n",label,locctr);
        fscanf(f2,"%s%s",code,mne);
        while(!feof(f2))
        {
            if(strcmp(code,opcode)==0)
            {   
                locctr+=3;
                break;
            }
            fscanf(f2,"%s%s",code,mne);
        }
        if(strcmp(opcode,"WORD")==0)
            locctr+=3;
        else if (strcmp(opcode,"RESW")==0)
            locctr+=3*(atoi(operand));
        else if (strcmp(opcode,"RESB")==0)
            locctr+=atoi(operand);
        else if (strcmp(opcode,"BYTE")==0)
        {
            if(operand[0]=='C')
                locctr+=(strlen(operand)-3);
            else
                locctr+=1;
        }
        fprintf(f4,"%s\t%s\t%s\n",label,opcode,operand);   
        fscanf(f1,"%s%s%s",label,opcode,operand);
    }
    fprintf(f4,"%d\t%s\t%s\n",locctr,label,opcode);
    fprintf(f5,"%d",(locctr-start));
    printf("length is: %d",(locctr-start));
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}