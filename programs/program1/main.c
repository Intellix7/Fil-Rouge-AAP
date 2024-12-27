// Include a file that contains all type definitions and functions.
#include "../definitions.h"


int main(int argc, char **argv) {
    // Creates the temporary string that will hold the text retrieved from the file.
    char temp[MAX_LEN];

    // Variable containing the metadatas from the file (SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES).
    t_metadata meta;

    // Halts the program if the user uses the wrong syntax.
    if (argc < 2) {
        printf("Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }

    // // Opens the datafile.
    FILE *anagrammeFile = fopen(argv[1], "r");

    // STEP 1 : IMPLEMENTING METADATA WITH : SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES

    // STEP 1.1 : SEPARATOR
    fgets(temp, MAX_LEN, anagrammeFile);
    while (strcspn(temp, "\n\r") > 1) {
        // A line is only read if it contains only one character.
        fgets(temp, MAX_LEN, anagrammeFile);
    }
    meta.sep = *temp; // Gets separator.

    // STEP 1.2 : NB_OF_FIELDS & FIELD_NAMES
    if (meta.sep != '#') {
        // if the # is not the separator, then it means we have to ignore every line starting with #.
        fgets(temp, MAX_LEN, anagrammeFile);
        while (temp[0] == '#') {
            fgets(temp, MAX_LEN, anagrammeFile);
        }

        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);

        // This variable represents a list of fields.
        t_field *field_table = malloc(sizeof(t_field) * meta.nbFields);

        fgets(temp, MAX_LEN, anagrammeFile);
        // Then again, we ignore lines starting with #.
        while (temp[0] == '#') {
            fgets(temp, MAX_LEN, anagrammeFile);
        }

        // Retrieves the fieldNames
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table;
    } else {
        // Case where # is the separator.
        // We then assume that there are no comment line after the separator declaration.
        fgets(temp, MAX_LEN, anagrammeFile);

        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);

        fgets(temp, MAX_LEN, anagrammeFile);

        // This variable represents a list of fields
        t_field *field_table = malloc(sizeof(t_field) * meta.nbFields);

        // Retrieves the fieldNames
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table;
    }

    // STEP 2 : CREATING THE DICTIONNARY
    t_tupletable *dico1 = malloc(sizeof(t_tupletable)); // Defines a pointer towards a dictionnary.
    int len_dic = 0;

    while (fgets(temp, MAX_LEN, anagrammeFile) != NULL) {
        // Reads lines until the end of file.
        split(meta.sep, temp, meta.nbFields, dico1->tuples[len_dic].key, dico1->tuples[len_dic].value);
        len_dic++; //filling dico1 with its tuples
    }

    dico1->nbTuples = len_dic; //number of keys added in dico1

    char finding[MAX_LEN];
    printf("Mots indexés : %d\n", len_dic);
    printf("Donnez le mot à trouver : \n");
    // printf("%s", finding);
    while (scanf("%99s", finding) != EOF) {
        // we can search as many words as we want until we stop the program
        print_tuples(meta, dico1, finding);
        printf("\nDonnez le mot à trouver : \n");
    }

    fclose(anagrammeFile);
}
