//Alim Yanis && Mellal Hodaifa

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef  struct Quad {
	char* Op ;
	char* Op1;
	char* Op2;
	char* T;
	int QC;	
	struct Quad* Suivant;
			} Quad;

void InsertQuad(Quad** ListQuad,char* Op, char* Op1, char* Op2,char* T,int QC)	{

Quad* nouveau = malloc(sizeof(Quad));
Quad* tete = *ListQuad;
Quad* prec;
nouveau->Op = strdup(Op);
nouveau->Op1 = strdup(Op1);
nouveau->Op2 = strdup(Op2);
nouveau->T = strdup(T);
nouveau->QC = QC;
nouveau->Suivant = NULL;

if (tete == NULL ) { *ListQuad = nouveau ;}
else {	while (tete != NULL) {
	prec = tete;
	tete = tete->Suivant;
				}
	prec->Suivant = nouveau;

      }
						}

char* Reverse(char *Cond)		{

char* Temp;

	if(!strcmp(Cond,"BLE")) Temp = strdup("BG"); 
	else if(!strcmp(Cond,"BL")) Temp = strdup("BGE"); 
	else if(!strcmp(Cond,"BE")) Temp = strdup("BNE"); 
	else if(!strcmp(Cond,"BNE")) Temp = strdup("BE");
	else if(!strcmp(Cond,"BGE")) Temp = strdup("BL"); 
	else  Temp = strdup("BLE"); 

		return Temp;

					}

void MaJ(Quad** ListQuad , int QC , int Address)	{

Quad* tete = *ListQuad;
char T[254] = { } ;
	
	while (tete != NULL) {
	if(tete->QC == QC) break;
	else tete = tete->Suivant;
			     }
	sprintf(T,"%d",Address);
	tete->Op1=strdup(T);

							}

void Chainage(Quad** ListQuad,char* indice,int num) 		{

char Valeur[254]={};
Quad* tete = *ListQuad;

   	sprintf(Valeur,"%d",num);
	while(tete != NULL)     {
		if(!strcmp(tete->Op1,indice)) tete->Op1=strdup(Valeur);
		tete = tete->Suivant ;	
				}
								}


void AffichageQuad(Quad* ListQuad) 		{

Quad* tete = ListQuad;
	if (tete == NULL) printf("Pas de quadruplets.\n");
	else {  while(tete != NULL)     {
		printf("\n%d-(%s,%s,%s,%s)\n",tete->QC,tete->Op,tete->Op1,tete->Op2,tete->T);
		tete = tete->Suivant ;	}
	     }
						}

void supprimer(Quad** ListQuad,int QC)	
{
	Quad *p,*prec,*q;
	
	if(*ListQuad!=NULL)
	{
		if((*ListQuad)->QC==QC) //le premier element 
		{ p=*ListQuad;
		  *ListQuad=(*ListQuad)->Suivant;
		  free(p);
		 
		}
		else //les autres 
		{
		  prec= *ListQuad;
		  p=(*ListQuad)->Suivant;
		  while(p!=NULL)
		  { if(p->QC==QC)
		    {
		      prec->Suivant=p->Suivant;
		      free(p);
		      break;
		    }
		    prec=p;
		    p=p->Suivant;
		  }
		  
		}
	}

	
}

void optimiser(Quad** ListQuad)	
{
	
	char* operand=malloc(10);
	char* temp=malloc(10);
	int modif=0;

	Quad* tete = *ListQuad;
	Quad* p=tete;
	while(p!=NULL)
	{
			//le cas ou x=x
			if(strcmp(p->Op,"=")==0 && strcmp(p->Op1,p->T)==0)
			{
				//supprimer le quad
				supprimer(&tete,p->QC);
				
			}
		p=p->Suivant;
	}
	*ListQuad=tete;
}



typedef  struct Pile {
	int Addr;	
	struct Pile* Suivant;
			} Pile;


void Empiler(Pile** P,int Addr)		{

Pile* nouveau = malloc(sizeof(Pile));
Pile* tete = *P;
nouveau->Addr = Addr;
nouveau->Suivant = NULL;

if (tete == NULL ) { *P = nouveau ;}
else {	nouveau->Suivant = *P;
	*P = nouveau;
     }
					}

int Depiler(Pile** P)	{
	int T;
	Pile *tete = *P;
	T = tete->Addr;
	tete = tete->Suivant;
	*P = tete;
	return T;
     	 		}
						



