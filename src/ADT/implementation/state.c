#include <stdio.h>
#include <stdlib.h>
#include "../header/state.h"


void CreateSTATE(STATE* state, PLAYER p, MAP map, Queue queue, float startTime)
{
    CURR_TIME(*state) = startTime;
    CURR_MAP(*state) = map;
    CURR_QUEUE(*state) = queue;
    CURR_PLAYER(*state) = p;
}


void incrementWaktu(STATE *state){
    float deltaTime = 0;
    if(pSpdDur(CURR_PLAYER(*state)) > 0 && hCount(CURR_TAS(*state)) == 0){
        pSpdDur(CURR_PLAYER(*state))  -= 1;
        deltaTime += 0.5;
    }
    else if(hCount(CURR_TAS(*state)) > 0){
        deltaTime += hCount(CURR_TAS(*state)) + 1;
        pSpdDur(CURR_PLAYER(*state))  = 0;
    }
    else{
        deltaTime += 1;
    }
    CURR_TIME(*state) += deltaTime;
}

void mesinWaktu(STATE *state){
    if(CURR_TIME(*state) >= 50){
        CURR_TIME(*state) -= 50;
    }
    else{
        CURR_TIME(*state) = 0;
    }
}