#include "definitions.h"

int main() {
    
    // char t[5][5];
    // t[4][1] = 'f';
    // char a = t[4][1];
    // printf("%c", a);

    t_metadata data;

    t_key key;
    t_field * field_table = malloc(sizeof(t_field) * MAX_FIELDS);
    
    char * t2 = "mot:anagramme 1:anagramme 2:anagramme 3:anagramme 4:anagramme 5:anagramme 6:anagramme 7:anagramme 8:anagramme 9:anagramme 10:anagramme 11:anagramme 12:";
    char * t3 = "pomme:banane:peche:litchi";
    split(':', t2, MAX_FIELDS, data.key, field_table);
    data.fieldNames = field_table;
    // printf("%s", data.fieldNames[2]);

    // split(':', t3, MAX_FIELDS, key, field_table);
    // printf("%p\n", key);
    // print_fields(field_table);
    t_tupletable * dico = malloc(sizeof(*dico));
    split(':', t3, MAX_FIELDS, dico->tuples[0].key, dico->tuples[0].value);
    dico->nbTuples = 1;
    data.nbFields = 14;
    // printf("%s", dico->tuples[0].value[3]);
    print_tuples(data, dico, "pomme");
}