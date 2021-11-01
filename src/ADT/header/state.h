#ifndef STATE_H
#define STATE_H

#include "lokasi.h"
#include "map.h"

typedef struct {
    float waktu;
    float speedBoostDur;
    int countHeavy;
} STATE;

void incrementWaktu(STATE *time);

void mesinWaktu(STATE *time);
#endif