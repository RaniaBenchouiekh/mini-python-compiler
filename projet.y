%{

//______PRE-CODE C_____________________________________________________________________________________________________________________

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Hash.h"
#include "Quad.h"
#include "Code_Mach.h"
extern FILE* yyin;
extern int numL,numC; 
extern char *yytext;
extern int yyleng ;
extern int Ind;

int yylex();
char *T;
int Prog_Ind=0,Pred_Ind=0, QC=0,cpt=1, First=0 ;
int yyerror(char *);
Quad* Qdr=NULL;
char Valeur[254] = { } ;


int existe; // pour verifier l'existance ou pas des idfs dans la ts
int t,taff,tidf,nat; //t: type idf, taff : type coté gauche d'une affectation, tidf: type coté droit d'une affectation, nat: nature idf 
//int no_comp; //pour le cas : variable = valeur ==> non compatibilité
hash_ele *tab[511]; // la table des symboles 
char *buf; //zone de texte d'un token

%}

//______DECLARATIONS DES UNITES LEXICALES_____________________________________________________________________________________________

%union
{ char *chaine;
  int entier;
  float reel;
  struct 	{
int Prog_Ind;
int Pred_Ind;	
	} IF_Save;
  struct 	{
int Type;
char* Valeur;	
	} TV;
}

%token IDF INT FLOAT CHAR t_int t_float t_char SAUT
%token ADD SOUS DIV MULT
%token SUP SUPEG INF INFEG EGAL DEGAL DIFF
%token ET OU 
%token IF ELIF ELSE FOR INRANGE WHILE 

%type <chaine> IDF CHAR t_int t_float t_char FOR INRANGE WHILE SAUT
%type <chaine> ADD SOUS DIV MULT SUP SUPEG INF INFEG EGAL DEGAL DIFF ET OU 
%type <entier>  D INT
%type <chaine> opL
%type <chaine> E T F NB val 
%type <reel> FLOAT
%type <IF_Save> IF ELSE ELIF
%left ET 
%left OU
%left SUPEG DEGAL DIFF INFEG INF
%left ADD SOUS
%left MULT DIV

%start S

%%
//_______GRAMMAIRE LALR_____________________________________________________________________________________________________________

S: 		prgm_syntx { printf("\n\nFin du programme\n"); YYACCEPT;}; 

prgm_syntx: rec 
		| rec prgm_syntx;


rec: 	{if(First){
				if(Prog_Ind >= Ind)
					{ printf("Erreur d'indentation\n");
					  return(0);
					}
				Prog_Ind=Ind;
				First=0;
					}
			else
			if(Prog_Ind !=Ind)
			{ if(Pred_Ind == Ind)
			  {return 1;}
			  else{
			  printf("Error d'indentation\n");
			  return(0);}
			}
			
			}Dec '\n' 
		|  {if(First){
				if(Prog_Ind >= Ind)
					{ 
					  return(0);
					}
				Prog_Ind=Ind;
				First=0;
					}
			else
			if(Prog_Ind !=Ind)
			{ 
			  printf("Error d'indentation\n");
			  return(0);
			}
			
			} Cond '\n' ;

Dec: 	  Dec1  
		| Dec2 
		| Dec3 ;


Dec1: 		type liste_simple;


liste_simple: 	IDF {   //verifier l existance de l'identificateur dans la ts
			existe=recherche_element(tab,$1); 
			//si l'idf n'existe pas, on l'insere dans la table (variable simple :4, de taille :1)
			if(existe==0)
			{ inserer(tab,$1,t,4,1); }
			//si l'idCf existe deja dans la ts 
			else 
			{printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Double déclaration\n Entité : %s, Ligne : %d, Colonne :%d \n_______________________________________________\n\n"
			         ,$1,numL-1,numC-yyleng+1);return 1;}
      		    }

		| liste_simple ',' IDF 
			{ //verifier l existance de l'identificateur dans la ts
			  existe=recherche_element(tab,$3); 
			  //si l'idf n'existe pas, on l'insere dans la table (variable simple:4, de taille :1)
			  if(existe==0) { inserer(tab,$3,t,4,1);}
			  //si l'idf existe deja dans la ts 
			  else 
			  {printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Double déclaration\nEntité : %s, Ligne : %d, Colonne :%d \n_______________________________________________\n"
			   ,$3,numL,numC-yyleng+1);return 1;}
		        };


