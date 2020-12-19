
/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "run_animation.h"
#include "run_interface.h"
#include "wait.h"
#include "log.h"
#include <time.h>

#define DIM_NUMBER						100 	/*Dimension (en pixel), des nombres (de forme carré, utilisés pour les lignes et les colonnes) */
#define DIM_ICONE						200 	/*Dimension (en pixel), des icones (de forme carré, représentant les images) */
#define DIM_BOUTONS_HAUTEUR				80 		/*hauteur (en pixel), des boutons */
#define DIM_BOUTONS_LONGUEUR			258 	/*longueur (en pxiel), des boutons */

#define BASE_POS_X						50		/*position x du menu des boutons */
#define BASE_POS_Y						325		/*position y du menu des boutons */

#define BOUTONS_POS_MAX_X				258		/*position x maximum des boutons */

#define B_RETURN_POS_MIN_Y				330		/*position y minimum du bouton "RETOUR" */
#define B_RETURN_POS_MAX_Y				410		/*position y maximum du bouton "RETOUR" */
#define B_SUIVANT_POS_MIN_Y				430		/*position y minimum du bouton "SUIVANT" */
#define B_SUIVANT_POS_MAX_Y				510		/*position y maximum du bouton "SUIVANT" */

#define IMG_FIRST_TEXT_POS_X			788		/*position x du premier text de ligne/colonne */
#define IMG_FIRST_TEXT_POS_Y			320		/*position y du premier text de ligne/colonne */
#define IMG_FIRST_NUMBER_POS_X			420		/*position x du premier nombre de ligne/colonne */
#define IMG_FIRST_NUMBER_POS_Y			420		/*position y du premier nombre de ligne/colonne */
#define IMG_FIRST_ICONE_POS_X			500		/*position x du premier icone */
#define IMG_FIRST_ICONE_POS_Y			100		/*position y du premier icone */
#define IMG_ECART_BETWEEN_ICONE			120		/*Ecart entre chaque icone */
#define IMG_ECART_BETWEEN_NUMBER		75 		/*Ecart entre chaque icone */

typedef enum { clavier, souris } selecttype; /* Permet de différencier les modes "clavier" et "souris" */

int start_game(bool campagnemode, short level, short ligne, short colonne);

