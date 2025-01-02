// Define a guard (= do not include this file more than once)
#ifndef _AAP_DEFINITIONS_H
#define _AAP_DEFINITIONS_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_LEN 1000
#define MAX_FIELDS 15
#define MAX_TUPLES 60000

// ----------------------------------------------------------------------
// 1. TYPES
typedef char t_field[MAX_LEN];       // A field is a string of max. 1000 characters.
typedef t_field t_key;               // A key is a field.
typedef t_field t_value[MAX_FIELDS]; // t_value is a list of max. 60000 fields.

typedef struct
{
    char sep;     // Character which separates a field from another one.
    int nbFields; // Max number of fields contained in a line.
    t_key key;    // The key label (E.g. for anagrammes.dat, the key label is "mot")
    t_field *fieldNames;
    // The list of the field-name-labels (E.g. for anagrammes.dat, it is : ["anagramme1", "anagramme2", ..., "anagramme13"])
} t_metadata;

typedef struct
{
    // A tuple contains a key and a list of fields associated to this key.
    t_key key;
    t_value value;
} t_tuple;

typedef struct
{
    t_tuple tuples[MAX_TUPLES]; // Table of tuples
    int nbTuples;               // Number of words stored
} t_tupletable;

typedef struct node
{
    t_tuple data;
    struct node *pNext;
} t_node;

typedef t_node *t_list;

typedef struct
{
    int hashfunction; // hash function ID
    int nbSlots;      // Number of slots
    t_list *slots;    // Slots table
} t_hashtable;

// special type for a list of hash function pointers
typedef int (*function)(t_key, t_hashtable);

// ----------------------------------------------------------------------
// 2. PROTOTYPES AND DOCUMENTATION

// 2.1 HELPER FUNCTIONS

void split(char sep, char *txt, int nbFields, t_key key, t_field *schema_field_table);

/*
split takes 5 parameters :
    - char sep : the separator
    - char * txt : string of characters that we want to split (E.g. : "key:ana1:ana2:ana3")
    - int nbFields : the max number of fields contained in a line.
    - t_key key : field which awaits for the key to be stored in it...
    - t_field * schema_field_table : list of fields which awaits for all the fields to be stored in it...

It returns nothing but stores the key & all the field names from "txt" in "key" and "schema_field_table".
*/

void print_tuples(t_metadata data, t_tupletable *dico, char *key);

/*
print_tuples takes 3 parameters :
    - t_metadata data : it allows to access fieldNames, nbFields and key.
    - t_tupletable * dico : pointer towards the dictionnary, which is a list of tuples. E.g. : [[key1, [ana1.1, ana1.2]], [key2, [ana2.1, ana2.2, ana2.3]]]*
    - key : the key to search in the dictionnary


It should display something like the following :
"[...] mots indexés"
"Saisir les mots recherchés : " (scanf)
--> If the key is found, then proceed to display the following :
"Recherche de [key] : trouvé ! nb comparaisons : [...]"
"mot : ..."
"anagramme 1: ..."
"anagramme 2: ..."
"anagramme 3: X" (display "X" if there is no more anagram)
...
"anagramme [nbFields]: X"

--> If the key is not found, then proceed to display the following :
"Recherche de [key] : échec ! nb comparaisons : [...]"
*/

void print_hastable(function *hashFunctionList, t_metadata data, t_hashtable hash, t_key key);
/* Takes 4 parameters :
    - The hash function list
    - t_metadata data which contains information about parsed file
    - t_hashtable hash which contains information about the hash table
    - the key to search for
Does the same thing as print_tuples but with the hash table implementation */

void export_hashtable(t_metadata data, t_hashtable hash, FILE *fileOut, FILE *countFile);
/* Takes 4 parameters :
    - Data about parsed file
    - Data about the hash table
    - The output file where the hash table will be exprted
    - The countfile where information about slot occupation will be exported */

// 2.2 CHAINED LIST FUNCTIONS

int isEmpty(t_list li);

t_tuple getFirstVal(t_list li);

t_list newList();

t_list addHeadNode(t_tuple data, t_list li);

t_list removeHeadNode(t_list li);

// 2.3 HASH FUNCTIONS

int first_ASCII(t_key key, t_hashtable hash);

/* 	first_ASCII takes two parameters :
    - a key
    - a t_hashtable object holding the information about the hashtable
Returns the ASCII code of its first character mod hash.nbslots */

int sum_ASCII(t_key, t_hashtable hash);

/* 	first_ASCII takes two parameters :
    - a key
    - a t_hashtable object holding the information about the hashtable
Returns the sum of the ASCII codes of all the characters in key mod hash.nbslots */

// ----------------------------------------------------------------------
// 3. FUNCTIONS

// 3.1 HELPER FUNCTIONS

void split(char sep, char *txt, int nbFields, t_key key, t_field *schema_field_table)
{
    int l = strlen(txt); // strlen gives the length of whole string given in parameters.
    int k = 0, i = 0, j = 0;

    // This first while loop retrieves the key
    while ((txt[i] != sep) && (txt[i] != '\0'))
    {
        key[i] = txt[i];
        i++;
    }

    key[i] = '\0';

    // places cursor on the beginning of the next field
    i++;

    /* 	This loop retrieves all the fields while separating words between
        the separator and ignoring \n and \0 characters */
    while ((i < l) && (k < nbFields))
    {
        while ((txt[i] != sep) && (txt[i] != '\0') && (txt[i] != '\n') && (txt[i] != '\r'))
        {
            schema_field_table[k][j] = txt[i];
            j++;
            i++;
        }
        k++;
        i++;
        j = 0;
    }
}

