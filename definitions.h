#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000
#define MAXFIELDS 15

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
t_field fieldNames[MAXFIELDS];
} t_metadata;

void hello(){
    printf("Hello\n");
}

// Prototypes 

// ** split() ** 
// split takes 2 parameters : 
//  - char sep which is the separator
//  - char * txt which is the string of characters that we want to split
// It returns a t_field * object that contains the list 
// of the different fields, including the key at the start

t_field * split(char sep, char * txt);

// ** print_fields() **
// It... prints... the fields...
 
void print_fields(t_field * field_table);


// ----------------------------------------------------------------------
// Actual function declarations


t_field * split(char sep, char * txt){
    int l = strlen(txt);
    // printf("%d\n", l);
    t_field * field_table = malloc(sizeof(t_field) * MAXFIELDS);
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
    return field_table;
}

void print_fields(t_field * field_table){
    printf("key : %s\n", field_table[0]);
    for (int i = 1; i < MAXFIELDS-1 ; i++){
        printf("value %d : %s\n", i, field_table[i]);
    }
}

