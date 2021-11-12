#ifndef STATE_H
#define STATE_H

#include "lokasi.h"
#include "map.h"
#include "player.h"
#include "queue.h"

typedef struct {
    float waktu;
    PLAYER player;
    MAP map;
    Queue itemsQueue;
} STATE;

/* --------- SELEKTOR STATE --------- */
#define CURR_PLAYER(p) (p).player
#define CURR_MAP(p) (p).map
#define CURR_QUEUE(p) (p).itemsQueue
#define CURR_TIME(p) (p).waktu
#define CURR_TAS(p) pTas(CURR_PLAYER(p))
#define CURR_TODO(p) pTodo(CURR_PLAYER(p))


/* --------- KONSTRUKTOR STATE --------- */
void CreateSTATE(STATE* state, PLAYER p, MAP map, Queue queue, float startTime);


/* --------- PROSEDUR/FUNGSI STATE --------- */
void incrementWaktu(STATE *state);
void mesinWaktu(STATE *state);
void pintuKemanaSaja(STATE *state);
//Memindahkan player ke lok tanpa menambah waktu
void useGadget(STATE *state, int idx);
void updateStatus(STATE *s);
//Update status dari bangunan

void displayWaktu(STATE s);

#endif