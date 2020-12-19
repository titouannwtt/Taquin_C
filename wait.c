/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "wait.h"

#define CYCLE 100000L

/*PERMET DE METTRE UN DELAI (en millisecondes)*/
int wait(unsigned long time) {
	unsigned long suivant;
	suivant=Microsecondes()+CYCLE;
	while(1) {
		if (Microsecondes()>suivant) {
			suivant = Microsecondes()+CYCLE;
			if (suivant>time) {
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}