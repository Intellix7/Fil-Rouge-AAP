#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXLEN 1000
#define MAXFIELDS 15
#define MAXTUPLES 60000


// ----------------------------------------------------------------------
// 1. TYPES 
typedef char t_field[MAXLEN];			// A field is a string of max. 1000 characters.
typedef t_field t_key;					// A key is a field.
typedef t_field t_value[MAXFIELDS];		// t_value is a list of max. 60000 fields.

typedef struct {
	char sep;				// Character which separates a field from another one.
	int nbFields;			// Max number of fields contained in a line.
    t_key key;				// The key label (Eg. for anagrammes.dat, the key label is "mot")
	t_field * fieldNames;	// The list of the field-name-labels (Eg. for anagrammes.dat, it is : ["anagramme1", "anagramme2", ..., "anagramme13"])
} t_metadata;

typedef struct {		// A tuple contains a key and a list of fields associated to this key.
	t_key key;
	t_value value;
} t_tuple;

typedef struct {
    t_tuple tuples[MAXTUPLES];  // Table of tuples
    int nbTuples;               // Number of words stored
} t_tupletable;

typedef struct node {
t_tuple data;
struct node *pNext;
} t_node;

typedef t_node * t_list;

typedef struct {
int hashfunction;// numéro de la fonction de hachage
int nbSlots; // nombre d’alvéoles
t_list * slots; // taille définie à l'exécution
} t_hashtable;

typedef int (*function)(t_key, t_hashtable);


// ----------------------------------------------------------------------
// 2. PROTOTYPES AND DOCUMENTATION

// 2.1 HELPER FUNCTIONS

void split(char sep, char * txt, int nbFields, t_key key, t_field * schema_field_table);
/*
split takes 5 parameters : 
	- char sep : the separator
	- char * txt : string of characters that we want to split (Eg. : "key:ana1:ana2:ana3")
	- int nbFields : the max number of fields contained in a line.
	- t_key key : field which awaits for the key to be stored in it...
	- t_field * schema_field_table : list of fields which awaits for all the fields to be stored in it...
	
It returns nothing but stores the key & all the field names from "txt" in "key" and "schema_field_table".
*/

void print_tuples(t_metadata data, t_tupletable * dico, char * key);
/*
print_tuples takes 3 parameters : 
	- t_metadata data : it allows to access fieldNames, nbFields and key.
	- t_tupletable * dico : pointer towards the dictionnary, which is a list of tuples. Eg. : [[key1, [ana1.1, ana1.2]], [key2, [ana2.1, ana2.2, ana2.3]]]*
	- key : the key to search in the dictionnary


It should display something like the following :
"[...] mots indexés"
"Saisir les mots recherchés : " (scanf)
--> If the key is found, then proceed to display the following :
"Recherche de [key] : trouvé ! nb comparaisons : [...]"
"mot : ..."
"anagramme 1: ..."
"anagramme 2: ..."
"anagramme 3: X" (display "X" if there is no more anagram)
...
"anagramme [nbFields]: X"

--> If the key is not found, then proceed to display the following :
"Recherche de [key] : échec ! nb comparaisons : [...]"
*/

// 2.2 CHAINED LIST FUNCTIONS

int isEmpty(t_list li);
t_tuple getFirstVal(t_list li);
// void showList(t_list li);
t_list newList();
t_list addHeadNode(t_tuple data, t_list li);
t_list removeHeadNode(t_list li);


// 2.3 HASH FUNCTIONS

int first_ASCII(t_key key, t_hashtable hash);
/* 	first_ASCII takes two parameters : 
	- a key
	- a t_hashtable object holding the information about the hashtable
Returns the ASCII code of its first character mod 
[the number of hash slots defined in the console arguments]  
*/

// ----------------------------------------------------------------------
// 3. FUNCTIONS

// 3.1 HELPER FUNCTIONS

void split(char sep, char * txt, int nbFields, t_key key, t_field * schema_field_table){
    int l = strlen(txt);	// strlen gives the length of whole string given in parameters.
    int k = 0, i = 0, j = 0;

	// This first while loop retrieves the key
    while ((txt[i] != sep) && (txt[i] != '\0')){
            key[i] = txt[i];
            i++;
    }

    key[i] = '\0';

	// places cursor on the beginning of the next field
	i++;

	/* 	This loop retrieves all the fields while separating words between 
		the separator and ignoring \n and \0 characters */
	while ((i < l) && (k < nbFields)) {
        while ((txt[i] != sep) && (txt[i] != '\0') && (txt[i] != '\n')){
            schema_field_table[k][j] = txt[i];
            j++;
            i++;
        }
        k++;
        i++;
        j = 0;
    }
}

void print_tuples(t_metadata data, t_tupletable * dico, char * key) {
	int index_key = 0;
	int found = 0;
	for (int i = 0; i < dico->nbTuples; i++) {
		/* 	Looking for the key inside the dictionnary. strcmp checks if 
			2 strings are equal and returns 0 if that's the case. */
		if (strcmp(key, dico->tuples[i].key) == 0) {
			found = 1;
			break;
		}
		index_key++;
	}
	if (!found) {
		printf("Recherche de %s : échec ! nb comparaisons : %d\n", key, index_key);
	}
	else {
		printf("Recherche de %s : trouvé ! nb comparaisons : %d\n", key, index_key+1);
		printf("%s : %s\n", data.key, key); // mot : key
		
		for (int k = 0; k < data.nbFields-1; k++) {
			if ((dico->tuples[index_key].value[k][0] != '\0')) {
				printf("%s: %s\n", data.fieldNames[k], dico->tuples[index_key].value[k]); // anagramme k: ...
			}
			else if (strcmp(data.fieldNames[k], "") != 0){
				printf("%s: X\n", data.fieldNames[k]); // anagramme k: X
			}
		}
	}		
}

// 3.2 CHAINED LIST FUNCTIONS

int isEmpty(t_list li){
    return (li == NULL);
}

t_tuple getFirstVal(t_list li) {
    assert(!isEmpty(li));
    return li->data;
}

// void showList(t_list li){
//     int k = 0;
//     printf("*** affichage de la liste ***\n");
//     while (li != NULL){
//         printf("Maillon %d, Valeur = %.1f\n", k, li->val);
//         li = li->p;
//         k++;
//     }
// }

t_list newList(){
    t_list li = NULL;
    return li;
}

t_list addHeadNode(t_tuple data, t_list li){
    t_node * n = malloc(sizeof(t_node));
    n->data = data;
    n->pNext = li;
    return n;

}

t_list removeHeadNode(t_list li){
    assert(!isEmpty(li));
    t_list p = li->pNext;
    free(li);
    return p;
}

// 3.3 HASH FUNCTIONS 

int first_ASCII(t_key key, t_hashtable hash){
	return (int)(key[0] % hash.nbSlots);
}