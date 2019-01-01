/*
 * File: Main.c
 * Author: Hieu Do
 * Description: Define the "main" function and the main loop (i.e. The REPL
 * display used when the program is running)
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

#ifndef HAVE_PROGRAM_H
# include "Program.h"
# define HAVE_PROGRAM_H
#endif

#ifndef HAVE_FUNCTIONS_H
# include "LinkedList.h"
# define HAVE_FUNCTIONS_H
#endif

#ifndef HAVE_MACROS_H
# include "Macros.h"
# define HAVE_MACROS_H
#endif

int mainLoop (void)
{
	head = NULL;
	tail = NULL;

	while (1) {
		fprintf (stdout, ">>> ");
        int command = fgetc (stdin);
        for (int c = fgetc(stdin); c != '\n' && c != EOF; c = fgetc(stdin))
            ;
	    switch (command) {
	    	case '0':
	    		quit ();
	    		break;
	    	case '1':
	    		printHelp ();
	    		break;
	    	case '2':
	    		importNewExo ();
	    		break;
	    	case '3':
	    		importExoFile ();
	    		break;
	    	case '4':
	    		searchExo ();
	    		break;
	    	case '5':
	    		printAllExo ();
	    		break;
	    	case '6':
	    		deleteAllExo ();
	    		break;
	    	default:
	    		printError (command);
				break;
	    }
	}
}

int main (void)
{
	fprintf (stdout, "Exoplanet table version 0.0.0.1\n");
	fprintf (stdout, "Type \'1\' (one) for the list of all possible commands.\n");
	mainLoop ();
	fprintf (stdout, "Good bye!\n");

	return 0;
}
