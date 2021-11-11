#ifndef PLAYER_H
#define PLAYER_H

#include "lokasi.h"
#include "liststat.h"
#include "todoList.h"
#include "map.h"

typedef struct {
    LOKASI loc;
    Tas tas;
    List todo;
    ListPos invGadget;
    int uang;
    int speedBoostDur;
} PLAYER;

#define pLoc(p) (p).loc
#define pTas(p) (p).tas
#define pUang(p) (p).uang
#define pTodo(p) (p).todo
#define pInvG(p) (p).invGadget
#define pSpdDur(p) (p).speedBoostDur



void createPlayer(PLAYER *p,LOKASI lokAwal, Tas tas, List todo, ListPos invGadget,  int uang, int speedBoostDur);
/*Membuat player baru dengan
    lokasi = lokAwal

*/

void movePlayer(MAP m, PLAYER *p,int opt);
//Memindahkan player ke lok

void pintuKemanaSaja(STATE *state);
//Memindahkan player ke lok tanpa menambah waktu

void pickUp(PLAYER *p);

void dropOff(PLAYER *p);

void useGadget(PLAYER *p,STATE *state, int idx);

void buyGadget(PLAYER *player, int idx);

void displayMoney(PLAYER player);

#endif