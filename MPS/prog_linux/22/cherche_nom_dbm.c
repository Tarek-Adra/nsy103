	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <gdbm/dbm.h>

	void affiche_contributeur (datum cle, datum donnee);
	
	
	int
main (int argc,char * argv [])
{
	datum  cle;
	datum  donnee;
	char   chaine [256];
	char * fin_chaine;
	
	if (argc != 2) {
		fprintf (stderr, "Syntaxe : %s nom_base\n", argv [0]);
		exit (1);
	}
	if (dbminit (argv [1]) != 0) {
		perror ("dbminit");
		exit (1);
	}
	while (1) {
		fprintf (stdout, "Nom : ");
		if (fgets (chaine, 256, stdin) == NULL)
			break;
		if ((fin_chaine = strpbrk (chaine, "\n\r ")) != NULL)
			* fin_chaine = '\0';
		if (strlen (chaine) == 0)
			continue;
		for (cle = firstkey (); cle . dptr != NULL; cle = nextkey (cle)) {
			donnee = fetch (cle);
			if (donnee . dptr != NULL)
				if (strstr (donnee . dptr, chaine) != NULL)
					affiche_contributeur (cle, donnee);
		}	
	}
	fprintf (stdout, "\n");
	dbmclose ();
	return (0);
}

	void
affiche_contributeur (datum cle, datum donnee)
{
	char * nom;
	char * email;
	char * web;
	
	nom = donnee . dptr;
	email = & (nom   [strlen (nom)   + 1]);
	web   = & (email [strlen (email) + 1]);

	fprintf (stdout, "Numero : %d\n", * ((int *) cle . dptr));
	fprintf (stdout, "  Nom      : %s\n", nom); 
	fprintf (stdout, "  Email    : %s\n", email);
	fprintf (stdout, "  Web      : %s\n", web);
}
