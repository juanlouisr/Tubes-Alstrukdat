#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void createPlayer(PLAYER *p,LOKASI lokAwal, Tas tas, 
        ListPos invGadget,  int uang, int speedBoostDur){
    pLoc(*p) = lokAwal;
    pTas(*p) = tas;
    pUang(*p) = uang;
    pInvG(*p) = invGadget;
    pSpdDur(*p) = speedBoostDur;
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

void useGadget(PLAYER *p, int idx){
    if(!isIdxValidListStat(pInvG(*p), idx)){
        printf("Tidak ada gadget yang dapat digunakan.\n");
    }
    else if(ELMTLS(pInvG(*p), idx) == VAL_UNDEF){
        printf("Tidak ada gadget yang dapat digunakan.\n");
    }
    else if(ELMTLS(pInvG(*p), idx) == 1){
        //kainPembungkuswaktu()
        ELMTLS(pInvG(*p), idx) = VAL_UNDEF;
    }
    else if(ELMTLS(pInvG(*p), idx) == 2){
        //SenterPembesar()
        ELMTLS(pInvG(*p), idx) = VAL_UNDEF;
    }
    else if(ELMTLS(pInvG(*p), idx) == 3){
        //pintuKemanaSaja()
        ELMTLS(pInvG(*p), idx) = VAL_UNDEF;
    }
    else if(ELMTLS(pInvG(*p), idx) == 4){
        //mesinWaktu()
        ELMTLS(pInvG(*p), idx) = VAL_UNDEF;
    }
}


void buyGadget(PLAYER *player, int idx){
    if(isFullListStat(pInvG(*player))){
        printf("Inventory penuh.\n");
    }
    else if(idx < 0 && idx > 4){
        printf("Tidak ada gadget yang dapat dibeli.\n");
    }
    else{
        if(idx == 1){
            if((*player).uang >= 800 ){
                (*player).uang -= 800;
                insertLastListStat(&pInvG(*player), idx);
                printf("Kain Pembungkus Waktu berhasil dibeli.\n");
                printf("Uang Anda sekarang : %d Yen", (*player).uang);
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget.\n");
            }
        }
        if(idx == 2){
            if((*player).uang >= 1200 ){
                (*player).uang -= 1200;
                insertLastListStat(&pInvG(*player), idx);
                printf("Senter Pembesar berhasil dibeli.\n");
                printf("Uang Anda sekarang : %d Yen", (*player).uang);
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget.\n");
            }
        }
        else if(idx == 3){
            if((*player).uang >= 1500 ){
                (*player).uang -= 1500;
                insertLastListStat(&pInvG(*player), idx);
                printf("Pintu Kemana Saja berhasil dibeli.\n");
                printf("Uang Anda sekarang : %d Yen", (*player).uang);
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget.\n");
            }
        }
        else if(idx == 4){
            if((*player).uang >= 3000 ){
                (*player).uang -= 3000;
                insertLastListStat(&pInvG(*player), idx);
                printf("Mesin Waktu berhasil dibeli.\n");
                printf("Uang Anda sekarang : %d Yen", (*player).uang);
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget.\n");
            }
        }
    }
}

