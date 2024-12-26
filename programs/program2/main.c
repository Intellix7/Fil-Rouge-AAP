// Include a file that contains all type definitions and functions.
#include "../definitions.h"


int main(int argc, char ** argv) {

    // Creates the temporary string that will hold the text retrieved from the file.
    char temp[MAXLEN];
     
    // Variable containing the metadatas from the file (SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES).
    t_metadata meta;

    // Default hash function
    int defaultHash = 0;

    // Variable containing all the information about the hashtable
    t_hashtable hash;
    
    // Halts the program if the user uses the wrong syntax.
    if (argc < 3) {
        printf("Utilisation :\n./programme <nom du fichier> <nombre d'alvéoles> <nom de la fonction de hachage (facultatif)>\n");
        exit(EXIT_FAILURE);
    }
    
	// Opens the datafile.
    FILE * anagrammeFile = fopen(argv[1], "r");

    // Stores the number of slots of the hash function
    int nbAlveoles = atoi(argv[2]);

    // Sets the hash function to be used, default being first_ASCII
    hash.hashfunction = defaultHash;
    if (argc == 4) {
        hash.hashfunction = atoi(argv[3]);
    }
    function hashFunctionList[] = {&first_ASCII};

	// STEP 1 : IMPLEMENTING METADATA WITH : SEPARATOR, NB_OF_FIELDS, KEY_NAME, FIELD_NAMES
    
	// STEP 1.1 : SEPARATOR
    fgets(temp, MAXLEN, anagrammeFile);
    while (strlen(temp) > 2) {     // A line is only read if it contains only one character.
        fgets(temp, MAXLEN, anagrammeFile);
    }
    meta.sep = *temp; 	// Gets separator.

	// STEP 1.2 : NB_OF_FIELDS & FIELD_NAMES
    if (meta.sep != '#') {     // if the # is not the separator, then it means we have to ignore every line starting with #.
        fgets(temp, MAXLEN, anagrammeFile);
        while (temp[0] == '#') {
            fgets(temp, MAXLEN, anagrammeFile);
        }
		
        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);

        // This variable represents a list of fields. 
        t_field * field_table = malloc(sizeof(t_field) * meta.nbFields); 

        fgets(temp, MAXLEN, anagrammeFile);
        // Then again, we ignore lines starting with #.
            while (temp[0] == '#') {
                fgets(temp, MAXLEN, anagrammeFile);
            }

        // Retrieves the fieldNames  
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table;
        free(field_table);       
    }
	
	else {
        // Case where # is the separator.
        // We then assume that there are no comment line after the separator declaration.
        fgets(temp, MAXLEN, anagrammeFile);
		
        // Retrieves the number of fields.
        meta.nbFields = atoi(temp);
		
        fgets(temp, MAXLEN, anagrammeFile);

        // This variable represents a list of fields
        t_field * field_table = malloc(sizeof(t_field) * meta.nbFields); 

        // Retrieves the fieldNames  
        split(meta.sep, temp, meta.nbFields, meta.key, field_table);
        meta.fieldNames = field_table; 
        free(field_table);
    }

	// STEP 2 : CREATING THE HASHTABLE

    int h = 0;
    int nbCollisions;
    hash.slots = malloc(sizeof(t_list) * hash.nbSlots);
    
    while (fgets(temp, MAXLEN, anagrammeFile) != NULL) {
        t_tuple * tuple = malloc(sizeof(*tuple));
        split(meta.sep, temp, meta.nbFields, tuple->key, tuple->value);
        h = hashFunctionList[hash.hashfunction](tuple->key, hash);
        if (isEmpty(hash.slots[0])) nbCollisions--;
        addHeadNode(*tuple, hash.slots[0]);
        nbCollisions++;
    }


	
    

	
    // char finding[MAXLEN];
    // printf("Donnez le mot à trouver : \n");
    // // printf("%s", finding);
    // while (scanf("%99s", finding) != EOF){// we can search as many word as we want until we stop the program

    //     /* Calls the function print_tuples which handles 
    //     the search of the specified word (finding) and displays the 
    //     values of said key (if found) and the number of comparisons */
    //     print_tuples(meta, dico1, finding);
       
    //     printf("\nDonnez le mot à trouver : \n");

    // }

    
	
    fclose(anagrammeFile);

}