/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "log.h"
#include "run_interface.h"

/*CONFIGURATION DE BASE*/
#define GAME_NAME "Jeu du Taquin"

/*INITIALISATION ET PARAMETRAGE DE LA FENETRE*/
int main(void) {
	unsigned short int res;
	printlog("success", "Lancement du jeu.");
	printlog("load", "Initialisation de l'interface graphique...");
	res=InitialiserGraphique();
	if ( res == 0 ) {
		printlog("err", "Impossible d'initialiser l'interface graphique.");
		exit(1);
	}
	else {
		printlog("success", "Interface graphique initialisée.");
	}
	printlog("load", "Création de la fenêtre...");
	if ( res == 0 ) {
		printlog("err", "Impossible de créer la fenêtre.");
		exit(1);
	}
	else {
		CreerFenetre(10, 10, 1500, 844);
		printlog("success", "Fenêtre graphique créée.");
	}
	ChoisirTitreFenetre(GAME_NAME);
	printlog("load", "Ouverture d'interface...");
	res=run_interface(1);
	if (res!=0) {
		printlog("err", "Impossible d'ouvrir l'interface.");
	}
	return EXIT_SUCCESS;
}