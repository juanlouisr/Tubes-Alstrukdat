#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void incrementWaktu(STATE *time, Tas tas){
    if((*time).speedBoostDur > 0 && hCount(tas) == 0){
        (*time).speedBoostDur -= 1;
        (*time).waktu += 0.5;
    }
    else if(hCount(tas) > 0){
        (*time).waktu += hCount(tas) + 1;
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