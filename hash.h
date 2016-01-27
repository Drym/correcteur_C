#ifndef _HASH_H
#define _HASH_H
#include <search.h>

#define HASH_TABLE_SIZE 100000

/* creation de destruction de la table */
void hash_table_create(void);
void hash_table_destroy(void);

/* renvoie 1 si word est dans la table, 0 sinon */
int hash_table_is_present(char *word);

/* renvoie le nombre d'occurences de word dans la table (0 si absent) */
int hash_table_search(char *word);

/* ajoute word dans la table */
void hash_table_add(char *word);
#endif
