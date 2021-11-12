#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    if(pSpdDur(CURR_PLAYER(*state)) > 0 && hCount(CURR_TAS(*state)) < 1){
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
    boolean found = false;
    while (!isEmptyQ(CURR_QUEUE(*state)) && HEAD(CURR_QUEUE(*state)).waktudatang <= CURR_TIME(*state))
    {
        Item item;
        dequeue(&CURR_QUEUE(*state), &item);
        insertLastTodoList(&CURR_TODO(*state), item);
    }
    // CEK DELTA TIME
    // KURANGIN MASING MASING INTERNAL TIME PERISHABLE ITEM DALAM TAS DENGAN DELTA TIME
    for(int i=0; i<=IDX_TOP(CURR_TAS(*state)); i++){
        if(ItemTipe(CURR_TAS(*state).buffer[i]) == 'P'){
            ItemWaktuSkrng(CURR_TAS(*state).buffer[i]) -= deltaTime;
        }
    }
    hapusPerishable(&CURR_TAS(*state));
    
}


void updateStatus(STATE *s){
    int i;
    int idx;
    char c;
    Address ADR = CURR_TODO(*s);
    c = getBuilding(CURR_MAP(*s),CURR_PLAYER(*s).loc.X ,CURR_PLAYER(*s).loc.Y );
    idx = getIdxBld(c,CURR_MAP(*s));
    for(i=0;i<nEffBuilding(CURR_MAP(*s));i++){
        ELMTTP(CURR_MAP(*s),i) = 'b';
    }
    clearReachable(&CURR_MAP(*s));
    for(i=0;i<nEffBuilding(CURR_MAP(*s));i++){
        if(ELMTADJ(CURR_MAP(*s),idx,i) == '1'){
            ELMTTP(CURR_MAP(*s),i) = 'r';
            insertLast(&CURR_MAP(*s).reachable,LOK(CURR_MAP(*s),i));
        } 
    }
    while(ADR != NULL){
        if(!isContainItem(CURR_TAS(*s), INFO(ADR))){
            idx = getIdxBld(INFO(ADR).locAwal,CURR_MAP(*s));
            ELMTTP(CURR_MAP(*s),idx) = 'p';
        }
        ADR = NEXT(ADR);
    }
    if(!isEmptyTas(pTas(CURR_PLAYER(*s)))){
        idx = getIdxBld(TOP(pTas(CURR_PLAYER(*s))).locAkhir,CURR_MAP(*s));
        ELMTTP(CURR_MAP(*s),idx) = 'd';
    }
    idx = getIdxBld(c,CURR_MAP(*s));
    ELMTTP(CURR_MAP(*s),idx) = 'm';
}


void useGadget(STATE *state, int idx){
    if (idx == 0)
    {
        return;
    }
    idx--;
    PLAYER *p = &CURR_PLAYER(*state);
    ElType temp;
    if(!isIdxValidListStat(pInvG(*p), idx)){
        printf("Tidak ada gadget yang dapat digunakan.");
    }
    else if(ELMTLS(pInvG(*p), idx) == VAL_UNDEF){
        printf("Tidak ada gadget yang dapat digunakan.");
    }
    else if(ELMTLS(pInvG(*p), idx) == 1){
        printf("Kain pembungkus waktu berhasil digunakan.");
        kainPembungkusWaktu(&pTas(*p));
        deleteAtListStat(&pInvG(*p), idx, &temp);
    }
    else if(ELMTLS(pInvG(*p), idx) == 2){
        printf("Senter pembesar berhasil digunakan.");
        senterPembesar(&pTas(*p));
        deleteAtListStat(&pInvG(*p), idx, &temp);
    }
    else if(ELMTLS(pInvG(*p), idx) == 3){
        printf("Pintu kemana saja berhasil digunakan.");
        pintuKemanaSaja(state);
        deleteAtListStat(&pInvG(*p), idx, &temp);
    }
    else if(ELMTLS(pInvG(*p), idx) == 4){
        printf("Mesin waktu berhasil digunakan.");
        mesinWaktu(state);
        deleteAtListStat(&pInvG(*p), idx, &temp);
    }
    printf("\n");
    
}


void mesinWaktu(STATE *state){
    if(CURR_TIME(*state) >= 50){
        CURR_TIME(*state) -= 50;
    }
    else{
        CURR_TIME(*state) = 0;
    }
}


void pintuKemanaSaja(STATE *s){
    displayList(CURR_MAP(*s).daftarlok);
    printf("Mau pindah kemana?");
    printf(">> ");
    int opt = getIntSTDIN();
    if (opt < 0 && opt > length(CURR_MAP(*s).daftarlok))
    {
        printf("Lokasi tidak valid!\n");
    }
    else
    {
        if (opt != 0)
        {
            pLoc(CURR_PLAYER(*s)) = ELMTLD(CURR_MAP(*s).daftarlok, opt-1);
        }
    }
}

void displayWaktu(STATE s)
{
    printf("Waktu: %.0f\n", floor(CURR_TIME(s)));
}

boolean gameOver(STATE s)
{
    return isEmptyQ(CURR_QUEUE(s))
        && isEmptyTas(CURR_TAS(s))
        && isEmptyTodoList(CURR_TODO(s));
}