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

  char nom[80];
  char mdp[6];
  char bufrep[80];
  char reponse[] = "Ok";

  int fdU2C,tubeU2C, fdC2U,tubeC2U, nbytes = 30, i,fin, id, nb;


  tubeU2C = mkfifo(FIFO_U2C, 0600);
  tubeC2U = mkfifo(FIFO_C2U, 0600);

  printf("tubes %d \n", tubeU2C );

  fdU2C= open(FIFO_U2C, O_RDONLY);


  printf("tube + fifo\n" );

  if (tubeC2U == -1 || tubeU2C == -1) {
    perror("erreur création tube nommé");
    exit(EXIT_FAILURE);
  }
  else if (tubeC2U == -1 || tubeU2C == -1) {
    perror("erreur création tube nommé");
    exit(EXIT_FAILURE);
  }
  else
  {
    i = 0;
    fin = 0;
    printf("Tube crée, recup données\n");
    do
      {
        read(fdU2C, &nom[i], 1);
        printf("%c", nom[i] );
        if(nom[i]=='\0') fin = 1;
        else i++;

      }while(fin==0);

      printf("\n %s\n",nom );
      i=0; fin=0;

    do
      {
        read(fdU2C, &mdp[i], 1);
        printf("%c", mdp[i] );
        if(mdp[i]=='\0') fin = 1;
        else i++;
      }while(fin==0);

      printf("\n %s\n",mdp );

    fdC2U= open(FIFO_C2U, O_WRONLY);
  	nb = write(fdC2U, reponse, strlen(reponse)+1);
    printf("user a ecrit %d octets pour la réponse\n", nb );

    // Fermeture des file descriptor et des tubes nommés
    close(fdU2C);
    unlink(FIFO_U2C);

    close(fdC2U);
    unlink(FIFO_C2U);

  }




  return 0;
}
