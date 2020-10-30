#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>



#define FIFO "myfifo1.fifo"
#define FIFO2 "myfifo2.fifo" // CONTRO vers user


//CONTROLLEUR

int main(int argc, char const *argv[])
{

	char nom[12] ;
	char bufrep[80] ;
	//char mdp[12] ;
	char reponse[] = "Ok";

	int fd, fd2, tube, tube2, nbytes = 30, i, fin, id;

	// if (argc !=3)
	// {
	// 	printf("Le nombre d'arguments n'est pas bon\n");
	// }
	// else
	// {
	// 	strcpy(nom, argv[1]);
	// 	printf("nom=%s \n ",nom );
	// }

	tube = mkfifo(FIFO, 0600);
	tube2 = mkfifo(FIFO2, 0600);

	fd= open(FIFO, O_RDONLY);


	if(tube==-1 || tube2 ==-1 )
	{
		perror("Erreur de création du tube nommé \n");
		exit(EXIT_FAILURE);
	}
	else if (fd == -1 || fd2 == -1)
	{
		perror("Erreur ouverture fd\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		//printf("Le message: envoyé : %s \n", id);
		i = 0;
		fin = 0;
		do {
			read(fd, &nom[i], 1);
			printf("%c", nom[i]);
			if(nom[i] == '\0')
				fin = 1;
			else ++i;
		}while(fin == 0);

		printf ("\nnom recu: %s\n", nom);
		read(fd, &id, 4);
		printf("id = %d", id);


		write(fd2, reponse, strlen(reponse)+1);
		//printf("Réponse %s :\n", bufrep);

		close(fd);
		unlink("myfifo1.fifo");

		close(fd2);
		unlink("myfifo2.fifo");

	}





	return 0;
}
