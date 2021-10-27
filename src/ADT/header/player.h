#ifndef PLAYER_H
#define PLAYER_H
#include "boolean.h"
#include "../../adtlib.h"

typedef struct {
    LOKASI loc;
    int uang;
} PLAYER;
#define pLoc(p) (p).loc

void createPlayer(PLAYER *p,LOKASI lokAwal);

#endif