// Include a file that contains all type definitions and functions.
#include "../definitions.h"

int main(int argc, char **argv)
{
    // Creates the temporary string that will hold the text retrieved from the file.
    char temp[MAX_LEN];

    // Variable containing all the information about the hashtable
    t_hashtable hash;

    // Variable containing the metadatas from the file (SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES).
    t_metadata meta;

    function hashFunctionList[] = {&first_ASCII, &sum_ASCII};

    // Halts the program if the user uses the wrong syntax.
    if (argc < 2)
    {
        printf(
            "Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }

    // Opens the datafile.
    FILE *hashFile = fopen(argv[1], "r");

    fgets(temp, MAX_LEN, hashFile);
    meta.sep = *temp;

    fgets(temp, MAX_LEN, hashFile);
    meta.nbFields = atoi(temp);

    fgets(temp, MAX_LEN, hashFile);
    hash.hashfunction = atoi(temp);

    fgets(temp, MAX_LEN, hashFile);
    hash.nbSlots = atoi(temp);

    fgets(temp, MAX_LEN, hashFile);
    t_field *fieldTable = malloc(sizeof(t_field) * meta.nbFields);
    split(meta.sep, temp, meta.nbFields, meta.key, fieldTable);
    meta.fieldNames = fieldTable;

    int k = 0;
    int nbCollisions = 0;
    int motsIndexes = 0;

    hash.slots = malloc(sizeof(t_list) * hash.nbSlots);

    while (fgets(temp, MAX_LEN, hashFile) != NULL)
    {
        if (temp[0] == '#')
        {
            k = atoi(temp + 1);
            // printf("%d\n", k);
            continue;
        }

        t_tuple *tuple = malloc(sizeof(*tuple));

        split(meta.sep, temp, meta.nbFields, tuple->key, tuple->value);
        if (isEmpty(hash.slots[k]))
            nbCollisions--;
        hash.slots[k] = addHeadNode(*tuple, hash.slots[k]);
        nbCollisions++;
        motsIndexes++;
    }

    char finding[MAX_LEN];
    printf("Nombre de mots indexés : %d\nNombre de collisions : %d\n", motsIndexes, nbCollisions);
    printf("Donnez le mot à trouver : \n");
    // printf("%s", finding);
    while (scanf("%99s", finding) != EOF)
    {
        // we can search as many word as we want until we stop the program
        print_hastable(hashFunctionList, meta, hash, finding);
        printf("\nDonnez le mot à trouver : \n");
    }

    fclose(hashFile);
}
