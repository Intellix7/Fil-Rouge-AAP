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

    // Default number of slots
    int defaultNbSlots = 10;

    // Variable containing all the information about the hashtable
    t_hashtable hash;

    // Setting default parameters
    hash.hashfunction = defaultHash;
    hash.nbSlots = defaultNbSlots;

    /*  If neither input the file path nor the output file path are specified
        The input and the output are handled in stdIn and stdOut */
    FILE *fileIn = stdin, *fileOut = stdout;

    FILE *countFile = fopen("countFile", "w");

    // This table stores the different hash functions available
    function hashFunctionList[] = {&first_ASCII, &sum_ASCII};

    char id;
    char *string;

    for (int i = 1; i < argc; i++)
    {
        id = argv[i][1];
        string = argv[i] + 2;
        switch (id)
        {
        case 'h':
            hash.hashfunction = atoi(string);
            break;

        case 's':
            hash.nbSlots = atoi(string);
            break;

        case 'i':
            fileIn = fopen(string, "r");
            break;

        case 'o':
            fileOut = fopen(string, "w");
            break;

        case 'c':
            countFile = fopen(string, "w");
            break;

        default:
            break;
        }
    }

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

    // Step 3 : Exporting the hash Table and creating the countFile

    export_hashtable(meta, hash, fileOut, countFile);
}