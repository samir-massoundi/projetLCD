#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
** conversionBin(): convertit un nombre passé en paramère en sa valeur 
					en binaire l'insère dans un tableau egalement en paramètre
** Entrée:	nbConvert : le nombre que l'on va convertir
			fd : le file descriptor courant
			tabBin : le tableau qui recevra le nombre converti en binaire, 
					cchaine de caractères conforme 
** Sortie: 
******************************************************************************/

void conversionBin(int nbConvert, int fd, char tabBin[]){


	printf("conversion binaire\n");
	
	//printf("Nombre en hexa 0x: %x\n", nbConvert);
	printf("Nombre en binaire 0b");
	
	
	//Conversion binaire
	int mask = 128;
	int i = 0;
	//char bin1[1]={'1'};
	//char bin0[1]={'0'};
	while(mask>0){
		if((nbConvert & mask) == 0)
		{
			printf("0");
			tabBin[i++]='0';
			//write(fd,bin0,sizeof(bin0));
		}
		else
		{
			printf("1");
			tabBin[i++]='1';
			//write(fd,bin1,sizeof(bin1));
		}
		//printf(" %d\n",mask);
		mask = mask >> 1;
		tabBin[i]='\0';
		
	}
	printf(" Fin conversion bin\n");

}

/******************************************************************************
** conversionHex(): convertit un nombre passé en paramère en sa valeur 
					en hexadecimal et l'insère dans un tableau egalement en 
					paramètre
** Entrée:	nbConvert : le nombre que l'on va convertir
			fd : le file descriptor courant
			tabBin : le tableau qui recevra le nombre converti en hexadecimal, 
					cchaine de caractères conforme 
** Sortie: 
******************************************************************************/

void conversionHex(int nbConvert, int fd, char tabBin[]){
		//Conversion hexadecimale 

	printf("conversion hexadecimale\n");

	//char hex[]={'\0','\0','\0'};

	sprintf(tabBin, "%x", nbConvert );
	//write(fd,hex, strlen(hex));
	printf(" nb hex : 0x%s\n", tabBin ); 

	printf(" Fin conversion hex\n");

}