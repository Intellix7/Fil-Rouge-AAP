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
	t_field * fieldNames;  // Here, the definition was changed according to the BONUS section because it makes things easier.
} t_metadata;

#define MAXTUPLES 60000
typedef struct {
    t_tuple tuples[MAXTUPLES]; // tableau des tuples
    int nbTuples; // nb mots saisis
    } t_tupletable;

// ----------------------------------------------------------------------
// Prototypes & documentation

void split(char sep, char * txt, t_field * field_table);
/*
split takes 3 parameters : 
	- char sep : the separator
	- char * txt : string of characters that we want to split [Eg. : "key:ana1:ana2:ana3"]
	- t_field * field_table : t_field pointer that will hold all the data within a line [Eg. : "[key, ana1, ana2, ana3]"]
It returns nothing but stores all fields in the field_table pointer.
*/

void print_fields(t_field * field_table);
// Prints the fields from a field table.

// ----------------------------------------------------------------------
// Functions

void split(char sep, char * txt, t_field * field_table){
    int l = strlen(txt);
    // printf("%d\n", l);
    int k = 0, i = 0, j = 0;
    while ((i < l) && (k < MAXFIELDS)) {
        // printf("%d\n", i);
        while ((txt[i] != sep) && (txt[i] != '\0')){
            // printf("%c, %d\n", txt[i], i);
            field_table[k][j] = txt[i];
            j++;
            i++;
        }
        k++;
        i++;
        j = 0;
    }
}

void print_fields(t_field * field_table){
    printf("key : %s\n", field_table[0]);
    for (int i = 1; i < MAXFIELDS-1 ; i++){
        printf("value %d : %s\n", i, field_table[i]);
    }
}

