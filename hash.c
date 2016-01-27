#include <stdio.h>
#include <search.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 200000

/* Fonction permetant de créer la hash table */
void hash_table_create(void){
	int a=hcreate(TAILLE);
	if(a==0){
		printf("pas assez de mémoire\n");
	}
}

/* Fonction permetant de vérifier si un mot est dans la hash table */
int hash_table_is_present(char *mot){
	ENTRY* r;
	ENTRY e;
	e.key=(char*)malloc(strlen(mot)*sizeof(char));
	if ( e.key == NULL ) {
		exit(EXIT_FAILURE);
	}
	strcpy(e.key,mot);
	r=hsearch(e,FIND);
	if(r==NULL)
		return 0;
	else return 1;
}

/* Fonction permetant de trouver le nombre d'occurence d'un mot dans la hash table */
int hash_table_search(char *mot){
	ENTRY* r;
	ENTRY e;
	e.key=(char*)malloc(strlen(mot)*sizeof(char));
	strcpy(e.key,mot);
	r=hsearch(e,FIND);
	if(r==NULL){
		return 0;
	}
	else {
		return *(int*)(r->data);
	}
}

/* Fonction permetant de detruire la hash table */
void hash_table_destroy(void){
	hdestroy();
}

/* Fonction permetant d'ajouter un mot à la hash table */
void hash_table_add(char *mot){
	ENTRY* r;
	ENTRY e;
	e.key=mot;
	r=hsearch(e,FIND);
	if(r==NULL) {
		e.data=(int*)malloc(sizeof(int));
		*(int*)(e.data)=1;
		e.key=mot;
		ENTRY* r2;
		r2=hsearch(e,ENTER);
		return;
	}
	else {
		(*(int*)(r->data))++;
	}
}
