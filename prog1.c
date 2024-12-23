#include "definitions.h"


int main(int argc, char ** argv) {
    
     char temp[MAXLEN];

     t_metadata meta; 
    
    if (argc<2) {
        printf("Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }
    
    FILE * anagrammeFile = fopen(argv[1], "r");

    fgets(temp, MAXLEN, anagrammeFile);
    while (strlen(temp) > 2){
        fgets(temp, MAXLEN, anagrammeFile);
    }
    meta.sep = *temp;
    // printf("%c\n", meta.sep);

    fgets(temp, MAXLEN, anagrammeFile);
    if (meta.sep != '#') {
        while (temp[0] == '#') {
            fgets(temp, MAXLEN, anagrammeFile);
        }
        meta.nbFields = atoi(temp);
        printf("%d", meta.nbFields);

        fgets(temp, MAXLEN, anagrammeFile);
            while (temp[0] == '#') {
                fgets(temp, MAXLEN, anagrammeFile);
            }

        t_field * field_table;    
        field_table = split(meta.sep, temp);

    }

    fclose(anagrammeFile);

}