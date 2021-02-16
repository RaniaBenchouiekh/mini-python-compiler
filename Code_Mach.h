#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include "file.h"

int comparer(char* chaine1, char* chaine2){
    int err;
    regex_t preg;
    err = regcomp (&preg, chaine2, REG_NOSUB | REG_EXTENDED);
    if (err == 0)
   {
      int match;
      match = regexec (&preg,chaine1, 0, NULL, 0);
      regfree (&preg);
      if (match == 0)
      {
          return 1;
      }else
      {
          return 0;
      }
      
}}
char* jump(char* cond){
    if(!strcmp(cond,"BL")) return "JB" ;
    if(!strcmp(cond,"BLE")) return "JBE" ;
    if(!strcmp(cond,"BG")) return "JA" ;
    if(!strcmp(cond,"BGE")) return "JAE" ;
    if(!strcmp(cond,"BNE")) return "JNZ" ;
    if(!strcmp(cond,"BE")) return "JZ" ;
    if(!strcmp(cond,"BR")) return "JMP" ;

}
void GenCode(Quad *Qdr,hash_ele* tab[]){
    int QC=0;
    int cpt=1;
    int rec_cpt;
    int jmp=-1;
    Pipe *List=NULL;
    char intr[254] = { } ;
    Quad *p=Qdr;
    FILE *f=NULL;
    f=fopen("Code_Mach.txt","w");
    fprintf(f,"Title code_Mach.as: Generation Code Machine\n");
    fprintf(f,"Pile Segement Stack;\n");
    fprintf(f,"     dw 100 dup(?)\n");
    fprintf(f,"Pile ends\n");
    fprintf(f,"DATA Segment\n");
    for (int i = 0; i < 511; ++i)
	{
		if (tab[i]!=NULL)
        fprintf(f,"     %s dw ?\n",tab[i]->name);
	}
    fprintf(f,"DATA ends\n");
    fprintf(f," MAIN:\n");
    fprintf(f,"         Assume CS:CODE,DS:DATA\n");
    fprintf(f,"         MOV AX,DATA\n");
    fprintf(f,"         MOV DS,AX\n");
    fprintf(f,"BEGIN: ;Debut du programme\n");
    if(f!=NULL)
        {
            while (p!=NULL){

                if (!strcmp(p->Op,"+"))
                {   jmp=get_sommet(&List,p->QC);
                    if(jmp!=-1){
                        printf("QC=%d\n",p->QC);
                        sprintf(intr,"Etiq%d",jmp);
                        fprintf(f,"%s:\n",intr);
                    }
// ************************** Addition *************************************************************************
                    //Le cas d'une opération d'adition: 
                    if (!comparer(p->Op1,"T[:digit:]*"))
                    { //Le cas ou les deux opérandes sont des variable/nombres
                        fprintf(f,"         MOV AX %s\n",p->Op1);
                        fprintf(f,"         MOV BX %s\n",p->Op2);
                        fprintf(f,"         ADD AX BX\n");
                        fprintf(f,"         PUSH AX\n");
                    }
                    else
                    { //Le cas ou Le premier opérande est un temporaire et le deuxième est une variable/nombre
                         if (!comparer(p->Op2,"T[:digit:]*"))
                         {
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         MOV BX %s\n",p->Op2);
                            fprintf(f,"         ADD AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                         }
                         else
                         { // Le cas ou les deux opérandes sont des temporaires 
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         POP BX\n");
                            fprintf(f,"         ADD AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                             
                         }
                         
                    }
                    
                    
                }else
                {
//******************** Affectation *****************************************************************************
                    if (!strcmp(p->Op,"="))
                    {
                       jmp=get_sommet(&List,p->QC);
                        if(jmp!=-1){
                        sprintf(intr,"Etiq%d",jmp);
                        fprintf(f,"%s:\n",intr);
                        }
                        if(comparer(p->Op1,"T[:digit:]*"))
                        {
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         MOV %s AX\n",p->T);
                        }else
                        {
                            fprintf(f,"         MOV AX %s\n",p->Op1);
                            fprintf(f,"         MOV %s AX\n",p->T);
                        }
                        
                    }else
                    {

// *********************MILTIPLICATION********************************************************************
                        if (!strcmp(p->Op,"*"))
                {
                        jmp=get_sommet(&List,p->QC);
                        if(jmp!=-1){
                            sprintf(intr,"Etiq%d",jmp);
                            fprintf(f,"%s:\n",intr);
                        }
                    if (!comparer(p->Op1,"T[:digit:]*"))
                    { //Le cas ou les deux opérandes sont des variable/nombres
                        fprintf(f,"         MOV AX %s\n",p->Op1);
                        fprintf(f,"         MOV BX %s\n",p->Op2);
                        fprintf(f,"         MUL AX BX\n");
                        fprintf(f,"         PUSH AX\n");
                    }
                    else
                    { //Le cas ou Le premier opérande est un temporaire et le deuxième est une variable/nombre
                         if (!comparer(p->Op2,"T[:digit:]*"))
                         {
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         MOV BX %s\n",p->Op2);
                            fprintf(f,"         MUL AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                         }
                         else
                         { // Le cas ou les deux opérandes sont des temporaires 
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         POP BX\n");
                            fprintf(f,"         MUL AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                             
                         }
                         
                    }
                    
                    
                }else
//**************************************Soustraction***********************************************************
                { if(!strcmp(p->Op,"-"))
                {
                    jmp=get_sommet(&List,p->QC);
                    if(jmp!=-1){
                        sprintf(intr,"Etiq%d",jmp);
                        fprintf(f,"%s:\n",intr);
                    }
                    if (!comparer(p->Op1,"T[:digit:]*"))
                    { //Le cas ou les deux opérandes sont des variable/nombres
                        fprintf(f,"         MOV AX %s\n",p->Op1);
                        fprintf(f,"         MOV BX %s\n",p->Op2);
                        fprintf(f,"         SUB AX BX\n");
                        fprintf(f,"         PUSH AX\n");
                    }
                    else
                    { //Le cas ou Le premier opérande est un temporaire et le deuxième est une variable/nombre
                         if (!comparer(p->Op2,"T[:digit:]*"))
                         {
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         MOV BX %s\n",p->Op2);
                            fprintf(f,"         SUB AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                         }
                         else
                         { // Le cas ou les deux opérandes sont des temporaires 
                            fprintf(f,"         POP BX\n");
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         SUB AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                             
                         }
                         
                    }

                }else
                {
    // *************************** Division **********************************************************
                    if (!strcmp(p->Op,"/"))
                    {
                        jmp=get_sommet(&List,p->QC);
                        if(jmp!=-1){
                            sprintf(intr,"Etiq%d",jmp);
                            fprintf(f,"%s:\n",intr);
                        }
                        if (!comparer(p->Op1,"T[:digit:]*"))
                    { //Le cas ou les deux opérandes sont des variable/nombres
                        fprintf(f,"         MOV AX %s\n",p->Op1);
                        fprintf(f,"         MOV BX %s\n",p->Op2);
                        fprintf(f,"         DIV AX BX\n");
                        fprintf(f,"         PUSH AX\n");
                    }
                    else
                    { //Le cas ou Le premier opérande est un temporaire et le deuxième est une variable/nombre
                         if (!comparer(p->Op2,"T[:digit:]*"))
                         {
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         MOV BX %s\n",p->Op2);
                            fprintf(f,"         DIV AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                         }
                         else
                         { // Le cas ou les deux opérandes sont des temporaires 
                            fprintf(f,"         POP BX\n");
                            fprintf(f,"         POP AX\n");
                            fprintf(f,"         DIV AX BX\n");
                            fprintf(f,"         PUSH AX\n");
                             
                         }
                         
                    }
                    }else
// *********************** Saut *****************************************************************************
                    {  
                        jmp=get_sommet(&List,p->QC);
                        if(jmp!=-1){
                            sprintf(intr,"Etiq%d",jmp);
                            fprintf(f,"%s:\n",intr);
                        } 
                        fprintf(f,"         POP CX\n");
                        fprintf(f,"         CMP CX,0\n");
                        rec_cpt=get_cpt(List,atoi(p->Op1));
                        if(rec_cpt!=-1)
                        {     
                            sprintf(intr,"Etiq%d",rec_cpt);
                            fprintf(f,"         %s %s: \n",jump(p->Op),intr);

                        }else
                        {
                            sprintf(intr,"Etiq%d",cpt);
                            fprintf(f,"         %s %s: \n",jump(p->Op),intr);
                            insert(&List,atoi(p->Op1),cpt);
                            cpt++;
                        }
                        

                        } 
                    
                    
                }
                
                    
                }
                
                    }
                    
                    
                }
              
            p=p->Suivant;
            QC++;
            }
            jmp=get_sommet(&List,QC);
                    if(jmp!=-1){
                        printf("QC=%d\n",QC);
                        sprintf(intr,"Etiq%d",jmp);
                        fprintf(f,"%s:\n",intr);
                    }
            fprintf(f,"     MAIN ENDS\n");
            fprintf(f,"         END MAIN\n");    
            fclose(f);
        }else
    {
        printf("Impossible d'ouvrir le fichier \n");
    }
    
        
    }




