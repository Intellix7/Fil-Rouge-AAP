#include "definitions.h"

int main() {
    
    // char t[5][5];
    // t[4][1] = 'f';
    // char a = t[4][1];
    // printf("%c", a);

    t_key key;
    t_field * field_table = malloc(sizeof(t_field) * MAXFIELDS);
    char * t2 = "mo:anagramme 1:anagramme 2:anagramme 3:anagramme 4:anagramme 5:anagramme 6:anagramme 7:anagramme 8:anagramme 9:anagramme 10:anagramme 11:anagramme 12:anagramme 13";
    char * t3 = "pomme:banane:poire:litchi";
    split(':', t2, MAXFIELDS, key, field_table);
    // printf("%p\n", key);
    // print_fields(field_table);
    t_tupletable * dico = malloc(sizeof(*dico));
    split(':', t3, MAXFIELDS, dico->tuples[0].key, dico->tuples[0].value);
    printf("%s", dico->tuples[0].value[3]);
}