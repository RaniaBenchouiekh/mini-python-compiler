%{
//pre-code C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "projet.tab.h"

extern YYSTYPE yylval;

int numL=1,numC=0,Ind=0;
%}

 //Entites du langage

espace         [" "\t]+
chiffre        [0-9]
lettre         [A-Za-z]
char 	       "'"."'"  
int            "("[+-]{chiffre}+")"|{chiffre}+      
float          "("[+-]{chiffre}+("."{chiffre}+)?")"|{chiffre}+("."{chiffre}+)?
idf 	       [A-Z]({lettre}|{chiffre})*
commentaire    "#".*
      
%% 

 //regles  de traductions

"+" { yylval =(YYSTYPE)strdup(yytext); numC++; return ADD; }
"-" { yylval =(YYSTYPE)strdup(yytext); numC++; return SOUS;}
"*" { yylval =(YYSTYPE)strdup(yytext); numC++; return MULT;}
"/" { yylval =(YYSTYPE)strdup(yytext); numC++; return DIV;}

"=" { yylval =(YYSTYPE)strdup(yytext); numC++; return EGAL;}
"==" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return DEGAL;}
"!=" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return DIFF; }
"<" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return INF;}
"<=" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return INFEG; }
">" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return SUP; }
">=" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return SUPEG; }

"and" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return ET; }
"or" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return OU;}

"if"  { numC+=yyleng; return IF;}
"elif"  { numC+=yyleng; return ELIF;}
"else"  { numC+=yyleng; return ELSE;}
"for"   { numC+=yyleng; return FOR;}
"in range"  { numC+=yyleng; return INRANGE;}
"while"  { numC+=yyleng; return WHILE;}


"int" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return t_int; }
"float" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return t_float; }
"char" { yylval =(YYSTYPE)strdup(yytext); numC+=yyleng; return t_char; }


"[" {numC++; return '[';}
"]" {numC++; return ']';}
"(" {numC++; return '(';}
")" {numC++; return ')';}
"," {numC++; return ',';}
":" {numC++; return ':';}
"{" {numC++; return '{';}
"}" {numC++; return '}';}

{idf}  	{yylval =(YYSTYPE)strdup(yytext);
	 if (yyleng>8) 
	    {printf("\nErreur: idf trop long !\nType d'erreur: Erreur Lexicale - Ligne: %d - Colonne: %d - Entite: %s \n",numL,numC,yytext); return 1;}
	 else {numC+=yyleng; return IDF;}}

{int}	 {yylval.entier=atoi(yytext);
	  
	  if(yylval.entier < (0-32768))
 	    {printf("\nErreur: Entier trop petit !\nType d'erreur: Erreur Lexicale - Ligne: %d - Colonne: %d - Entite: %s \n",numL,numC,yytext);
	     return 1;
	    }

	  else{ 
	        if(yylval.entier > 32767)
		{printf("\nErreur: Entier trop grand !\nType d'erreur: Erreur Lexicale - Ligne: %d - Colonne: %d - Entite: %s \n",numL,numC,yytext);
	     	 return 1;
		}

		else 
		{numC+=yyleng;	
		 return INT;
		}
	      }
	 }

{float}	 {yylval.reel=atof(yytext);
	  
	  if(yylval.reel < (0-32768))
 	    {printf("\nErreur: Reel trop petit !\nType d'erreur: Erreur Lexicale - Ligne: %d - Colonne: %d - Entite: %s \n",numL,numC,yytext);
	     return 1;
	    }

	  else{ 
		if(yylval.reel > 32767)
		{printf("\nErreur: Reel trop grand !\nType d'erreur: Erreur Lexicale - Ligne: %d - Colonne: %d - Entite: %s \n",numL,numC,yytext);
	     	 return 1;
		}

		else 
		{numC+=yyleng;	
		 return FLOAT;
		}
	      }

	 }

{char}   {numC+=yyleng; 
	  return CHAR;
	 }

{espace} {numC+=yyleng;Ind+=yyleng;}

{commentaire} ;

"\n" {numL++; numC=0;Ind=0;return '\n';}


. {numC+=yyleng; printf("Type : Erreur lexicale, Entite : \"%s\", Ligne : %d, Colonne : %d\n",yytext,numL,numC);}

%%

//post-code C
int yywrap () 
{return 1;}

