
/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "run_animation.h"
#include "run_game.h"
#include "quit.h"
#include "wait.h"
#include "log.h"

#define DIM_BOUTONS_HAUTEUR		80 			/*hauteur (en pixel), des boutons */
#define DIM_BOUTONS_LONGUEUR	258 		/*longueur (en pxiel), des boutons */

#define BASE_POS_X				50			/*position x du menu des boutons */
#define BASE_POS_Y				325+0		/*position y du menu des boutons */

#define BOUTONS_POS_MAX_X		258			/*position x maximum des boutons */

#define B_JOUER_POS_MIN_Y		330+0		/*position y minimum du bouton "JOUER" */
#define B_JOUER_POS_MAX_Y		410+0		/*position y maximum du bouton "JOUER" */
#define B_QUITTER_POS_MIN_Y		430+0		/*position y minimum du bouton "QUITTER" */
#define B_QUITTER_POS_MAX_Y		510+0		/*position y maximum du bouton "QUITTER" */

typedef enum { clavier, souris } selecttype; /* Permet de différencier les modes "clavier" et "souris" */

void display_menu();

int run_interface(unsigned int interface) {
/* 	Interface 1 = Affichage du menu principal
	Interface 2 = Lancement du jeu (Bouton Jouer)
	Interface 3 = Affichage du menu options (Bouton Options)
	Interface 4 = Affichage des règles (Bouton Règles)
	Interface 5 = Quitte l'interface du jeu (Bouton Quitter)
*/
	if ( (interface >= 0) && (interface <= 5) ) {
		if (interface==1) {
			display_menu();
		}
		else if (interface==2) {
			printlog("load", "Ouverture de l'interface de jeu...");
			select_game();
		}
		else if (interface==3) {
			printlog("load", "Ouverture du menu options...");
		}
		else if (interface==4) {
			printlog("load", "Ouverture des règles...");
		}
		else if (interface==5) {
			printlog("load", "Fermeture du jeu en cours...");
			quit();
		}
	}
	else {
		printlog("err", "L'interface demandé est introuvable.");
		exit(1);
	}
	return EXIT_SUCCESS;
}

/*==================================================================*/

void display_menu() { /* Interface 1 */
	unsigned short int res;
	bool button_jouer_is_press;
	bool button_options_is_press;
	bool button_regles_is_press;
	bool button_quit_is_press;
	selecttype mode;

	mode					=	souris;
	button_jouer_is_press	=	false;
	button_options_is_press	=	false;
	button_regles_is_press	=	false;
	button_quit_is_press	=	false;

	printlog("success", "Menu principal ouvert.");
	printlog("load", "Chargement de l'image de fond...");
	ChargerImageFond("img/background/max-fieve-pixelsolaire.jpg");
	printlog("success", "Image de fond (re)chargée.");
	
	while (1) {
		if (mode==souris) {
			SourisPosition();
			if (SourisCliquee() == 1) {
				/* "JOUER" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_JOUER_POS_MIN_Y ) && (_Y <= B_JOUER_POS_MAX_Y )) ) {
					if (button_jouer_is_press == false) {
						printlog("success", "Bouton \"Jouer\" utilisé.");
						ChargerImage("img/button-play_push.png", ( BASE_POS_X + 5 ), B_JOUER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
						run_animation(1);
						res=run_interface(2);
						if (res!=0) {
							printlog("err", "Impossible de lancer l'interface de jeu.");
						}
						button_jouer_is_press = true;
						wait(100);
						button_jouer_is_press = false;
					}
				}
				/* "QUITTER" */
				if ( ((_X >= ( BASE_POS_X + 5 )) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_QUITTER_POS_MIN_Y ) && (_Y <= B_QUITTER_POS_MAX_Y )) ) {
					if (button_quit_is_press == false) {
						printlog("success", "Bouton \"Quitter\" utilisé.");
						ChargerImage("img/button-quit_push.png"    , ( BASE_POS_X + 5 ),  B_QUITTER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
						res=run_interface(5);
						if (res!=0) {
							printlog("err", "Impossible de fermer le jeu.");
						}
						else {
							exit(0);
						}
						button_quit_is_press = true;
						wait(100);
						button_quit_is_press = false;
					}
				}
			}
			else {
				/* "JOUER" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_JOUER_POS_MIN_Y ) && (_Y <= B_JOUER_POS_MAX_Y )) ) {
					ChargerImage("img/button-play_hover.png", ( BASE_POS_X + 5 ), B_JOUER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
				else {
					ChargerImage("img/button-play_normal.png" , ( BASE_POS_X + 5 ),  B_JOUER_POS_MIN_Y , 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR); 
				}
				/* "QUITTER" */
				if ( ((_X >= ( BASE_POS_X + 5 )) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_QUITTER_POS_MIN_Y ) && (_Y <= B_QUITTER_POS_MAX_Y )) ) {
					ChargerImage("img/button-quit_hover.png"    , ( BASE_POS_X + 5 ),  B_QUITTER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
				else {
					ChargerImage("img/button-quit_normal.png"    , ( BASE_POS_X + 5 ),  B_QUITTER_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
			}
		}
		if (mode==clavier) {
		}
	}
}
