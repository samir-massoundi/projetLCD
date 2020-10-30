#ifndef ECRAN_H
#define ECRAN_H

int init_port();

void videEcran(int fd);

void goPos(int fd, char col, char row);

void ecrireLCD(int fd, char txt[]);
void clearLine(int fd, int row);

#endif