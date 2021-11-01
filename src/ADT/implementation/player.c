#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void createPlayer(PLAYER *p,LOKASI lokAwal){
    pLoc(*p) = lokAwal;
};

void movePlayer(MAP m, PLAYER *p,int opt){
    pLoc(*p) = ELMTLD(REACH(m),opt-1);
};

void updateStatus(MAP *m,PLAYER p){
    int i;
    int idx;
    char c;
    for(i=0;i<nEffBuilding(*m);i++){
        if(ELMTADJ(*m,idx,i) == '1'){
            ELMTTP(*m,i) = 'b';
        } 
    }
    clearReachable(m);
    c = getBuilding(*m,Absis(pLoc(p)),Ordinat(pLoc(p)));
    idx = getIdxBld(c);
    for(i=0;i<nEffBuilding(*m);i++){
        if(ELMTADJ(*m,idx,i) == '1'){
            ELMTTP(*m,i) = 'r';
            insertLast(&REACH(*m),LOK(*m,i));
        } 
    }
    ELMTTP(*m,idx) = 'm';
}

