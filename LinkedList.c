/*
 * File: LinkedList.c
 * Author: Hieu Do
 * Description: Implement functions used with the list defined in LinkedList.h
 */
#ifndef HAVE_STDLIB_H
# include <stdlib.h>
# define HAVE_STDLIB_H
#endif
#include <string.h>
#ifndef HAVE_STDIO_H
# include <stdio.h>
# define HAVE_STDIO_H
#endif

#ifndef HAVE_MACROS_H
# include "Macros.h"
# define HAVE_MACROS_H
#endif

#ifndef HAVE_LINKEDLIST_H
# include "LinkedList.h"
# define HAVE_LINKEDLIST_H
#endif

/* This can be used with -std=gnu11, just an alternative written by me */
char *strdup (char *str)
{
	char *dest = (char *)malloc ((strlen (str) + 1) * sizeof (char));
	int i = 0;
	for (i = 0; str[i] != '\0'; i++) {
		dest[i] = str[i];
	}
	dest[i] = '\0';
	return dest;
}

struct exoStruct *getNewExo (char *name, char *mass, char *period, char *distance)
{
	struct exoStruct *newExo = (struct exoStruct *)malloc (sizeof (struct exoStruct));

	newExo->name = name;
	newExo->mass = mass;
	newExo->period = period;
	newExo->distance = distance;

	newExo->prev = NULL;
	newExo->next = NULL;

	return newExo;
}

/* Insert exoplanet newExo at the right place based on ASCII order */
int exoInsert (char *name, char *mass, char *period, char *distance)
{
	struct exoStruct *newExo = getNewExo (strdup (name), 
								 		  strdup (mass), 
								 		  strdup (period), 
								 		  strdup (distance));
	struct exoStruct *currentExo = head;

	if (head == NULL) {
		head = newExo;
		tail = newExo;
		newExo->next = NULL;
		newExo->prev = NULL;
	}
	else {
		// Search for the right place to insert new exoplanet
		while (currentExo->next != NULL && strcmp (currentExo->name, name) > 0) {
			currentExo = currentExo->next;
		}
		// Avoid adding the same entry multiple time
		if (strcmp (currentExo->name, name) == 0) {
			return FAILURE;
		}
		// Insert the exoplanet
		newExo->next = currentExo;
		if (currentExo->prev == NULL) {
			newExo->prev = NULL;
			head = newExo;
		}
		else {
			newExo->prev = currentExo->prev;
			currentExo->next->prev = newExo;
		}
		currentExo->prev = newExo;
	}
	return SUCCESS;
}

/* Append exoplanet newExo at the end of the list */
void exoAppend (char *name, char *mass, char *period, char *distance)
{
	struct exoStruct *newExo = getNewExo (strdup (name), 
								 		  strdup (mass), 
								 		  strdup (period), 
								 		  strdup (distance));
	struct exoStruct *currentExo = tail;

	if (tail == NULL) {
		head = newExo;
		tail = newExo;
	}
	else {
		newExo->prev = currentExo;
		currentExo->next = newExo;
		tail = newExo;
	}
}

struct exoStruct *exoSearch (char *searchTerm)
{
	struct exoStruct *currentExo = head;
	while (currentExo != NULL) {
		if (strcmp (currentExo->name, searchTerm) == 0) {
			return currentExo;
		}
		currentExo = currentExo->next;
	}
	return NULL;
}

int exoDeleteAll (void)
{
	if (head == NULL) {
		return FAILURE;
	}
	struct exoStruct *currentExo = NULL;

	while (head != NULL) {
		currentExo = head;
		head = currentExo->next;

        free (currentExo->name);
        free (currentExo->mass);
        free (currentExo->distance);
        free (currentExo->period);
		free (currentExo);
	}
	return SUCCESS;
}
