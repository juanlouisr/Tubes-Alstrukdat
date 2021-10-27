#ifndef PLAYER_H
#define PLAYER_H

#include "lokasi.h"
#include "map.h"
typedef struct {
    LOKASI loc;
    int uang;
} PLAYER;
#define pLoc(p) (p).loc


void createPlayer(PLAYER *p,LOKASI lokAwal);
/*Membuat player baru dengan
    lokasi = lokAwal

*/
void updateStatus(MAP *m,PLAYER p);
//Update status dari bangunan

void movePlayer(MAP m, PLAYER *p,int opt);
//Memindahkan player ke lok
#endif