void print_tuples(t_metadata data, t_tupletable *dico, char *key)
{
    int index_key = 0;
    int found = 0;
    for (int i = 0; i < dico->nbTuples; i++)
    {
        /* 	Looking for the key inside the dictionnary. strcmp checks if
            2 strings are equal and returns 0 if that's the case. */
        if (strcmp(key, dico->tuples[i].key) == 0)
        {
            found = 1;
            break;
        }
        index_key++;
    }
    if (!found)
    {
        printf("Recherche de %s : échec ! nb comparaisons : %d\n", key, index_key);
    }
    else
    {
        printf("Recherche de %s : trouvé ! nb comparaisons : %d\n", key, index_key + 1);
        printf("%s : %s\n", data.key, key); // mot : key

        for (int k = 0; k < data.nbFields - 1; k++)
        {
            if ((dico->tuples[index_key].value[k][0] != '\0'))
            {
                printf("%s: %s\n", data.fieldNames[k], dico->tuples[index_key].value[k]); // anagramme k: ...
            }
            else if (strcmp(data.fieldNames[k], "") != 0)
            {
                printf("%s: X\n", data.fieldNames[k]); // anagramme k: X
            }
        }
    }
}

void print_hastable(function *hashFunctionList, t_metadata data, t_hashtable hash, t_key key)
{
    int h = hashFunctionList[hash.hashfunction](key, hash);
    int nbComparisons = 0;
    t_list temp = hash.slots[h];
    while ((!isEmpty(temp)) && (strcmp(temp->data.key, key) != 0))
    {
        nbComparisons++;
        temp = temp->pNext;
    }

    if (temp == NULL)
    {
        printf("Recherche de %s : échec ! nb comparaisons : %d\n", key, nbComparisons + 1);
    }
    else
    {
        printf("Recherche de %s : trouvé ! nb comparaisons : %d\n", key, nbComparisons + 1);
        printf("%s : %s\n", data.key, key);

        for (int k = 0; k < data.nbFields - 1; k++)
        {
            if (temp->data.value[k][0] != '\0')
            {
                printf("%s: %s\n", data.fieldNames[k], temp->data.value[k]);
            }
            else if (strcmp(data.fieldNames[k], "") != 0)
            {
                printf("%s: X\n", data.fieldNames[k]);
            }
        }
    }
}

void export_hashtable(t_metadata data, t_hashtable hash, FILE *fileOut, FILE *countFile)
{
    // Arbitrary choice...
    char tupleSeparator = '<';

    t_list temp_list;
    int k;
    int nbKey;
    // Prints to output file relevant information to reconstruct the hash table if needed
    fprintf(fileOut, "%c\n%c\n%d\n%d\n%d\n", data.sep, tupleSeparator, data.nbFields, hash.hashfunction, hash.nbSlots);

    // Print Field names to output file
    fprintf(fileOut, "%s", data.key);
    for (int i = 0; i < data.nbFields; i++)
    {
        fprintf(fileOut, "%c%s", data.sep, data.fieldNames[i]);
    }

    fprintf(fileOut, "\n");

    // Goes through all slots
    for (int i = 0; i < hash.nbSlots; i++)
    {
        temp_list = hash.slots[i];

        // prints to the count file the slot number
        fprintf(countFile, "%d,", i);

        // Prints each tuple in the slot on the same line, separated by the tupleSeparator
        nbKey = 0;
        while (!isEmpty(temp_list))
        {
            fprintf(fileOut, "%s", temp_list->data.key);
            k = 0;

            while ((temp_list->data.value[k][0] != '\0') && (k < data.nbFields - 1))
            {
                fprintf(fileOut, "%c%s", data.sep, temp_list->data.value[k]);
                k++;
            }

            fprintf(fileOut, "%c", tupleSeparator);
            temp_list = temp_list->pNext;
            nbKey++;
        }

        // Prints the slot occupation to count file
        fprintf(countFile, " %d\n", nbKey);
        fprintf(fileOut, "\n");
    }
}

// 3.2 CHAINED LIST FUNCTIONS

int isEmpty(t_list li)
{
    return (li == NULL);
}

t_tuple getFirstVal(t_list li)
{
    assert(!isEmpty(li));
    return li->data;
}

t_list newList()
{
    t_list li = NULL;
    return li;
}

t_list addHeadNode(t_tuple data, t_list li)
{
    t_node *n = malloc(sizeof(t_node));
    n->data = data;
    n->pNext = li;
    return n;
}

t_list removeHeadNode(t_list li)
{
    assert(!isEmpty(li));
    t_list p = li->pNext;
    free(li);
    return p;
}

// 3.3 HASH FUNCTIONS

int first_ASCII(t_key key, t_hashtable hash)
{
    return (int)(key[0] % hash.nbSlots);
}

int sum_ASCII(t_key key, t_hashtable hash)
{
    int s = 0;
    for (size_t i = 0; i < strlen(key); i++)
    {
        s += (int)key[i];
    }
    return (s % hash.nbSlots);
}

#endif