type: 		t_int     {t=1; /*type "int"*/}
		| t_float {t=2; /*type "float"*/}
		| t_char  {t=3; /*type "char"*/} ;


Dec2: 		Aff 
		| Dec2 ',' Aff;


val: 		INT 	{ sprintf(Valeur,"%d",$1); $$ = strdup(Valeur);
					 if(taff!=1 && taff!=0) //if(no_comp==0 && taff!=1)
		     	  { sprintf(buf,"%d",$1);
			    printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Incompatibilité de types.\nEntité: %s, Ligne: %d, Colonne: %d \n_______________________________________________\n\n",buf,numL,numC-yyleng+1);return 1;}}

		| FLOAT { if(taff!=2 && taff!=0) //if(no_comp==0 && taff!=2)
		          {sprintf(buf,"%f",$1);
			   printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Incompatibilité de types.\nEntité: %s, Ligne: %d, Colonne: %d \n_______________________________________________\n\n",buf,numL,numC-yyleng+1);return 1;}}

		| CHAR { if(taff!=3 && taff!=0)  //if(no_comp==0 && taff!=3)
		         printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Incompatibilité de types.\nEntité: %s, Ligne: %d, Colonne: %d \n_______________________________________________\n\n",$1,numL,numC-yyleng+1);return 1;};


Dec3: 		type IDF '[' INT ']'
			{ //verifier l existance de l'identificateur dans la ts
			  existe=recherche_element(tab,$2); 
			  //si l'idf n'existe pas, on l'insere dans la table (tableau : 6 de taille :$4)
			  if(existe==0) 
			  { inserer(tab,$2,t,6,$4);}
			  //si l'idf existe deja dans la ts 
			  else 
			  {printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Variable existante\n Entité : %s, Ligne : %d, Colonne :%d \n_______________________________________________\n\n"
			   ,$2,numL,numC-yyleng+1);return 1;}
			} ; 


Aff : 		IDF      { //verifier l existance de l'identificateur dans la ts
			  existe=recherche_element(tab,$1); 
			  //si l'idf n'existe pas, on l'insere dans la table (variable simple:4 de taille :1)
			  if(existe==0) 
			  { //no_comp=1; // le cas où l'idf n'est pas deja declaré, on ne compte pas la compatibilité des types 
		 	    //on insere l idf dans la ts, on le note I
			   inserer(tab,$1,0,5,1);}
			   else{ taff=get_type(tab,$1);}} 
			   EGAL E { T=strdup($1); 
      	       			InsertQuad(&Qdr,$3,$4," ",T,QC);	
      	     		    QC++; 
					  } ;  


E : 		E ADD T {
						sprintf(Valeur,"T%d",cpt); T = strdup(Valeur); 
						InsertQuad(&Qdr,$2,$1,$3,T,QC); $$ = strdup(T);
						cpt++; QC++;     
					}
		| E SOUS T { sprintf(Valeur,"T%d",cpt); T = strdup(Valeur); 
			     InsertQuad(&Qdr,$2,$1,$3,T,QC);$$ = strdup(T);
			     cpt++; QC++;}
		| T {$$=strdup($1);};


T : 		T MULT F {sprintf(Valeur,"T%d",cpt); T = strdup(Valeur); 
			     InsertQuad(&Qdr,$2,$1,$3,T,QC);$$ = strdup(T);
			     cpt++; QC++;}
		| T DIV F  {sprintf(Valeur,"T%d",cpt); T = strdup(Valeur); 
						InsertQuad(&Qdr,$2,$1,$3,T,QC); $$ = strdup(T);
						cpt++; QC++;    }
		| F {$$=strdup($1);};


F :		'(' E ')' {$$=strdup($2);}   
		| NB {$$=strdup($1);};


NB : 		val { $$=strdup($1); }
		| IDF { //verifier l existance de l'identificateur dans la ts
			existe=recherche_element(tab,$1); 
			//si l'idf n'existe pas, on signale une erreur 
			if(existe==0) 
			{ printf("\n_______________________________________________\nType d'erreur: Erreur sémantique \nMessage d'erreur: Variable inexistante\n Entité : %s, Ligne : %d, Colonne :%d \n_______________________________________________\n\n"
			  ,$1,numL,numC-yyleng+1);return 1;}
			//si l'idf existe deja dans la ts, on recupere son type pour la verification de compatibilté de types 
                        else 
			{ tidf=get_type(tab,$1);
				$$=strdup($1);
			  //on met a jour le type de I *********************************** pblm de recuperation de nom
			
			}	
      		      };

Cond:  IF '(' D ')' ':' '\n'
{ First=1;$1.Pred_Ind=Pred_Ind; Pred_Ind=Prog_Ind; $1.Prog_Ind= Prog_Ind;}
 prgm_syntx 
 		{	 
		InsertQuad(&Qdr,"BR","","","",QC);
		QC++;	
		MaJ(&Qdr,$3,QC);
		$3=QC-1;
		Pred_Ind=$1.Pred_Ind;
		Prog_Ind=$1.Prog_Ind;
		} 
										 Cond2
										 {MaJ(&Qdr,$3,QC);};
Cond2: {if(Prog_Ind !=Ind) {printf("Erreur d'indentation\n"); exit(0);}}ELIF '(' D ')' ':' '\n' { First=1;$2.Pred_Ind=Pred_Ind; Pred_Ind=Prog_Ind; $2.Prog_Ind= Prog_Ind;}
  prgm_syntx  
  { 									  InsertQuad(&Qdr,"BR","","","",QC);
										  QC++;	
										  MaJ(&Qdr,$4,QC);
										  $4=QC-1;
										  Pred_Ind=$2.Pred_Ind;
										  Prog_Ind=$2.Prog_Ind; } Cond2 {MaJ(&Qdr,$4,QC);
										  }  | Cond3  ;
Cond3: {if(Prog_Ind !=Ind) {printf("Erreur d'indentation\n"); exit(0);}}ELSE ':' '\n' 
{ First=1;$2.Pred_Ind=Pred_Ind; Pred_Ind=Prog_Ind; $2.Prog_Ind= Prog_Ind;}
  prgm_syntx {Pred_Ind=$2.Pred_Ind;Prog_Ind=$2.Prog_Ind;} | ;
 

D : 		E opL E { sprintf(Valeur,"T%d",cpt);T = strdup(Valeur);
					  InsertQuad(&Qdr,"-",$1,$3,T,QC);
					  QC++;
					  InsertQuad(&Qdr,$2," "," ",T,QC);
					  $$=QC;
					  QC++;
					  cpt++;
					  

					};


opL : 		SUPEG {$$=strdup("BL"); }
    		| SUP  {$$=strdup("BLE");} 
    		| INFEG {$$=strdup("BG"); }
    		| INF {$$=strdup("BGE");} 
    		| DEGAL {$$=strdup("BNE");}
    		| DIFF {$$=strdup("BE"); };





%%

//_____POST-CODE C_____________________________________________________________________________________________________________________



int yyerror(char* msg)
{
  printf("Type : Erreur Syntaxique, Entite : \"%s\", Ligne: %d, Colonne: %d\n",yytext,numL,numC-yyleng+1);
  return 1;
}

int main()
{
	
	existe=0;
        buf = malloc(20);
	t=0,nat=0,tidf=0,taff=0;
	//no_comp=0;
 	for (int i = 0; i < 511; ++i) tab[i]=NULL;

	yyin=fopen("code.txt","r");
	yyparse();

	printf("\n\n_____ TABLE DES SYMBOLES _____________________________________________\n\n");
	afficher(tab);
	printf("______________________________________________________________________\n\n");
	optimiser(&Qdr);
	AffichageQuad(Qdr);
	GenCode(Qdr,tab);
	return 0;	
}


