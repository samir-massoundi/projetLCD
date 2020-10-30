#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

/******************************************************************************
** init_port(): ouvre le port série et l'initialise.
** Entrée:
** Sortie: fd, le file descriptor sur le port serie.
******************************************************************************/
int init_port()
{
	//ouverture du port
	int fd;

	if( (fd = open("/dev/ttyS0", O_WRONLY | O_NOCTTY | O_NDELAY)) > 0) 
		// On verifie si on arrive bien a ouvrir le file descriptor 
	{
		fcntl(fd, F_SETFL, 0);
		printf("File descriptor ouvert \n");

		struct termios options; 

		tcgetattr(fd, &options); 
		cfsetispeed(&options, B9600);
		cfsetospeed(&options, B9600);

		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		tcsetattr(fd, TCSANOW, &options);
	}
	// nb= write(fd, c,strlen(c));
	// 	printf("%d\n",nb);
	// 	close(fd);
	return fd;	
}
/******************************************************************************
** goPos(): Regle le curseur a la position en paramètre
** Entrée: col, la colonne désirée |
		   row, la lignée désirée |
		   fd, le file descriptor |
** Sortie: 
******************************************************************************/
void goPos(int fd, char col, char row)
{	
	//char tab[4]={254,71,col,row};
	char tab[4]={254,71};
	tab[2]=col;
	tab[3]=row;
	write(fd, tab, sizeof(tab));
}

/******************************************************************************
** videEcran(): Vide l'ecran LCD et remet le curseur a la première position
**				en haut a gauche.
** Entrée: fd, le file descriptor | 
** Sortie: 
******************************************************************************/
void videEcran(int fd) 
{
	char tab[2]={0xFE,0x58};
	write(fd, tab, sizeof(tab));
}

/******************************************************************************
** fonction ecrireLCD(): ecrit sur l'ecran LCD la chaine de caractère passée
**						 en paramètre
** Entrée:  fd, le file descriptor | txt, le texte a afficher
** Sortie: /
******************************************************************************/

void ecrireLCD(int fd, char txt[])
{	
	write(fd,txt,sizeof(txt));
}

/******************************************************************************
** fonction clear_line(): efface une ligne de l'ecran lcd et 
						  et replace le curseur eu debut de la ligne
** Entrée:  fd, le file descriptor
			row le numero de la ligne
** Sortie: /
******************************************************************************/

void clearLine(int fd, int row)
{
	goPos(fd, 1,row);

	char spa =' ';
	int i = 1;

	for (i=1 ; i <= 19; i++)
	{
		//goPos(fd, i,row);
		write(fd, &spa, 1);
	}

	goPos(fd, 1,row);
}

/******************************************************************************
** fonction : TEMPLATE DE DOCUMENTATION DE FONCTION
** Entrée:  
** Sortie: 
******************************************************************************/