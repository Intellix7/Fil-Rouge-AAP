#include "definitions.h"

int main() {
    
    // char t[5][5];
    // t[4][1] = 'f';
    // char a = t[4][1];
    // printf("%c", a);

    t_field * field_table;
    char * t = "hello:world";
    field_table = split(':', t);
}