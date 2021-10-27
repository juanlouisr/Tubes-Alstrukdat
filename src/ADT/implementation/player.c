#include <stdio.h>
#include "../../adtlib.h"

void createPlayer(PLAYER *p,LOKASI lokAwal){
    pLoc(*p) = lokAwal;
};

void movePlayer(MAP m, PLAYER *p,int opt){
    pLoc(*p) = ELMTLD(REACH(m),opt);
};