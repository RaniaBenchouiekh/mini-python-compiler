#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hash_ele
{
	char* name;
	int type;
	int nature;
	int taille;
	struct hash_ele* svt;
} hash_ele;


int hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%511;
}


void inserer (struct hash_ele* tab_hash[], char* idf, int type, int Nature,int taille)
{
	int i=hash(idf);
	struct hash_ele *nouveau = malloc(sizeof(hash_ele));
	nouveau->name=strdup(idf);
	nouveau->type=type;
	nouveau->nature=Nature;
	nouveau->taille=taille;
	nouveau->svt=tab_hash[i];
	tab_hash[i]=nouveau;

}

void afficher ( struct hash_ele* tab_hash[])
{
	for (int i = 0; i < 511; ++i)
	{
		if (tab_hash[i]!=NULL)
		printf("INDICE %d: IDF: %s // TYPE: %d // NATURE: %d // TAILLE: %d \n",i,tab_hash[i]->name,tab_hash[i]->type,tab_hash[i]->nature,tab_hash[i]->taille);
	}
}

int recherche_element(struct hash_ele* tab_hash[], char* name)
	{
		int i=hash(name);
		struct hash_ele* element = tab_hash[i];
		while(element!=NULL)
		{ if (!strcmp(element->name,name)) return 1;
		  	
		  else element=element->svt;
		}
		return 0;
	}

int get_type(struct hash_ele* tab_hash[], char* name)
	{
		int i=hash(name);
		struct hash_ele* element = tab_hash[i];
		while(element!=NULL)
		{ if (!strcmp(element->name,name)) return element->type;
		  else element=element->svt;
		}
	}


int get_nat(struct hash_ele* tab_hash[], char* name)
	{
		int i=hash(name);
		struct hash_ele* element = tab_hash[i];
		while(element!=NULL)
		{ if (!strcmp(element->name,name)) return element->nature;
		  else element=element->svt;
		}
	}
/*
int main(int argc, char const *argv[])
{
 	hash_ele *tab[511];
 	for (int i = 0; i < 511; ++i)
 		{
 			tab[i]=NULL;
 		}	
 	inserer (tab, "hodaifa",1,4);
 	inserer (tab, "hello", 1,0);
 	inserer (tab, "nazim", 3,1);
 	inserer (tab, "char", 3,1);
 	afficher(tab);
 	printf("%d\n",recherche_element(tab,"hodaif"));
 	printf("%d\n",get_nat(tab,"hodaifa") );
	return 0;
}*/

//IL MANQUE LA TAILLE
/*
void afficher(struct hash_ele* tab_hash[])
{	
	int i,j;
	printf(".---------.");
	for(j=1;j<=3;j++)
	{	
	for(i=1;i<=10;i++) printf("-");
	if(j==3)
	{
	printf("-.");
	}
	else
	printf(".");
	}
	printf("\n|  INDICE  |  ENTITE  |   TYPE   |  NATURE  |\n");
	printf(".---------.");
	for(j=1;j<=3;j++)
	{	
	for(i=1;i<=10;i++) printf("-");
	if(j==3)
	{
	printf("-.");
	}
	else
	printf(".");
	}
	

	for (int i = 0; i < 511; ++i)
	{
	
		if (tab_hash[i]!=NULL)
		{
		printf("\n|  %d     |",i);
		printf("  %s",tab_hash[i]->name);
		switch(strlen(tab_hash[i]->name))
		{
			case 1: printf("       |   %d      ",tab_hash[i]->type);
				break;
			case 2: printf("      |   %d      ",tab_hash[i]->type);
				break;
			case 3: printf("     |   %d      ",tab_hash[i]->type);
				break;
			case 4: printf("    |   %d      ",tab_hash[i]->type);
				break;
			case 5: printf("   |   %d      ",tab_hash[i]->type);
				break;
			case 6: printf("  |   %d      ",tab_hash[i]->type);
				break;
			case 7: printf(" |   %d      ",tab_hash[i]->type);
				break;
			case 8: printf("|   %d      ",tab_hash[i]->type);
				break;
			default : break;
		}
		switch(sizeof(tab_hash[i]->type))
		{
			case 4: printf("|  %d       |",tab_hash[i]->nature);
				break;
			case 6: printf("|  %d       |",tab_hash[i]->nature);
				break;
			default : break;
		}
		/*switch(sizeof(tab_hash[i]->nature))
		{
			case 8: printf("  |");
				break;
			case 9 : printf(" |");
				break;
			default : break;
		}
		
		}	
	}
	printf("\n.---------.");
	for(j=1;j<=3;j++)
	{	
	for(i=1;i<=10;i++) printf("-");
	if(j==3)
	{
	printf("-.");
	}
	else
	printf(".");
	}
	printf("\n");
}*/
