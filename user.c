#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO "myfifo1.fifo"
#define FIFO2 "myfifo2.fifo"

int main(int argc, char *argv[])
{
	/* code */
	int tube,tube2;
	char bufRecep[64];
	char rep[3];
	int id, nb;

	printf("User\n");
	tube2 = open(FIFO, O_WRONLY);
	if(tube2 < 0)
	{
		perror("open");
		exit(-1);
	}
	printf("open\n");

	if (tube2 == -1)
	{
		printf("erreur tube \n");
		exit(EXIT_FAILURE);
	}

	nb = write(tube2, argv[1], strlen(argv[1])+1);
	printf("user write %d octets\n", nb);
	id = atoi(argv[2]);
	nb = write(tube2, &id, 4);
	printf("user write %d octets\n", nb);
	printf("user a ecrite\n");

	tube = open(FIFO2, O_RDONLY);
	if(tube < 0)
	{
		perror("open");
		exit(-1);
	}
	printf("open\n");

	read(tube, rep, 3);
	printf("reponse: %s\n", rep);

	//printf("%s\n", bufRecep);

/*
	if(strcmp(bufRecep, rep) == 0)
	{
		printf("ok\n");
		write(tube2, "ok", 2);
	}
	else
	{
		printf("pas ok \n");
		write(tube2, "pas ok", 6);
	}
*/

	return 0;
}
