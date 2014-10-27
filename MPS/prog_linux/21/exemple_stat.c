
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/stat.h>

	void
affiche_status (struct stat * status)
{
	if (S_ISBLK (status -> st_mode))
		fprintf (stderr, "bloc ");
	else if (S_ISCHR (status -> st_mode))
		fprintf (stderr, "caract�re ");
	else if (S_ISDIR (status -> st_mode))
		fprintf (stderr, "r�pertoire ");
	else if (S_ISFIFO (status -> st_mode))
		fprintf (stderr, "fifo ");
	else if (S_ISLNK (status -> st_mode))
		fprintf (stderr, "lien ");
	else if (S_ISREG (status -> st_mode))
		fprintf (stderr, "fichier ");
	else if (S_ISSOCK (status -> st_mode))
		fprintf (stderr, "socket ");
	fprintf (stderr, "u:");
	fprintf (stderr, status -> st_mode & S_IRUSR ? "r" : "-");
	fprintf (stderr, status -> st_mode & S_IWUSR ? "w" : "-");
	fprintf (stderr, status -> st_mode & S_IXUSR ? "x" : "-");
	fprintf (stderr, " g:");
	fprintf (stderr, status -> st_mode & S_IRGRP ? "r" : "-");
	fprintf (stderr, status -> st_mode & S_IWGRP ? "w" : "-");
	fprintf (stderr, status -> st_mode & S_IXGRP ? "x" : "-");
	fprintf (stderr, " o:");
	fprintf (stderr, status -> st_mode & S_IROTH ? "r" : "-");
	fprintf (stderr, status -> st_mode & S_IWOTH ? "w" : "-");
	fprintf (stderr, status -> st_mode & S_IXOTH ? "x" : "-");
	fprintf (stderr, "\n");
}	


	int
main (int argc, char * argv [])
{
	struct stat status;
	int	i;

	if (argc == 1) {
		fprintf (stderr, "stdin : ");
		if (fstat (STDIN_FILENO, & status) < 0)
			perror ("");
		else
			affiche_status (& status);
		fprintf (stderr, "stdout : ");
		if (fstat (STDOUT_FILENO, & status) < 0)
			perror ("");
		else
			affiche_status (& status);
	} else {
		for (i = 1; i < argc ; i ++) {
			fprintf (stderr, "%s : ", argv [i]);
			if (stat (argv [i], & status) < 0)
				perror ("");
			else
				affiche_status (& status);
		}
	}
	return (0);
}
