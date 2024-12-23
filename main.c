#include "definitions.h" // Le fichier définitions.h contient toutes les fonctions utiles que l'on appellera dans main.


int main(int argc, char ** argv) {
    
    char temp[MAXLEN];

    t_metadata meta; 
    
	// On vérifie que l'utilisateur a bien correctement rentré le nom du fichier.
    if (argc<2) {
        printf("Utilisation :\n./programme <nom du fichier>\n");
        exit(EXIT_FAILURE);
    }
    
    FILE * anagrammeFile = fopen(argv[1], "r");

	// On copie des lignes du fichier anagramme jusqu'à ce qu'on obtienne la ligne du séparateur.
    fgets(temp, MAXLEN, anagrammeFile);
    while (strlen(temp) > 2){
        fgets(temp, MAXLEN, anagrammeFile);
    }
	
	// On attrape le séparateur.
    meta.sep = *temp;
	
	// On règle le cas où le séparateur est "#"
    fgets(temp, MAXLEN, anagrammeFile);
    if (meta.sep != '#') {
        while (temp[0] == '#') {
            fgets(temp, MAXLEN, anagrammeFile);
        }
		
		// On attrape le nombre de champs que l'on convertit en entier avec "atoi".
        meta.nbFields = atoi(temp);
		
		// De même, on saute toute les lignes qui sont des commentaires jusqu'à la ligne qui donne la table des champs.
        fgets(temp, MAXLEN, anagrammeFile);
            while (temp[0] == '#') {
                fgets(temp, MAXLEN, anagrammeFile);
            }
		
		// On attrape la table des champs qu'on sépare et qu'on implémente dans un tableau [clé, liste_champs]
        t_field * field_table;    
        field_table = split(meta.sep, temp);

    }
	// À ajouter cas où meta.sep == '#'...
	
    fclose(anagrammeFile);

}