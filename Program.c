/*
 * File: Program.c
 * Author: Hieu Do
 * Description: Define general functions used in the program
 */

#ifndef HAVE_STDLIB_H
# include <stdlib.h>
# define HAVE_STDLIB_H
#endif
#ifndef HAVE_STRING_H
# include <string.h>
# define HAVE_STRING_H
#endif
#ifndef HAVE_STDIO_H
# include <stdio.h>
# define HAVE_STDIO_H
#endif

#ifndef HAVE_MACROS_H
# include "Macros.h"
# define HAVE_MACROS_H
#endif

#ifndef HAVE_LINKED_LIST_H
# include "LinkedList.h"
# define HAVE_LINKED_LIST_H
#endif

/* Import a new exoplanet by entering data from the keyboard */
void importNewExo (void)
{
	char *name = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *mass = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *period = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *distance = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));

	printf ("Name: "); 		scanf ("%s", name);
	printf ("Mass: "); 		scanf ("%s", mass);
	printf ("Period: "); 	scanf ("%s", period);
	printf ("Distance: "); 	scanf ("%s", distance);

	fprintf (stdout, "%s\n", distance);

	int success = exoInsert (name, mass, period, distance);
	if (success) {
		fprintf (stdout, "\"%s\" imported successfully.\n", name);
	}
	else {
		fprintf (stdout, "\"%s\" can't be imported, \
the entry might have already existed.\n", name);
	}

    free (name);
    free (mass);
    free (period);
    free (distance);
}

/* Import list of exoplanets from file ExopData.csv located in current 
 * directory. The file has been formatted so as to provide simple data
 * retrieve. The script Exop.py was used to retrieve the file.
 *
 * Can't check for duplication at the moment.
 */
void importExoFile (void)
{
	FILE *exoData = fopen ("./ExopData.csv", "r");
	char *line = (char *)malloc (MAX_LINE_LIMIT * sizeof *line);

	char *name = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *mass = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *period = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));
	char *distance = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));

	int planets = 0;

	while (fgets (line, MAX_LINE_LIMIT, exoData)) {
		name = strtok (line, ",");
		mass = strtok (NULL, ",");
		period = strtok (NULL, ",");
		distance = strtok (NULL, "\n");

		exoAppend (name, mass, period, distance);
		planets++;
	}
	fclose (exoData);
    free (line);
	fprintf (stdout, "File import success, %i planets imported.\n", planets);
}

void printHorizontalLine (void)
{
	for (int i = 0; i < 68; i++) {
		if (i == 0 || i == 25 || i == 41 || i == 54 || i == 67) {
			fprintf (stdout, "+");
		}
		else {
			fprintf (stdout, "-");
		}
	}
	fprintf (stdout, "\n");
}

void printHeader (void)
{
	printHorizontalLine ();
	fprintf (stdout, "|%-24s|%-15s|%-12s|%-12s|\n", 
			 "NAME", 
			 "MASS", 
			 "PERIOD", 
			 "DISTANCE");
	printHorizontalLine ();
}

void searchExo (void)
{
	char *searchTerm = (char *)malloc (MAX_ENTRY_LIMIT * sizeof (char));

	fprintf (stdout, "Enter exoplanet's name: ");
	fscanf (stdin, "%s", searchTerm);
	struct exoStruct *foundExo = exoSearch (searchTerm);
    free (searchTerm);

	if (foundExo) {
		printHeader();
		fprintf (stdout, "|%-24s|%-15s|%-12s|%-12s|\n", 
				 foundExo->name,
				 foundExo->mass,
				 foundExo->period,
				 foundExo->distance);
		printHorizontalLine ();
	}
	else {
		fprintf (stdout, "\"%s\" does not exist.\n", searchTerm);
	}
}

void printAllExo (void)
{
	struct exoStruct *currentExo = head;

	if (head != NULL) {
		printHeader ();
	    while (currentExo != NULL) {
	    	fprintf (stdout, "|%-24s|%-15s|%-12s|%-12s|\n", currentExo->name,
	    			 currentExo->mass,
	    			 currentExo->period,
	    			 currentExo->distance);
			printHorizontalLine ();

	    	currentExo = currentExo->next;
		}
	}
	else {
		fprintf (stderr, "The list is currently empty.\n");
	}
}

void deleteAllExo (void)
{
	int status = exoDeleteAll ();
	if (!status) {
		fprintf (stderr, "Can't delete, the list is empty\n");
	}
}

void printHelp (void)
{
	fprintf (stdout, "\
List of available commands:\n\
	0 -- quit\n\
	1 -- open help\n\
	2 -- import new exo, enter from the key board\n\
	3 -- import new exo from file\n\
	4 -- search exo by name, enter from the key board\n\
	5 -- print all exo currently in the list\n\
	6 -- delete all exo in the list\n");
}

void printError (int error)
{
	fprintf (stderr, "Unregconized command \'%c\'.\n", (error > 32 && error < 128 ? error : '?'));
}

void quit (void)
{
	fprintf (stdout, "Exoplanets are being deleted...\n");
	deleteAllExo ();
	fprintf (stdout, "Program quit now.\n");
	exit (EXIT_SUCCESS);
}
