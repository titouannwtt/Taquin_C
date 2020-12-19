/* TITOUAN WATTELET */
/*------------------*/


/* LIBRAIRIES */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum { false, true } bool;

/*Fonction log*/
/*A utilisé sous forme:
	printlog(<err/log> "<message>")
*/
void printlog(char logtype[], char message[]) {
	bool print_in_console;
	bool print_in_logfile;
	FILE *logfile;
	FILE *errfile;

	print_in_console = true;
	print_in_logfile = true;
	if (print_in_logfile==true) {
		if (strcmp(logtype,"err")==0) {
			errfile = fopen("logs/errors.log", "a+");
			if (errfile == NULL) {	
				printf("\033[0m[\033[31mERROR\033[0m]\033[31m\033[1m Impossible d'ouvrir \"errors.log\" \033[0m\n");
			}
			fprintf(errfile, "[ERROR] %s\n", message);
			fclose(errfile);
		}
		if ( (strcmp(logtype,"load")==0) || (strcmp(logtype,"success")==0) || (strcmp(logtype,"err")==0)) {
			logfile = fopen("logs/logs.log", "a+");
			if (logfile == NULL) {	
				printf("\033[0m[\033[31mERROR\033[0m]\033[31m\033[1m Impossible d'ouvrir \"latest.log\" \033[0m\n");
			}
			fprintf(logfile, "[LOG] %s\n", message);
			fclose(logfile);
		}
	}

	if (print_in_console==true) {
		if (strcmp(logtype,"err")==0) {
			printf("\033[0m[\033[31mERROR\033[0m]\033[31m\033[1m %s \033[0m\n", message);
		}
		else if (strcmp(logtype,"load")==0) {
			printf("\033[0m[\033[37mLOG\033[0m]\033[1m %s \033[0m\n", message);
		}
		else if (strcmp(logtype,"success")==0) {
			printf("\033[0m[\033[37mLOG\033[0m]\033[32m\033[1m %s \033[0m\n", message);
		}
		else {
			printf("\033[0m[\033[31mERROR\033[0m]\033[31m Usage of Fonction: \"log(<err/log> \"<message>\".\033[0m\n");
			exit(2);
		}
	}
}
