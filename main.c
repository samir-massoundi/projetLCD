#include <stdio.h>
#include <stdlib.h>
#include "conversion.h"
#include <time.h>
#include <string.h>
#include "ecran.h"
#include <fcntl.h>
#include <termios.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	
	char choix = 0;
	int val;
	char bufVal[80] = {0}; //buffer de la valeur décimale
	char decim[]="decimal :";
	char bina[]="binaire :b";
	char hexad[]="hexa :0x";

	int stuff;

	char valBina[9] ; // tableau qui contient la valeur convertie en Binaire
	char valHexa[3] = {'\0','\0','\0'}; // tableau qui contient la valeur convertie en Hexadécimal

	//TIME
	time_t currTime;
	struct tm * timeinfo;
	char bufferT [9];

	int i=0, pip[2], status; // 
	char chaine[10];
	pid_t pid;
	
	int fd = init_port();
	if(fd < 0) {
		printf("Impossible d'ouvrir le port serie.\n");
		exit(EXIT_FAILURE);
	}
	videEcran(fd);
	pipe(pip);

	pid=fork();

	//tube nommé verification : 



	switch(pid)
	{
		case -1 : 
			printf("erreur fork\n"); // cas Erreur
			break;// cas erreur

		case 0 : // cas fils 
			close(pip[1]);
			fcntl(pip[0],F_SETFL, O_NONBLOCK);

			while(1)
			{
				goPos(fd,1,1);
				time (&currTime);
				timeinfo = localtime (&currTime);
				strftime (bufferT,sizeof(bufferT),"%T",timeinfo);

				write(fd, bufferT, strlen(bufferT));
				sleep(1);

				//read(pip[0],chaine,strlen(chaine));
				read(pip[0],chaine, strlen("STOP_")+1);
				if (strcmp(chaine,"STOP_") == 0) break;			

			}	
			printf("Fin du fils\n");
			close(pip[0]);
			exit(0);

		default: // cas père 
		close(pip[0]);
		do
		{	
			printf("Convertisseur LCD Decimal -> Binaire Hexa \n");
			printf("c - convertir une donnée\nq - quitter le programme \n");

			scanf("%c", &choix);
			while(getchar()!='\n');
			switch(choix)
			{
				case 'c':
					printf("Conversion\nVeuillez saisir une donnée(inferieure a 255): ");	/* code */
					scanf("%d",&val);
					while(getchar()!='\n');

					if (val >=0 && val<=255)
					{	
						clearLine(fd, 2);
						clearLine(fd, 3);
						clearLine(fd, 4);
						printf("La valeur %d sera convertie \n\n",val );

						sprintf(bufVal,"%d",val);

						goPos(fd,1,2);
						write(fd, decim,strlen(decim));
						write(fd, bufVal, strlen(bufVal));

						goPos(fd,1,3);
						write(fd, bina,strlen(bina));
						conversionBin(val,fd,valBina);
						write(fd, valBina, strlen(valBina));


						goPos(fd,1,4);
						write(fd, hexad,strlen(hexad));
						conversionHex(val,fd,valHexa);
						write(fd, valHexa, strlen(valHexa));
					}
					else 
					{
						printf("Valeur en dehors du rang autorisé\n \n");
					}

					break;

				case 'q':
					write(pip[1],"STOP_",6);
					printf("Sortie du programme\n");
					close(pip[1]);
					wait(&status);
					break;

				default:
					printf("Mauvaise saisie, recommencez\n");
				break;
			}
		} while (choix!='q');
		break;
	}
	//fermer le port
	close(fd);
	exit(0);
}