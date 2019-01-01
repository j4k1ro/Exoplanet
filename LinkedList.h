/*
 * File: LinkedList.h
 * Author: Hieu Do
 * Description: Declare structs used for each exoplanet in the list maintained
 * when the program is run
 */

/* struct exoStruct */
struct exoStruct {
	char *name;
	char *mass;
	char *period;
	char *distance;

	struct exoStruct *next;
	struct exoStruct *prev;
};

/* Global variables */
struct exoStruct *head;
struct exoStruct *tail;

/* Function prototypes */
int exoInsert (char *, char *, char *, char *);
void exoAppend (char *, char *, char *, char *);
struct exoStruct *exoSearch (char *);
int exoDeleteAll (void);
