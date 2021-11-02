#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void createPlayer(PLAYER *p,LOKASI lokAwal, int uang, Tas tas){
    pLoc(*p) = lokAwal;
    pTas(*p) = tas;
    pUang(*p) = uang;
}

void movePlayer(MAP m, PLAYER *p,int opt){
    pLoc(*p) = ELMTLD(REACH(m),opt-1);
}

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

void pickUp(PLAYER *p){
    if (TOP(pTas(*p)).tipe == VIP_ITEM){
        printf("ZHISUKA MARAH LHOO\n");
    }
    else{
        boolean found = false;
        // Ngambil dari todolist
        // Address temp = pTodo(*p);
        // while (temp != NULL && !found){
        //     if (INFO(temp).locAwal == pLoc(*p).Nama){
        //         if (!isContainItem(pTas(*p), INFO(temp))){
        //             found == true;
        //             push(pTas(*p), INFO(temp))
        //         }
        //     }
        //     temp = NEXT(temp);
        // }
    }
}

void dropOff(PLAYER *p){
    if (!isEmptyTas(pTas(*p))){
        if (pLoc(*p).Nama == TOP(pTas(*p)).locAkhir){
            Item item;
            pop(&pTas(*p), &item);
            switch (item.tipe)
            {
            case NORMAL_ITEM:
                pUang(*p) += 200;
                break;
            case HEAVY_ITEM:
                pUang(*p) += 400;
                pSpdDur(*p) = 5;
                break;
            case PERISHABLE_ITEM:
                pUang(*p) += 400;
                increaseCurrentMaxCapacity(&pTas(*p));
                break;
            case VIP_ITEM:
                pUang(*p) += 600;
                // tambah abilty return to sender
                break;
            default:
                break;
            }
            // Hapus dari todo
            // int idx = indexOfLinkedList(pTodo(*p), item);
            // if (idx != -1){
            //     deleteAt(&pTodo(*p), idx, &item);
            // }
        }
    }
}