void select_game() { /* Interface 2 */
	char filename[50]; /*Sera utilisé pour stocker les noms de fichier dans les boucles*/
	short i, count, clic; /*i: Counter | count: Counter pour les icones/nombres | clic: Stock le résultat de SourisCliquee à chaque début de boucle*/
	unsigned int res; /*Utilisé pour vérifier qu'une fonction s'est executée correctement */
	int img_posx, img_posy; /*Stock les différentes coordonnées des images au sein des boucles */
	selecttype mode; /* Sert à différencier le mode utilisé actuellement par l'utilisateur ("clavier" ou "souris") */
	bool button_is_press; /*Petite variable, presque tout le temps sur "false", qui passe sur "true" pendant quelques...*/
						  /*...millisecondes, lorsqu'un bouton est utilisé. Cela permet une legère animation du bouton*/
	bool campagnemode; /* Variable sur "true" ou "false" qui permet de savoir si l'utilisateur préfère jouer en mode libre*/
					   /*(choix d'images et du nombre de lignes/colonnes), ou en mode campagne (3 niveaux).*/
	/*Si le mode campagne est sur "false"... */
		/*...le joueur peut choisir entre 3 levels (level=image). levelselected sera sur "0" si aucune image*/
		/*n'est selectionnée, sinon: correspondra au numéro de l'image selectionnée.*/
		short levelselected;
		/*...le joueur devra choisir le nombre de colonnes qu'il souhaite pour l'image.*/
		short colonneselected; 
		/*...le joueur devra choisir le nombre de lignes qu'il souhaite pour l'image.*/
		short ligneselected;
		/*..."allselected" sera sur "true", une fois les 3 variables précedement initiliasées définies.*/
		bool allselected;

	mode 					= souris;
	campagnemode 			= false;
	levelselected	 		= 0;
	colonneselected 		= 0;
	ligneselected 			= 0;
	allselected 			= false;
	button_is_press			= false;

	sprintf(filename, "img/background/animation/menu_to_option_25.jpg");
	ChargerImageFond(filename);

	printlog("success", "Interface de selection ouvert.");
	while (1) {
		wait(5); /*Evite quelques bugs graphiques */
		ChargerImage("img/text_line_number.png", IMG_FIRST_TEXT_POS_X, IMG_FIRST_TEXT_POS_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
		ChargerImage("img/text_colonne_number.png", IMG_FIRST_TEXT_POS_X, IMG_FIRST_TEXT_POS_Y+DIM_NUMBER*2+20, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
		/* Si l'utilisateur utilise actuellement la souris */
		if (mode==souris) {
			clic=SourisCliquee(); /*mettre le résultat de SourisCliquee() dans une variable, car si on appel directement SourisCliquee plus d'une fois dans une boucle on rencontre des problèmes*/
			SourisPosition();
			count = 0;
			/* 3 icones à afficher, de manière régulière, donc boucler l'action d'affichage 3 fois */
			for(i=0; i<3; i++) {
				count++; /*On aurait pu utiliser directement "i", mais je passerais peut-être par un while par la suite */
				img_posx = (IMG_FIRST_ICONE_POS_X+((IMG_ECART_BETWEEN_ICONE*(count-1))))+DIM_ICONE*(count-1); /*Position x de l'icone selon la boucle*/
				img_posy = IMG_FIRST_ICONE_POS_Y; /*Position y de l'icone selon la boucle*/
				/* Si la personne clic... */
				if (clic == 1) {
					if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_ICONE ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_ICONE )) ) {
						/*...et que l'icone en question était déjà selectionné, ... */
						if ( levelselected == count) {
							/*...déselectionner l'icone. */
							levelselected=0;
							printlog("success", "Image dé-selectionnée.");
						}
						/*Sinon... */
						else {
							/*...définir l'icone comme "selectionné". */
							levelselected=count;
							printlog("success", "Image selectionnée.");
						}
					}
				}
				/* Si l'image est selectionnée... */
				if ( levelselected == count) {
					/* ...afficher le cadre de selection autour */
					ChargerImage("img/icone_select.png", img_posx, img_posy, 0, 0, DIM_ICONE, DIM_ICONE);
				}
				/* Si on passe la souris sur l'image... */
				if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_ICONE ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_ICONE )) ) {
					sprintf(filename, "img/icone_hover_level%d.png", count);
					/*...afficher l'image sur-exposée */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_ICONE, DIM_ICONE);
				}
				/* Si on ne passe pas la souris sur l'image... */
				else {
					sprintf(filename, "img/icone_level%d.png", count);
					/*...afficher l'image */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_ICONE, DIM_ICONE);
				}
				/* Si l'image est selectionnée... */
				if ( levelselected == count) {
					/* ...afficher le cadre de selection autour */
					ChargerImage("img/icone_select.png", img_posx, img_posy, 0, 0, DIM_ICONE, DIM_ICONE);
				}
			}
			count = 2;
			/* 6 nombres de lignes à afficher, de manière régulière, donc boucler l'action d'affichage 6 fois */
			for(i=0; i<6; i++) {
				count++;
				img_posx = (IMG_FIRST_NUMBER_POS_X+((IMG_ECART_BETWEEN_NUMBER*(count-3))))+DIM_NUMBER*(count-3); /*Position x du nombre selon la boucle*/
				img_posy = IMG_FIRST_NUMBER_POS_Y; /*Position y du nombre selon la boucle*/
				/* Si la personne clic... */
				if (clic == 1) {
					if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_NUMBER ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_NUMBER )) ) {
						/*...et que le nombre en question était déjà selectionné, ... */
						if ( ligneselected == count) {
							/*...déselectionner ce nombre. */
							ligneselected=0;
							printlog("success", "Ligne dé-selectionnée.");
						}
						/*Sinon... */
						else {
							/*...définir ce nombre comme "selectionné". */
							ligneselected=count;
							printlog("success", "Ligne selectionnée.");
						}
					}
				}
				/* Si on passe la souris sur le nombre... */
				if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_NUMBER ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_NUMBER )) ) {
					sprintf(filename, "img/LC_hover_number_%d.png", count);
					/*...afficher le nombre sur-exposée */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
				/* Si on ne passe pas la souris sur le nombre... */
				else {
					sprintf(filename, "img/LC_number_%d.png", count);
					/*...afficher le nombre */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
				/* Si le nombre est selectionnée... */
				if ( ligneselected == count) {
					/* ...afficher le cadre de selection autour */
					ChargerImage("img/LC_select.png", img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
			}
			count = 2;
			/* 6 nombres de colonnes à afficher, de manière régulière, donc boucler l'action d'affichage 6 fois */
			for(i=0; i<6; i++) {
				count++;
				img_posx = (IMG_FIRST_NUMBER_POS_X+((IMG_ECART_BETWEEN_NUMBER*(count-3))))+DIM_NUMBER*(count-3); /*Position x du nombre selon la boucle*/
				img_posy = IMG_FIRST_NUMBER_POS_Y+IMG_ECART_BETWEEN_NUMBER*3; /*Position y du nombre selon la boucle*/
				/* Si la personne clic... */
				if (clic == 1) {
					if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_NUMBER ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_NUMBER )) ) {
						/*...et que le nombre en question était déjà selectionné, ... */
						if ( colonneselected == count) {
							/*...déselectionner ce nombre. */
							colonneselected=0;
							printlog("success", "Colonne dé-selectionnée.");
						}
						/*Sinon... */
						else {
							/*...définir ce nombre comme "selectionné". */
							colonneselected=count;
							printlog("success", "Colonne selectionnée.");
						}
					}
				}
				/* Si on passe la souris sur le nombre... */
				if ( ((_X >= img_posx ) && (_X <= ( img_posx + DIM_NUMBER ) )) && ((_Y >= img_posy ) && (_Y <= img_posy + DIM_NUMBER )) ) {
					sprintf(filename, "img/LC_hover_number_%d.png", count);
					/*...afficher le nombre sur-exposée */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
				/* Si on ne passe pas la souris sur le nombre... */
				else {
					sprintf(filename, "img/LC_number_%d.png", count);
					/*...afficher le nombre */
					ChargerImage(filename, img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
				/* Si le nombre est selectionnée... */
				if ( colonneselected == count) {
					/* ...afficher le cadre de selection autour */
					ChargerImage("img/LC_select.png", img_posx, img_posy, 0, 0, DIM_NUMBER, DIM_NUMBER);
				}
			}
			if ( (ligneselected!=0) && (colonneselected!=0) && (levelselected!=0) ) {
				if (allselected==false) {
					allselected=true;
					printlog("success", "Variables de lancement selectionnées, il est maintenant possible de lancer une partie");
				}
			}
			else {
				if (allselected==true) {
					allselected=false;
					printlog("success", "Variables de lancement dé-selectionnées, il n'est plus possible de lancer une partie");
				}
			}
			if (clic == 1) {
				/* "RETOUR" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_RETURN_POS_MIN_Y ) && (_Y <= B_RETURN_POS_MAX_Y )) ) {
					if (button_is_press == false) {
						printlog("success", "Bouton \"Retour\" utilisé.");
						ChargerImage("img/button-return_push.png", ( BASE_POS_X + 5 ), B_RETURN_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
						run_animation(2);
						res=run_interface(1);
						if (res!=0) {
							printlog("err", "Impossible de lancer l'interface de jeu.");
						}
						button_is_press = true;
						wait(100);
						button_is_press = false;
					}
				}
				/* "SUIVANT" */
				if (allselected == true) {
					if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_SUIVANT_POS_MIN_Y ) && (_Y <= B_SUIVANT_POS_MAX_Y )) ) {
						printlog("success", "Bouton \"Suivant\" utilisé.");
						ChargerImage("img/button-next_push.png"    , ( BASE_POS_X + 5 ),  B_SUIVANT_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
						res=start_game(campagnemode, levelselected, ligneselected, colonneselected);
						if (res!=0) {
							printlog("err", "Impossible de lancer une partie");
						}
					}
				}
				else {
					ChargerImage("img/button-next_lock.png", ( BASE_POS_X + 5 ), B_SUIVANT_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
			}
			else {
				/* "RETOUR" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_RETURN_POS_MIN_Y ) && (_Y <= B_RETURN_POS_MAX_Y )) ) {
					ChargerImage("img/button-return_hover.png", ( BASE_POS_X + 5 ), B_RETURN_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
				else {
					ChargerImage("img/button-return_normal.png" , ( BASE_POS_X + 5 ),  B_RETURN_POS_MIN_Y , 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR); 
				}
				/* "SUIVANT" */
				if (allselected == true) {
					if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_SUIVANT_POS_MIN_Y ) && (_Y <= B_SUIVANT_POS_MAX_Y )) ) {
						ChargerImage("img/button-next_hover.png"    , ( BASE_POS_X + 5 ),  B_SUIVANT_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
					}
					else {
						ChargerImage("img/button-next_normal.png", ( BASE_POS_X + 5 ), B_SUIVANT_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
					}
				}
				else {
					ChargerImage("img/button-next_lock.png", ( BASE_POS_X + 5 ), B_SUIVANT_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
			}

		}
	}
}

int start_game(bool campagnemode, short level, short ligne, short colonne) { /* Interface 2.2 */
	char number[50]; /*Sera utilisé pour stocker le nom de l'image contenant les chiffres*/
	char filename[50]; /*Sera utilisé pour stocker le nom de l'image*/
	short count, jump, ncount, njump; /*i: Counter | count: Counter pour les icones/nombres | clic: Stock le résultat de SourisCliquee à chaque début de boucle*/
	unsigned int res; /*Utilisé pour vérifier qu'une fonction s'est executée correctement */
	int tab[64][3];
	int hideblock;
	int clic;
	int stock;
	int temp;
	int melange;
	int taille;
	int hideblockposx;
	int hideblockposy;
	int posx;
	int posy;
	int r, z;
	int dimension, firstposx, firstposy, i, n;
	int ldim, hdim;
	selecttype mode; /* Sert à différencier le mode utilisé actuellement par l'utilisateur ("clavier" ou "souris") */
	bool button_is_press; /*Petite variable, presque tout le temps sur "false", qui passe sur "true" pendant quelques...*/
						  /*...millisecondes, lorsqu'un bouton est utilisé. Cela permet une legère animation du bouton*/
	mode 					= souris;
	button_is_press			= false;
	srand(time(NULL));

	if (campagnemode==false) {
		printlog("load", "Lancement de la partie en mode libre...");
		if (level==1) {
			dimension=760;
			firstposx=1500-dimension-dimension/3;
		}
		else if (level==2) {
			dimension=800;
			firstposx=500;
		}
		else if (level==3) {
			dimension=840;
			firstposx=450;
		}
		else {
			printlog("err", "Numéro d'image/level invalide. Veuillez choisir des valeurs entre 1 et 3");
			exit(1);
		}
		firstposy=(844-dimension)/2;
	}
	else {
		printlog("load", "Lancement de la partie en mode campagne...");
	}

	ChargerImageFond("img/background/animation/menu_to_option_25.jpg");
	printlog("success", "Interface de la partie ouvert");
	ldim=dimension/ligne;
	hdim=dimension/colonne;
	sprintf(filename, "img/image_level_%d.png", level);

	taille=ligne*colonne;
	count=0;
	jump=0;
	for(i=0; i<taille; i++) {
		tab[i][0]=i;
		tab[i][1]=i;
		tab[i][2]=i;
		if (count>=ligne) {
			count=0;
			jump++;
		}
		if (i!=0) {
			sprintf(number, "img/case_number/%d.png", tab[i][1]);
			ChargerImage(filename, firstposx+(ldim*count), firstposy+(hdim*jump), (count*ldim), (hdim*jump), ldim-2, hdim-2);
			ChargerImage(number, (((firstposx+(ldim*count))*2+ldim-2)/2)-94/2, (((firstposy+(hdim*jump))*2+hdim-2)/2)-94/2, 0, 0, 94, 94);
		}
		count++;
	}
	hideblock=tab[0][0];
		/*MELANGE */
				for(melange=0; melange<1000*level*level; melange++) {
					count=0;
					jump=0;
					r = rand() % 4;
		 			for(i=0; i<taille; i++) {
						if (count>=ligne) {
							count=0;
							r++;
							if (r==4) {
								r = rand() % 4;
							}
							jump++;
						}
						if (tab[i][2]!=hideblock) {
							r = rand() % 4;
							if (( (r==0) && (tab[i][2])-1==hideblock) ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (jump==njump) {
										if (tab[n][2]==hideblock) {
											hideblockposx=firstposx+(ldim*ncount);
											hideblockposy=firstposy+(hdim*njump);
											posx=firstposx+(ldim*count);
											posy=firstposy+(hdim*jump);
											/*Copie le hideblock dans fenetre 1*/
											CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
											/*Copie le block cliqué à la position du hideblock*/
											CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
											/*Copie le hideblock dans fenetre 0*/
											CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
											temp=tab[n][0];
											tab[n][0]=tab[i][0];
											hideblock=tab[i][2];
											tab[i][0]=temp;
											n=taille;
											r = rand() % 4;
										}
									}
									ncount++;
								}
							}
							if ( (r==3) && (tab[i][2]-ligne==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (tab[n][2]==hideblock) {
										hideblockposx=firstposx+(ldim*ncount);
										hideblockposy=firstposy+(hdim*njump);
										posx=firstposx+(ldim*count);
										posy=firstposy+(hdim*jump);
										/*Copie le hideblock dans fenetre 1*/
										CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
										/*Copie le block cliqué à la position du hideblock*/
										CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
										/*Copie le hideblock dans fenetre 0*/
										CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
										temp=tab[n][0];
										tab[n][0]=tab[i][0];
										hideblock=tab[i][2];
										tab[i][0]=temp;
										n=taille;
									}
									ncount++;
								}
							}
							if ( (r==1) && ((tab[i][2])+1==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (jump==njump) {
										if (tab[n][2]==hideblock) {
											hideblockposx=firstposx+(ldim*ncount);
											hideblockposy=firstposy+(hdim*njump);
											posx=firstposx+(ldim*count);
											posy=firstposy+(hdim*jump);
											/*Copie le hideblock dans fenetre 1*/
											CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
											/*Copie le block cliqué à la position du hideblock*/
											CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
											/*Copie le hideblock dans fenetre 0*/
											CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
											temp=tab[n][0];
											tab[n][0]=tab[i][0];
											hideblock=tab[i][2];
											tab[i][0]=temp;
											n=taille;
											r++;
											if (r==4) {
												r = rand() % 4;
											}
											r++;
											if (r==4) {
												r = 1;
											}
										}
									}
									ncount++;
								}
							}
							if ( (r==2) && (tab[i][2]+ligne==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (tab[n][2]==hideblock) {
										hideblockposx=firstposx+(ldim*ncount);
										hideblockposy=firstposy+(hdim*njump);
										posx=firstposx+(ldim*count);
										posy=firstposy+(hdim*jump);
										/*Copie le hideblock dans fenetre 1*/
										CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
										/*Copie le block cliqué à la position du hideblock*/
										CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
										/*Copie le hideblock dans fenetre 0*/
										CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
										temp=tab[n][0];
										tab[n][0]=tab[i][0];
										hideblock=tab[i][2];
										tab[i][0]=temp;
										n=taille;
										r++;
										if (r==4) {
											r = rand() % 4;
										}
										r++;
										if (r==4) {
											r = 2;
										}
									}
									ncount++;
								}
							}
						}
					count++;
					}
				}
	while (1) {
		/* Si l'utilisateur utilise actuellement la souris */
		if (ToucheEnAttente()==1) {
			mode=clavier;
		}
		if (ToucheEnAttente()==1) {
			stock=Touche();
			if ( (stock==0xff51 ) || (stock==0xff52 ) || (stock==0xff53 ) || (stock==0xff54 ) ) {
					count=0;
					jump=0;
		 			for(i=0; i<taille; i++) {
						if (count>=ligne) {
							count=0;
							jump++;
						}
						if (tab[i][2]!=hideblock) {
							if (( (stock==0xff51) && (tab[i][2])-1==hideblock) ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (jump==njump) {
										if (tab[n][2]==hideblock) {
											hideblockposx=firstposx+(ldim*ncount);
											hideblockposy=firstposy+(hdim*njump);
											posx=firstposx+(ldim*count);
											posy=firstposy+(hdim*jump);
											/*Copie le hideblock dans fenetre 1*/
											CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
											/*Copie le block cliqué à la position du hideblock*/
											CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
											/*Copie le hideblock dans fenetre 0*/
											CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
											temp=tab[n][0];
											tab[n][0]=tab[i][0];
											hideblock=tab[i][2];
											tab[i][0]=temp;
											n=taille;
											i=taille;
										}
									}
									ncount++;
								}
							}
							if ( (stock==0xff52) && (tab[i][2]-ligne==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (tab[n][2]==hideblock) {
										hideblockposx=firstposx+(ldim*ncount);
										hideblockposy=firstposy+(hdim*njump);
										posx=firstposx+(ldim*count);
										posy=firstposy+(hdim*jump);
										/*Copie le hideblock dans fenetre 1*/
										CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
										/*Copie le block cliqué à la position du hideblock*/
										CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
										/*Copie le hideblock dans fenetre 0*/
										CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
										temp=tab[n][0];
										tab[n][0]=tab[i][0];
										hideblock=tab[i][2];
										tab[i][0]=temp;
										n=taille;
										i=taille;
									}
									ncount++;
								}
							}
							if ( (stock==0xff53) && ((tab[i][2])+1==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (jump==njump) {
										if (tab[n][2]==hideblock) {
											hideblockposx=firstposx+(ldim*ncount);
											hideblockposy=firstposy+(hdim*njump);
											posx=firstposx+(ldim*count);
											posy=firstposy+(hdim*jump);
											/*Copie le hideblock dans fenetre 1*/
											CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
											/*Copie le block cliqué à la position du hideblock*/
											CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
											/*Copie le hideblock dans fenetre 0*/
											CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
											temp=tab[n][0];
											tab[n][0]=tab[i][0];
											hideblock=tab[i][2];
											tab[i][0]=temp;
											n=taille;
											i=taille;
										}
									}
									ncount++;
								}
							}
							if ( (stock==0xff54) && (tab[i][2]+ligne==hideblock)  ) {
								ncount=0;
								njump=0;
								for(n=0; n<taille; n++) {
									if (ncount>=ligne) {
										ncount=0;
										njump++;
									}
									if (tab[n][2]==hideblock) {
										hideblockposx=firstposx+(ldim*ncount);
										hideblockposy=firstposy+(hdim*njump);
										posx=firstposx+(ldim*count);
										posy=firstposy+(hdim*jump);
										/*Copie le hideblock dans fenetre 1*/
										CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
										/*Copie le block cliqué à la position du hideblock*/
										CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
										/*Copie le hideblock dans fenetre 0*/
										CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
										temp=tab[n][0];
										tab[n][0]=tab[i][0];
										hideblock=tab[i][2];
										tab[i][0]=temp;
										n=taille;
										i=taille;
									}
									ncount++;
								}
							}
						}
						count++;
					}
					z=0;
					for(i=0; i<taille; i++) {
						if (tab[i][0]!=tab[i][2]) {
							z=1;
						}
					}
					if (z==0) {
						sprintf(filename, "img/background/animation/menu_to_option_25.jpg");
						ChargerImageFond(filename);
						break;
					}
				}
			}
		else {
			clic=SourisCliquee();
			SourisPosition();
			if (clic !=0 ) {
				if ( ( (_X >= firstposx ) && (_X <= firstposx+dimension ) ) && ((_Y >= firstposy ) && (_Y <= firstposy+dimension ) ) ) {
					count=0;
					jump=0;
		 			for(i=0; i<taille; i++) {
						if (count>=ligne) {
							count=0;
							jump++;
						}
						if ( ( (_X >= firstposx+(ldim*count) ) && (_X <= firstposx+(ldim*count)+ldim )) && ((_Y >= firstposy+(hdim*jump) ) && (_Y <= firstposy+(hdim*jump)+hdim )) ) {
							if (tab[i][2]!=hideblock) {
								if (	(((tab[i][2])-1==hideblock) || ((tab[i][2])+1==hideblock) ||	(tab[i][2]+ligne==hideblock) || (tab[i][2]-ligne==hideblock))	) {
									ncount=0;
									njump=0;
						 			for(n=0; n<taille; n++) {
										if (ncount>=ligne) {
											ncount=0;
											njump++;
										}
										if (jump==njump) {
											if (tab[n][2]==hideblock) {
												hideblockposx=firstposx+(ldim*ncount);
												hideblockposy=firstposy+(hdim*njump);
												posx=firstposx+(ldim*count);
												posy=firstposy+(hdim*jump);
												/*Copie le hideblock dans fenetre 1*/
												CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
												/*Copie le block cliqué à la position du hideblock*/
												CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
												/*Copie le hideblock dans fenetre 0*/
												CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
												temp=tab[n][0];
												tab[n][0]=tab[i][0];
												hideblock=tab[i][2];
												tab[i][0]=temp;
												n=taille;
											}
										}
										else if ( (tab[i][2]+ligne==hideblock) || (tab[i][2]-ligne==hideblock) ) {
											if (tab[n][2]==hideblock) {
												hideblockposx=firstposx+(ldim*ncount);
												hideblockposy=firstposy+(hdim*njump);
												posx=firstposx+(ldim*count);
												posy=firstposy+(hdim*jump);
												/*Copie le hideblock dans fenetre 1*/
												CopierZone( 0, 0, hideblockposx, hideblockposy, ldim-2, hdim-2, 2000, 2000);
												/*Copie le block cliqué à la position du hideblock*/
												CopierZone( 0, 0, posx, posy, ldim-2, hdim-2, hideblockposx, hideblockposy);
												/*Copie le hideblock dans fenetre 0*/
												CopierZone( 0, 0, 2000, 2000, ldim-2, hdim-2, posx, posy);
												temp=tab[n][0];
												tab[n][0]=tab[i][0];
												hideblock=tab[i][2];
												tab[i][0]=temp;
												n=taille;
											}
										}
										ncount++;
									}
								}
							}
						}
						count++;
					}
					z=0;
					for(i=0; i<taille; i++) {
						if (tab[i][0]!=tab[i][2]) {
							z=1;
						}
					}
					if (z==0) {
						sprintf(filename, "img/background/animation/menu_to_option_25.jpg");
						ChargerImageFond(filename);
						break;
					}
				}
				/* "RETOUR" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_RETURN_POS_MIN_Y ) && (_Y <= B_RETURN_POS_MAX_Y )) ) {
					if (button_is_press == false) {
						printlog("success", "Bouton \"Retour\" utilisé.");
						ChargerImage("img/button-return_push.png", ( BASE_POS_X + 5 ), B_RETURN_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
						res=run_interface(2);
						if (res!=0) {
							printlog("err", "Impossible de lancer l'interface de jeu.");
						}
					}
				}
			}
			else {
				/* "RETOUR" */
				if ( ((_X >= ( BASE_POS_X + 5 ) ) && (_X <= ( ( BASE_POS_X + 5 ) + BOUTONS_POS_MAX_X ) )) && ((_Y >= B_RETURN_POS_MIN_Y ) && (_Y <= B_RETURN_POS_MAX_Y )) ) {
					ChargerImage("img/button-return_hover.png", ( BASE_POS_X + 5 ), B_RETURN_POS_MIN_Y, 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR);
				}
				else {
					ChargerImage("img/button-return_normal.png" , ( BASE_POS_X + 5 ),  B_RETURN_POS_MIN_Y , 0, 0, DIM_BOUTONS_LONGUEUR, DIM_BOUTONS_HAUTEUR); 
				}
			}
		}
	}
	return EXIT_SUCCESS;
}