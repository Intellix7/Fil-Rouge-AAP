// Include a file that contains all type definitions and functions.
#include "../definitions.h"

int main(int argc, char **argv)
{
    // Creates the temporary string that will hold the text retrieved from the file.
    char temp[MAX_LEN];

    // Variable containing the metadatas from the file (SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES).
    t_metadata meta;

    // Default hash function
    int defaultHash = 0;

    // Variable containing all the information about the hashtable
    t_hashtable hash;

    // Halts the program if the user uses the wrong syntax.
    if (argc < 3)
    {
        printf(
            "Utilisation :\n./programme <nom du fichier> <nombre d'alvéoles> <nom de la fonction de hachage (facultatif)>\n");
        exit(EXIT_FAILURE);
    }

    // Opens the datafile.
    FILE *fileIn = fopen(argv[1], "r");

    // Stores the number of slots of the hash function
    hash.nbSlots = atoi(argv[2]);

    // Sets the hash function to be used, default being first_ASCII
    hash.hashfunction = defaultHash;
    if (argc == 4)
    {
        hash.hashfunction = atoi(argv[3]);
    }
    function hashFunctionList[] = {&first_ASCII, &sum_ASCII};

    // STEP 1 : IMPLEMENTING METADATA WITH : SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES

    // STEP 1.1 : SEPARATOR
    fgets(temp, MAX_LEN, fileIn);
    while (strcspn(temp, "\n\r") > 1)
    {
        // A line is only read if it contains only one character.
        fgets(temp, MAX_LEN, fileIn);
    }
    meta.sep = *temp; // Gets separator.

    // STEP 1.2 : NB_OF_FIELDS & FIELD_NAMES
    if (meta.sep != '#')
    {
        // if the # is not the separator, then it means we have to ignore every line starting with #.
        fgets(temp, MAX_LEN, fileIn);
        while (temp[0] == '#')
        {
            fgets(temp, MAX_LEN, fileIn);
        }

        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);

        // This variable represents a list of fields.
        t_field *field_table = malloc(sizeof(t_field) * meta.nbFields);

        fgets(temp, MAX_LEN, fileIn);
        // Then again, we ignore lines starting with #.
        while (temp[0] == '#')
        {
            fgets(temp, MAX_LEN, fileIn);
        }

        // Retrieves the fieldNames
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table;
    }
    else
    {
        // Case where # is the separator.
        // We then assume that there are no comment line after the separator declaration.
        fgets(temp, MAX_LEN, fileIn);

        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);

        fgets(temp, MAX_LEN, fileIn);

        // This variable represents a list of fields
        t_field *field_table = malloc(sizeof(t_field) * meta.nbFields);

        // Retrieves the fieldNames
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table;
    }

    // STEP 2 : CREATING THE HASHTABLE

    int h;
    int nbCollisions = 0;
    int motsIndexes = 0;
    hash.slots = malloc(sizeof(t_list) * hash.nbSlots);

    while (fgets(temp, MAX_LEN, fileIn) != NULL)
    {
        t_tuple *tuple = malloc(sizeof(*tuple));

        split(meta.sep, temp, meta.nbFields, tuple->key, tuple->value);
        h = hashFunctionList[hash.hashfunction](tuple->key, hash);
        if (isEmpty(hash.slots[h]))
            nbCollisions--;
        hash.slots[h] = addHeadNode(*tuple, hash.slots[h]);
        nbCollisions++;
        motsIndexes++;
    }

    char finding[MAX_LEN];
    printf("Nombre de mots indexés : %d\nNombre de collisions : %d\n", motsIndexes, nbCollisions);
    printf("Donnez le mot à trouver : \n");
    // printf("%s", finding);
    while (scanf("%99s", finding) != EOF)
    // we can search as many word as we want until we stop the program
    {

        /* Calls the function print_tuples which handles
        the search of the specified word (finding) and displays the
        values of said key (if found) and the number of comparisons */
        print_hastable(hashFunctionList, meta, hash, finding);

        printf("\nDonnez le mot à trouver : \n");
    }

    fclose(fileIn);
}
