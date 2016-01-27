#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "correct.h"
#include "hash.h"

/* Fonction deletions : 1er type de correction */
int deletions(char* mot, char** cor, int index) {
	
	int taille = strlen(mot);
	int i=0;
	int y= 0;
	int compteur=0;
	char tmp[taille];
	strcpy(tmp,mot);
	
	for(y; y < taille; y++) {
		
		i=y;
		strcpy(mot,tmp);
		while(mot[i]!='\0'){
			mot[i]=mot[i+1];
			i++;
		}
		
		*(cor+index)=(char*)malloc(taille*sizeof(char));
		if ( *(cor+index) == NULL ) {
			exit(EXIT_FAILURE);
		}
		strcpy(*(cor+index),mot);
		
		index++;
		compteur++;
	}
	
	strcpy(mot,tmp);
	return compteur;	
}

/* Fonction deletions : 2eme type de correction */
int transpositions(char* mot, char** cor, int index) {
	
	int taille = strlen(mot);
	int i=0;
	int y= 0;
	int compteur=0;
	
	char tmp[taille];
	strcpy(tmp,mot);
	
	for(y; y < (taille-1); y++) {
			
		strcpy(mot,tmp);
		mot[i] = tmp[i+1];
		mot[i+1] = tmp[i];
		i++;
		
		*(cor+index)=(char*)malloc(taille*sizeof(char));
		if ( *(cor+index) == NULL ) {
			exit(EXIT_FAILURE);
		}
		strcpy(*(cor+index),mot);
		index++;
		compteur++;
	}	
	
	strcpy(mot,tmp);
	return compteur;
}

/* Fonction deletions : 3eme type de correction */
int alterations(char* mot, char** cor, int index) {
	
	int taille = strlen(mot);
	int i=0;
	int y= 0;
	int compteur=0;
	char tmp[taille];
	strcpy(tmp,mot);
	
	for(y; y < strlen(ALPHABET); y++) {
		i = 0;
		
		while(i < taille) {
			strcpy(mot,tmp);
			mot[i] = ALPHABET[y];	
			i++;

			*(cor+index)=(char*)malloc(taille*sizeof(char));
			if ( *(cor+index) == NULL ) {
				exit(EXIT_FAILURE);
			}
			strcpy(*(cor+index),mot);
			index++;
			compteur++;
		}
	}
	
	strcpy(mot,tmp);
	return compteur;
}

/* Fonction deletions : 4eme type de correction */
int inserts(char* mot, char** cor, int index) {
	
	int taille = strlen(mot);
	int i=0;
	int y= 0;
	int z=0;
	int compteur=0;
	
	char tmp[taille];
	strcpy(tmp,mot);

//ajoute une lettre inutile à la fin	
	strcat(mot,"a");

//déplace la lettre inutile au debut
	while(i < taille) {
		
		mot[i+1] = tmp[i];
		i++;
	}
	
//remplace la lettre inutile par succesivement toutes les lettres de l'alphabet	
	i=0;
	while(i < taille+1) {
		
		y=0;
		for(y; y < strlen(ALPHABET); y++) {
			mot[i] = ALPHABET[y];
			*(cor+index)=(char*)malloc(taille*sizeof(char));
			if ( *(cor+index) == NULL ) {
				exit(EXIT_FAILURE);
			}
			strcpy(*(cor+index),mot);
			*(cor+index)=(char*)malloc(taille*sizeof(char));
			if ( *(cor+index) == NULL ) {
				exit(EXIT_FAILURE);
			}
			strcpy(*(cor+index),mot);
			index++;
			compteur++;
		}
		
		mot[i] = tmp[i];
		i++;
	}
	
	strcpy(tmp,mot);
	return compteur;
}
/* Fonction permetant d'afficher les différentes corrections */

void afficher(char** cor){
	int i=0;
	while(*(cor+i)!=NULL){
		printf("%s\n",*(cor+i));
		i++;
	}
}


/* Fonction better_candidate : retourne le meilleur mot en fonction du nombre d'occurences*/
char* better_candidate(char * word,char ** corrections, int index){
    int i;
    char* better=(char*)malloc(20*sizeof(char));
    if ( better == NULL ) {
		exit(EXIT_FAILURE);
	}
    int max=0;
    for (i=0;i<index;i++){
		if(hash_table_is_present(*(corrections+i))){
			if(hash_table_search(*(corrections+i))>max){
				max=hash_table_search(*(corrections+i));
				strcpy(better,*(corrections+i));
			}
		}
    }
    if( max == 0) {
		free(better);
		better = NULL;
	}

    return better;
}

/* Détruit et libert en mémoire corrections */
destroy_corrections(char** corrections, int index) {
	free(corrections);
	corrections = NULL;
}

////////////////////////////////////////////////////////////////////////

static char **build_corrections(char *word, int *size)
{
	
  char **corrections;
  corrections=(char**)malloc(1000*sizeof(char*));
  if ( corrections == NULL ) {
	exit(EXIT_FAILURE);
  }
  int index = 0;

  if (corrections == NULL) {
    fprintf(stderr, "cannot allocate the array of corrections");
    exit(EXIT_FAILURE);
  }

  /* construires une liste de mots possibles */
  index = deletions(word, corrections, index);
  index += transpositions(word, corrections, index);
  index += alterations(word, corrections, index);
  index += inserts(word, corrections, index);

  *size = index;
  return corrections;
}


static char *find_correction(char *word)
{

  char *result;
  int index = 0;
  char **corrections = build_corrections(word, &index);
  
  /* choisir le meilleur candidat entre word et les corrections possibles du mot */
  result = better_candidate(word, corrections, index);

  if (result == NULL) {
    /* Pas de correction avec  une seule erreur pour "word" */
	printf("__Pas de correction avec une distance de 1 pour '%s'\n", word);
	printf("__Tentative d'une correction à deux erreurs\n");
	
	char** correc2erreurs;
	correc2erreurs = (char**)malloc(1000*sizeof(char*));
	if ( correc2erreurs == NULL ) {
		exit(EXIT_FAILURE);
	}
	int i;
	char **corrections2;
	int index2=0;
	
	for(i=0;i<index;i++) {
		
		int taille=strlen(word)+1;
		corrections2 = build_corrections(*(corrections+i), &index2);
		result = better_candidate(*(corrections+i),corrections2,index2);
		*(correc2erreurs+i)=(char*)malloc(taille*sizeof(char));
		if ( *(correc2erreurs+i) == NULL ) {
			exit(EXIT_FAILURE);
		}
		
		if(result != NULL) {
			strcpy(*(correc2erreurs+i),result);
		}
	}
	
	result =  better_candidate(word, correc2erreurs, index);
	if (result == NULL) {
		printf("__Aucune corrections possibles\n");
	}
	/* Netoyage */
	destroy_corrections(corrections2, index);
	destroy_corrections(correc2erreurs, index);
  }

  /* un peu de ménage avant de renvoyer le meilleur candidat */
  result = strdup(result? result: word);
  destroy_corrections(corrections, index);

  return result;
}

char *correct_word(char *word)
{
  if (hash_table_is_present(word))
    return word;
  else {
    char *correct = find_correction(word);

    return correct? correct: word;
  }
}
