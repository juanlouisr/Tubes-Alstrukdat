#ifndef STATE_H
#define STATE_H

#include "lokasi.h"
#include "map.h"

typedef struct {
    float waktu;
    float speedBoostDur;
} STATE;

void incrementWaktu(STATE *time, Tas tas);

void mesinWaktu(STATE *time);
#endif