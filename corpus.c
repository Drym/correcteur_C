#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "corpus.h"
#include "hash.h"
#define TAILLE_MAX 100

char * convertir(char *mot){
	char *newstr, *p;
    p=newstr= strdup(mot);
    while(*p){
		if(*p<'Z' && *p>'A')
		*p+=32;
		p++;
	}
    return newstr;
}

/* Ouvre le fichier et stock les mots dans une hash table*/
int init_corpus_from_file(char *filename) {
	
	FILE* fichier = NULL;
	char* mot;
	char* motminuscule;
    fichier = fopen(filename, "r+");
	char chaine[TAILLE_MAX];

	if (fichier != NULL) {
		while(fgets(chaine, TAILLE_MAX, fichier) != NULL){
			mot=strtok(chaine,SEPARATORS);
			if(mot!=NULL){
				motminuscule=convertir(mot);
				hash_table_add(motminuscule);
			}
			
			while(mot!=NULL){
				mot=strtok(NULL,SEPARATORS);
				if(mot!=NULL){
					motminuscule=convertir(mot);
					hash_table_add(motminuscule);
				}
			} 
		}
			fclose(fichier);
			return 1;
	}
	
	else {
		// On affiche un message d'erreur si on veut
		printf("Impossible d'ouvrir le fichier test.txt");
		return 0;
	}
}
