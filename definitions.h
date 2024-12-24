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

void print_fields(t_field * field_table);
// Prints the fields from a field table.

void print_tuples(char * key, t_tuple * tuple_list, t_field * schema_field_table);
/*
print_tuples takes 3 parameters : 
	- char * key : the key to search in the dictionnary
	- t_tuple * tuple_list : the dictionnary, which is a list of tuples (Eg. : [["key1", ["ana1", "ana2"]], ["key2", ["ana1", "ana2", "ana3"])
	- t_field * schema_field_table : File schema, i.e. list of the names of the fields composing the file's lines (including the key) Eg. : "[key, ana1, ..., ana13]"
It should display something like the following :
"[...] mots indexés"
"Saisir les mots recherchés : " (scanf)
"Recherche de [key] : [échec/trouvé] ! nb comparaisons : [...]"
If the key is found, then proceed to display the following :
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

// void print_fields(t_field * field_table){
//     printf("key : %s\n", field_table[0]);
//     for (int i = 1; i < MAXFIELDS-1 ; i++){
//         printf("value %d : %s\n", i, field_table[i]);
//     }
// }

void print_tuples(char * key, t_tuple * tuple_list, t_field * standard_field_table) {
	
}

