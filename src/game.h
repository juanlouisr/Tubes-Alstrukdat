#ifndef __GAME_H__
#define __GAME_H__
#include "adtlib.h"
#include "utillib.h"

extern Word inptCfg;
extern Word commands[1000];
extern int args[1000];
extern int ccount;
extern int arguCount;


void LoadConfig(MAP *map, PLAYER *player, Queue *queue, FILE *file);
void LoadNewState(STATE *state);
void GameHandler(Word command, STATE *state, FILE *file);
void displayHelp();
void move(STATE *state, FILE *file);
void buy(STATE *state, FILE *file);
void use(STATE *state, FILE *file);
void save(STATE *state);
void load(STATE *state);

#endif