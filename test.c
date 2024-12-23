#include "definitions.h"

int main() {
    
    // char t[5][5];
    // t[4][1] = 'f';
    // char a = t[4][1];
    // printf("%c", a);

    t_field * field_table;
    char * t = "mot:anagramme 1:anagramme 2:anagramme 3:anagramme 4:anagramme 5:anagramme 6:anagramme 7:anagramme 8:anagramme 9:anagramme 10:anagramme 11:anagramme 12:anagramme 13";
    field_table = split(':', t);

    print_fields(field_table);
}