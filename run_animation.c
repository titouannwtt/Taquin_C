
/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "wait.h"
#include "log.h"

#define CYCLE 10000L

#define DIM_BOUTONS_HAUTEUR		80 			/*hauteur (en pixel), des boutons */
#define DIM_BOUTONS_LONGUEUR	258 		/*longueur (en pxiel), des boutons */

#define BASE_POS_X				50			/*position x du menu des boutons */
#define BASE_POS_Y				325+0		/*position y du menu des boutons */

#define BOUTONS_POS_MAX_X		258			/*position x maximum des boutons */

#define B_JOUER_POS_MIN_Y		330+0		/*position y minimum du bouton "JOUER" */
#define B_JOUER_POS_MAX_Y		410+0		/*position y maximum du bouton "JOUER" */
#define B_OPTIONS_POS_MIN_Y		430+0		/*position y minimum du bouton "OPTIONS" */
#define B_OPTIONS_POS_MAX_Y		510+0		/*position y maximum du bouton "OPTIONS" */
#define B_REGLES_POS_MIN_Y		530+0		/*position y minimum du bouton "QUITTER" */
#define B_REGLES_POS_MAX_Y		610+0		/*position y maximum du bouton "QUITTER" */
#define B_QUITTER_POS_MIN_Y		630+0		/*position y minimum du bouton "REGLES" */
#define B_QUITTER_POS_MAX_Y		710+0		/*position y maximum du bouton "REGLES" */

typedef enum { false, true } bool; /* Permet d'utiliser les termes "false" et "true" pour des variables, plutôt que "0" ou "1" */

int run_animation(unsigned int animation) {
/* 	Animation 1 = Menu vers jeu */
	char filename[50];
	int count;
	if ( (animation >= 1) && (animation <= 5) ) {
		if (animation==1) {
			count=0;
			printlog("load", "Lancement de l'animation souterraine...");
			while (count!=25) {
				count++;
				SourisCliquee(); /*Evite de lancer un clic dès que la boucle est finie si jamais l'utilisateur à cliquer quelque part */
				sprintf(filename, "img/background/animation/menu_to_option_%d.jpg", count);
				ChargerImageFond(filename);
				/* "BOUTON RETOUR" */
				ChargerImage("img/button-return_lock.png", ( BASE_POS_X + 5 ), B_JOUER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				/* "BOUTON SUIVANT" */
				ChargerImage("img/button-next_lock.png", ( BASE_POS_X + 5 ), B_OPTIONS_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				wait(8);
			}
		}
		if (animation==2) {
			count=25;
			printlog("load", "Lancement de l'animation surface...");
			while (count!=0) {
				count--;
				SourisCliquee(); /*Evite de lancer un clic dès que la boucle est finie si jamais l'utilisateur à cliquer quelque part */
				sprintf(filename, "img/background/animation/menu_to_option_%d.jpg", count);
				ChargerImageFond(filename);
				/* "BOUTON RETOUR" */
				ChargerImage("img/button-return_lock.png", ( BASE_POS_X + 5 ), B_JOUER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				/* "BOUTON SUIVANT" */
				ChargerImage("img/button-next_lock.png", ( BASE_POS_X + 5 ), B_OPTIONS_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				wait(8);
			}
		}
	}
	return EXIT_SUCCESS;
}
