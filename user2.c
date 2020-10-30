#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>


#define FIFO_U2C "usr2contro.fifo" // Tube user vers CONTROLLEUR
#define FIFO_C2U "contro2usr.fifo" // Tube contro vers user

int main(int argc, char const *argv[]) {

  int id, nb ;
  char rep[3] ;
  int tubeU2C, tubeC2U;

  //
  tubeU2C= open(FIFO_U2C, O_WRONLY);

  printf("Tube ouvert\n");


  if(tubeC2U==-1 || tubeU2C ==-1)
  {
    perror("echec de l'ouverture du fd");
    exit(EXIT_FAILURE);
  }
  else if (argc !=3)
  {
    printf("mauvais nombre d'arguments\n" );
    exit(EXIT_FAILURE);
  }

  nb = write(tubeU2C, argv[1], strlen(argv[1])+1 );
  printf("user a ecrit %d octets pour l'utilisateur\n", nb );

  nb = write(tubeU2C, argv[2], strlen(argv[2])+1 );
  printf("user a ecrit %d octets pour le mot de passe\n", nb );
  /////////////////////////////

  tubeC2U= open(FIFO_C2U, O_RDONLY);
  read(tubeC2U, rep, 3);
  printf("reponse : %s \n",rep );


  return 0;
}
