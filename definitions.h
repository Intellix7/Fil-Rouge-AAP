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

t_field * split(char sep, char * txt);

t_field * split(char sep, char * txt){
    int l = strlen(txt);
    printf("%d\n", l);
    t_field * field_table = malloc(sizeof(t_field) * MAXFIELDS);
    int k = 0, i = 0;
    int j = 0;
    while ((i < l) && (k < MAXFIELDS)) {
        printf("%d\n", i);
        while (txt[i] != sep){
            printf("%c, %d", txt[i], i);
            field_table[k][j] = txt[i];
            j++;
            i++;
        }
        k++;
        j = 0;
        i++;
    }
    return field_table;
}

