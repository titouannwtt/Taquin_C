#ifndef RUN_GAME_H
#define RUN_GAME_H

typedef enum { false, true } bool; /* Permet d'utiliser les termes "false" et "true" pour des variables, plutôt que "0" ou "1" */
int start_game(bool campagnemode, short level, short ligne, short colonne);
void select_game();

#endif /* RUN_GAME_H */
