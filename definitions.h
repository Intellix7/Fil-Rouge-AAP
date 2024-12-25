#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


// ----------------------------------------------------------------------
// 2. PROTOTYPES AND DOCUMENTATION

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

void print_tuples(t_metadata data, t_tupletable * dico);
/*
print_tuples takes 2 parameters : 
	- t_metadata data : it allows to access fieldNames, nbFields and key.
	- t_tupletable * dico : pointer towards the dictionnary, which is a list of tuples. Eg. : [[key1, [ana1.1, ana1.2]], [key2, [ana2.1, ana2.2, ana2.3]]]


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


// ----------------------------------------------------------------------
// 3. FUNCTIONS

void split(char sep, char * txt, int nbFields, t_key key, t_field * schema_field_table){
    int l = strlen(txt);	// strlen gives the length of whole string given in parameters.
    int k = 0, i = 0, j = 0;

    while ((txt[i] != sep) && (txt[i] != '\0')){
            key[i] = txt[i];
            i++;
    }

    key[i] = '\0';


    while ((i < l) && (k < nbFields)) {
        while ((txt[i] != sep) && (txt[i] != '\0')){
            schema_field_table[k][j] = txt[i];
            j++;
            i++;
        }
        k++;
        i++;
        j = 0;
    }
}

void print_tuples(t_metadata data, t_tupletable * dico) {
	char * key; // Word to search in dictionnary.
	
	printf("%d mots indexés\n", dico->nbTuples);
	printf("Saisir les mots recherchés : ");
	scanf("%s", *key);
	printf("\n");

	int index_key = 0;
	int found = 0;
	for (int i = 0; i < dico->nbTuples; i++) {
		if (strcmp(key, dico->tuples[i].key) == 0) { // Looking for the key inside the dictionnary. strcmp checks if 2 strings are equal and returns 0 if that's the case.
			found = 1;
			break;
		}
		index_key += 1;
	}
	if (found != 0) {
		printf("Recherche de %s : échec ! nb comparaisons : %d\n", key, index_key);
	}
	else {
		printf("Recherche de %s : trouvé ! nb comparaisons : %d\n", key, index_key);
		printf("%s : %s\n", data.key, key); // mot : key
		
		for (int k = 1; k < data.nbFields; k++) {
			if (dico->tuples[index_key].value[k] != '') {
				printf("%s: %s", data.fieldNames[k], dico->tuples[index_key].value[k]); // anagramme k: ...
			}
			else {
				printf("%s: X", data.fieldNames[k]); // anagramme k: X
			}
		}
	}		
}

