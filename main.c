// include a file that contains all type definitions and function declarations
#include "definitions.h"


int main(int argc, char ** argv) {
    
    char finding;
    printf("Donnez le mot à trouver :");
    scanf("%c", &finding);

    // Creating the temporary string that will hold the text retrieved from the file
    char temp[MAXLEN];
     
    // variable containing the metadatas from the file
    t_metadata meta; 
    
    // halts the program if the user uses the wrong syntax
    if (argc<2) {
        printf("Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }
    
    FILE * anagrammeFile = fopen(argv[1], "r");

    // Retrieves the separator from the file
    // A line is only read if it contains only one character
    fgets(temp, MAXLEN, anagrammeFile);
    while (strlen(temp) > 2){
        fgets(temp, MAXLEN, anagrammeFile);
    }
    meta.sep = *temp;
    // printf("%c\n", meta.sep);

    // if the # is not the separator, then it means we have to ignore every line starting with #
    if (meta.sep != '#') {
        fgets(temp, MAXLEN, anagrammeFile);
        while (temp[0] == '#') {
            fgets(temp, MAXLEN, anagrammeFile);
        }
        // Retrieves the number of fields
        meta.nbFields = atoi(temp);
        // printf("%d", meta.nbFields);

        // This variable represents a list of fields 
        t_field * field_table = malloc(sizeof(t_field) * meta.nbFields); 

        fgets(temp, MAXLEN, anagrammeFile);
        // Then again, we ignore lines starting with #
            while (temp[0] == '#') {
                fgets(temp, MAXLEN, anagrammeFile);
            }

        // Retrieves the fieldNames  
        split(meta.sep, temp, field_table);
        meta.fieldNames = field_table;
        // print_fields(meta.fieldNames); 

        t_tupletable * dico1 = malloc(sizeof(t_tupletable)); /*creation of the "tableau classique"*/
        int len_dic = 0;
        fgets(temp, MAXLEN, anagrammeFile);
        while(strlen(temp)>0){ /* filling the keys */
            int i = 0;
            int j = 0; 
            printf("%c", *temp);
            while(temp[i] =! meta.sep){
                dico1->tuples->key[j]=temp[i];
                j = j+1;
                i = i+1;
                printf("%d %d \n", j, i);

            }
            i=i+1;
            printf("%c", dico1->tuples->key[5]);
            
            while(temp[i] =! "\n"){ //filling the values
                *(dico1->tuples->value[j])=temp[i];
                j = j+1;
                i = i+1;  
            }
        len_dic++;    
        fgets(temp, MAXLEN, anagrammeFile);    
        }
        dico1->nbTuples = len_dic;


        for(int k=0; k < dico1->nbTuples; k++){
            if(strcmp(&finding, dico1->tuples[k].key)==0){
                printf("%d mots indexés \n", dico1->nbTuples);
                printf("Recherche de %c : trouvé ! nb comparaisons : %d \n", finding, k);
                break;
            }
        
        }
         
    }
	else {
        // Case where # is the separator.
        // We then assume that there are no comment line after the separator declaration
        fgets(temp, MAXLEN, anagrammeFile);
        meta.nbFields = atoi(temp);
        fgets(temp, MAXLEN, anagrammeFile);

        // This variable represents a list of fields
        t_field * field_table = malloc(sizeof(t_field) * meta.nbFields); 
        
        split(meta.sep, temp, field_table);
        meta.fieldNames = field_table;
    }


	
    fclose(anagrammeFile);

}