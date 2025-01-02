// Include a file that contains all type definitions and functions.
#include "../definitions.h"

int main(int argc, char **argv)
{
    // Creates the temporary string that will hold the text retrieved from the file.
    char *temp = malloc(MAX_LEN * MAX_TUPLES);

    // Variable containing all the information about the hashtable
    t_hashtable hash;

    // Variable containing the metametas from the file (SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES).
    t_metadata meta;

    // Halts the program if the user uses the wrong syntax.
    if (argc < 2)
    {
        printf(
            "Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }

    // Opens the datafile.
    FILE *hashFile = fopen(argv[1], "r");

    // Retrieves the char that separates values within a tuple
    fgets(temp, MAX_LEN, hashFile);
    meta.sep = *temp;

    // Retrieves tuple separators
    fgets(temp, MAX_LEN, hashFile);
    char tupleSeparator[] = {*temp, '\0'};

    // Retrieves the number of fields
    fgets(temp, MAX_LEN, hashFile);
    meta.nbFields = atoi(temp);

    // Retrieves the number of the hash function
    fgets(temp, MAX_LEN, hashFile);
    hash.hashfunction = atoi(temp);

    // Retrieves the number slots
    fgets(temp, MAX_LEN, hashFile);
    hash.nbSlots = atoi(temp);

    // Retrieves the fields
    fgets(temp, MAX_LEN, hashFile);
    t_field *fieldTable = malloc(sizeof(t_field) * meta.nbFields);
    split(meta.sep, temp, meta.nbFields, meta.key, fieldTable);
    meta.fieldNames = fieldTable;

    // Gets the position of the cursor in the file at the beginning of the data lines
    int origin = ftell(hashFile);

    char finding[MAX_LEN];
    int h;
    int nbComparisons;
    char *tuple;
    t_key key;
    t_field *values = malloc(sizeof(t_field) * meta.nbFields);
    printf("Donnez le mot à trouver :\n");

    // Here we use fgets to be able to parse sentences with spaces in them
    while (fgets(finding, MAX_LEN, stdin) != NULL)
    // The loops keeps running until the users enters the EOF charatcer by pressing ctrl + D
    {
        // Removes the end of line character at the end of user input
        finding[strcspn(finding, "\r\n")] = 0;

        // Resets the cursor position
        fseek(hashFile, origin, SEEK_SET);

        // Compute the hash value of searched key
        h = hashFunctionList[hash.hashfunction](finding, hash);
        nbComparisons = 0;

        // This loop places the cursor at the line corresponding to the hash value
        for (int i = 0; i < h + 1; i++)
        {
            fgets(temp, MAX_LEN * MAX_TUPLES, hashFile);
        }

        // strtok reads temp until it hits the tupleSeparator, yielding the first tuple
        tuple = strtok(temp, tupleSeparator);
        split(meta.sep, tuple, meta.nbFields, key, values);

        // This loop runs until we hit the right key or we run out of tuples
        while ((tuple != NULL) && ((strcmp(key, finding) != 0)))
        {
            nbComparisons++;
            tuple = strtok(NULL, tupleSeparator);
            free(values);
            values = calloc(sizeof(t_field), meta.nbFields);
            if (tuple != NULL)
                split(meta.sep, tuple, meta.nbFields, key, values);
        }

        // Display management
        if (tuple == NULL)
        {
            printf("Recherche de %s : échec ! nb comparaisons : %d\n", finding, nbComparisons + 1);
        }
        else
        {
            printf("Recherche de %s : trouvé ! nb comparaisons : %d\n", finding, nbComparisons + 1);
            printf("%s : %s\n", meta.key, key);

            for (int k = 0; k < meta.nbFields - 1; k++)
            {
                if (values[k][0] != '\0')
                {
                    printf("%s: %s\n", meta.fieldNames[k], values[k]);
                }
                else if (strcmp(meta.fieldNames[k], "") != 0)
                {
                    printf("%s: X\n", meta.fieldNames[k]);
                }
            }
        }

        printf("\nDonnez le mot à trouver :\n");
    }

    fclose(hashFile);
}
