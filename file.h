#include <stdlib.h>
#include <stdio.h>
typedef  struct Pipe {
	int info;	
    int cpt;
	struct Pipe* Suivant;
			} Pipe;

int Pipe_Vid(Pipe *List){
   if(List == NULL) {return 1;}
    return 0;
}
void insert(Pipe **List, int val,int cpt){

Pipe* nouveau = malloc(sizeof(Pipe));
nouveau->info=val;
nouveau->cpt=cpt;
nouveau->Suivant=NULL;
if (Pipe_Vid(*List))
{   *List=nouveau;   
}
else{
Pipe* p = *List;
while(p->Suivant!=NULL){

    p=p->Suivant;
}
p->Suivant=nouveau;
}}
int get_sommet(Pipe **List,int val)
{
    if(!Pipe_Vid(*List))
    {
    Pipe *p =*List;
    Pipe *prec=NULL;
    int cpt=-1;
    if(p->info == val)
        {
        cpt=p->cpt;
        *List= p->Suivant;
        free(p);
        return cpt;
        }
    else
    {
      prec = p;
      p=p->Suivant; 
      while(p!=NULL)
    {     
        if(p->info == val)
        {
        cpt=p->cpt;
        prec=p->Suivant;
        return cpt;
        }
        prec=p;
        p=p->Suivant;
    }
        return -1;
     
    }}
    else
    {
        return -1;
    }
    
}
int get_cpt(Pipe *List, int Qc)
{
   Pipe *p=List;
   if(Pipe_Vid(List))
   return -1;
   else
   {
       while(p!=NULL)
       {
           if (p->info == Qc)
                return p->cpt;
           else
                p=p->Suivant;
            
       }
       return -1;
   }
   
   

}