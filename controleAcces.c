#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	
	char id[12] ;
	char mdp[12] ;

	int fd, nbytes = 30;


	if (argc !=3)
	{
		printf("Le nombre d'arguments n'est pas bon, il doit y en avoir deux\n");
	}
	else
	{
		strcpy(id, argv[1]);
		strcpy(mdp, argv[2]);

		printf("id=%s mdp =%s\n",id, mdp );
	}
	
	int tube = mkfifo("myfifo.fifo", 0644);
	fd= open(myfifo.fifo, O_RDWR);

	if(tube==-1)
	{
		printf("Erreur de création du tube nommé");
	}
	else if (fp == -1)
	{
		printf("Erreur ouverture fd\n");
	}
	else 
	{
		write(fd, id[12], strlen(id));
	}

	getchar();
	/*close(fd);
	unlink("myfifo.fifo")*/

	return 0;
}