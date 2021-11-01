#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void incrementWaktu(STATE *time){
    if((*time).speedBoostDur > 0 && (*time).countHeavy == 0){
        (*time).speedBoostDur -= 1;
        (*time).waktu += 0.5;
    }
    else if((*time).countHeavy > 0){
        (*time).waktu += (*time).countHeavy + 1;
        (*time).speedBoostDur = 0;
    }
    else{
        (*time).waktu += 1;
    }
}

void mesinWaktu(STATE *time){
    if((*time).waktu >= 50){
        (*time).waktu -= 50;
    }
    else{
        (*time).waktu = 0;
    }
}