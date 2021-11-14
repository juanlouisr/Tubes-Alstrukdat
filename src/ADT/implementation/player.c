#include <stdio.h>
#include <stdlib.h>
#include "../../adtlib.h"

void createPlayer(PLAYER *p,LOKASI lokAwal, Tas tas, List todo,
                ListPos invGadget,  int uang, int speedBoostDur){
    pLoc(*p) = lokAwal;
    pTas(*p) = tas;
    pUang(*p) = uang;
    pTodo(*p) = todo;
    pInvG(*p) = invGadget;
    pSpdDur(*p) = speedBoostDur;
    (*p).vipReturned = 0;
}

void movePlayer(MAP m, PLAYER *p,int opt){
    if (opt > 0 && opt <= length(REACH(m)))
        pLoc(*p) = ELMTLD(REACH(m),opt-1);
}


void pickUp(PLAYER *p){
    if (TOP(pTas(*p)).tipe == VIP_ITEM){
        printf("ZHISUKA MARAH LHOO\n");
    }
    else{
        if (isFullTas(pTas(*p))){
            printf("TAS SUDAH PENUH! HARAP KIRIMKAN BARANG TERLEBIH DAHULU!\n");
        }
        else{
            boolean found = false;
            // Ngambil dari todolist
            Address temp = pTodo(*p);
            while (temp != NULL && !found){
                if (INFO(temp).locAwal == pLoc(*p).Nama){
                    found = true;
                    push(&pTas(*p), INFO(temp));
                    printf("Pesanan "); 
                    printInProgressItem(INFO(temp));
                    printf(" masuk tas!\n");
                    Item item;
                    int idx = indexOfTodoList(pTodo(*p), INFO(temp));
                    if (idx != IDX_UNDEF){
                        deleteAtTodoList(&pTodo(*p), idx, &item);
                    }
                }
                else{
                    temp = NEXT(temp);
                }
            }
        }
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
                pSpdDur(*p) = 10;
                break;
            case PERISHABLE_ITEM:
                pUang(*p) += 400;
                increaseCurrentMaxCapacity(&pTas(*p));
                break;
            case VIP_ITEM:
                pUang(*p) += 600;
                (*p).vipReturned++;
                break;
            default:
                break;
            }
            printf("Pesanan "); 
            printInProgressItem(item);
            printf(" berhasil diantar!\n");
        }
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

void displayMoney(PLAYER player){
    printf("Uang anda sekarang: %d Yen\n",pUang(player));
};

void displayCurrLoc(PLAYER player)
{
    printf("Mobita sekarang berada di titik ");
    TulisLOKASI(player.loc);
}

void returnToSender(PLAYER *player)
{
    if ((*player).vipReturned)
    {
        if (!isEmptyTas(pTas(*player)))
        {
            if (TOP(pTas(*player)).tipe != VIP_ITEM)
            {
                (*player).vipReturned--;
                Item item;
                pop(&pTas(*player), &item);
                if (item.tipe == PERISHABLE_ITEM)
                {
                    // reset internal time
                    item.internalTime = item.waktuSampai;
                }
                insertLastTodoList(&pTodo(*player), item);
            }
            else
            {
                printf("Mobita harus segera melayani Zhisuka!\n");
            }
        }
        {
            printf("Tas Mobita kosong!\n");
        }
    }
    else
    {
        printf("Mobita tidak memiliki Ability Return To Sender!\n");
    }
}