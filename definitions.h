#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000
#define MAXFIELDS 15
#define MAXTUPLES 60000


// ----------------------------------------------------------------------
// Types 

typedef char t_field[1000];
typedef t_field t_key;
typedef t_field t_value[MAXFIELDS];

typedef struct {
	t_key key;
	t_value value;
} t_tuple;

typedef struct {
	char sep;
	int nbFields;
    t_key key;
	t_field * fieldNames;  // Here, the definition was changed according to the BONUS section because it makes things easier.
} t_metadata;

typedef struct {
    t_tuple tuples[MAXTUPLES];  // Table of tuples
    int nbTuples;               // Number of words stored
} t_tupletable;


// ----------------------------------------------------------------------
// Prototypes & documentation

void split(char sep, char * txt, int nbFields, t_key key, t_field * schema_field_table);
/*
split takes 3 parameters : 
	- char sep : the separator
	- char * txt : string of characters that we want to split (Eg. : "key:ana1:ana2:ana3")
	- t_field * field_table : t_field pointer that will hold all the data within a line (Eg. : "[key, ana1, ana2, ana3]")
It returns nothing but stores all fields in the field_table pointer.
*/

void print_tuples(t_metadata data, t_tupletable * dico);
/*
print_tuples takes 2 parameters : 
	- t_metadata data : it allows to access fieldNames, nbFields and key.
	- t_tupletable * dico : pointer towards the dictionnary, which is a list of tuples (Eg. : [["key1", ["ana1", "ana2"]], ["key2", ["ana1", "ana2", "ana3"]]])

It should display something like the following :
"[...] mots indexés"
"Saisir les mots recherchés : " (scanf)
"Recherche de [key] : [échec/trouvé] ! nb comparaisons : [...]"
If the key is found, then proceed to display the following :
"mot : ..."
"anagramme 1: ..."
"anagramme 2: ..."
"anagramme 3: X" (display "X" if there is no more anagram)
...
"anagramme [nbFields]: X"
*/

// ----------------------------------------------------------------------
// Functions

void split(char sep, char * txt, int nbFields, t_key key, t_field * schema_field_table){
    int l = strlen(txt);
    // printf("%d\n", l);
    int k = 0, i = 0, j = 0;

    while ((txt[i] != sep) && (txt[i] != '\0')){
            // printf("%c, %d\n", txt[i], i);
            key[i] = txt[i];
            i++;
    }

    key[i] = '\0';


    while ((i < l) && (k < nbFields)) {
        // printf("%d\n", i);
        while ((txt[i] != sep) && (txt[i] != '\0')){
            // printf("%c, %d\n", txt[i], i);
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

