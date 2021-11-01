
#include "../../adtlib.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStat(ListPos *l)
{
    int i;
    for (i = 0; i < LSCAP; i++)
    {
        ELMTLS(*l, i) = VAL_UNDEF;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int lengthListStat(ListPos l)
{
    boolean notMark = true;
    int i = 0;
    if (isEmptyListStat(l))
    {
        return 0;
    }
    else
    {
        while (i < LSCAP && notMark)
        {
            if (ELMTLS(l, i) != VAL_UNDEF)
            {
                i++;
            }
            else
            {
                notMark = false;
            }
        }
        return i;
    }
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListStat(ListPos l, int i)
{
    return (i > IDX_UNDEF && i < LSCAP);
}

boolean isIdxEffListStat(ListPos l, int i)
{
    return (i > IDX_UNDEF && i < lengthListStat(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListStat(ListPos l)
{
    return (ELMTLS(l, 0) == VAL_UNDEF);
}

/* *** Test List penuh *** */
boolean isFullListStat(ListPos l)
{
    return (ELMTLS(l, LSCAP - 1) != VAL_UNDEF);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readListStat(ListPos *l)
{
    int n;
    int i;
    int x;

    do
    {
        scanf("%d", &n);
    } while (n < 0 || n > LSCAP);

    CreateListStat(l);
    if (n > 0)
    {
        for (i = 0; i < n; i++)
        {
            scanf("%d", &ELMTLS(*l, i));
        }
    }
}

void displayGadget(){
    printf("Gadget yang tersedia : \n");
    printf("1. Kain Pembungkus Waktu (800 Yen)\n");
    printf("2. Senter Pembesar (1200 Yen)\n");
    printf("3. Pintu Kemana Saja (1500 Yen)\n");
    printf("4. Mesin Waktu (3000 Yen)\n");
    printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
}

void displayInventory(ListPos l){
    for(int i=0; i<LSCAP; i++){
        if(ELMTLS(l, i) == 1){
            printf("%d. Kain Pembungkus Waktu\n");
        }
        else if(ELMTLS(l, i) == 2){
            printf("%d. Senter Pembesar\n");
        }
        else if(ELMTLS(l, i) == 3){
            printf("%d. Pintu Kemana Saja\n");
        }
        else if(ELMTLS(l, i) == 4){
            printf("%d. Mesin Waktu\n");
        }
        else if(ELMTLS(l, i) == VAL_UNDEF){
            printf("%d. -\n");
        }
    }
    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n");
}

void useGadget(ListPos *l, int idx){
    if(!isIdxValidListStat(*l, idx)){
        printf("Tidak ada gadget yang dapat digunakan.\n");
    }
    else if(ELMTLS(*l, idx) == VAL_UNDEF){
        printf("Tidak ada gadget yang dapat digunakan.\n");
    }
    else if(ELMTLS(*l, idx) == 1){
        //kainPembungkuswaktu()
        ELMTLS(*l, idx) = VAL_UNDEF;
    }
    else if(ELMTLS(*l, idx) == 2){
        //SenterPembesar()
        ELMTLS(*l, idx) = VAL_UNDEF;
    }
    else if(ELMTLS(*l, idx) == 3){
        //pintuKemanaSaja()
        ELMTLS(*l, idx) = VAL_UNDEF;
    }
    else if(ELMTLS(*l, idx) == 4){
        //mesinWaktu()
        ELMTLS(*l, idx) = VAL_UNDEF;
    }
}

void buyGadget(ListPos *l, int idx, PLAYER *player){
    if(isFullListStat(*l)){
        printf("Inventory penuh.\n");
    }
    else if(idx < 0 && idx > 4){
        printf("Tidak ada gadget yang dapat dibeli.\n");
    }
    else{
        if(idx == 1){
            if((*player).uang >= 800 ){
                (*player).uang -= 800;
                insertAtEmpty(l, idx);
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
                insertAtEmpty(l, idx);
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
                insertAtEmpty(l, idx);
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
                insertAtEmpty(l, idx);
                printf("Mesin Waktu berhasil dibeli.\n");
                printf("Uang Anda sekarang : %d Yen", (*player).uang);
            }
            else{
                printf("Uang tidak cukup untuk membeli gadget.\n");
            }
        }
    }
}



/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListStatEqual(ListPos l1, ListPos l2)
{
    int i;
    boolean isEqual = true;

    if (lengthListStat(l1) == lengthListStat(l2))
    {
        i = 0;
        while (i < lengthListStat(l1) && isEqual)
        {
            if (ELMTLS(l1, i) == ELMTLS(l2, i))
            {
                i++;
            }
            else
            {
                isEqual = false;
            }
        }
    }
    else
    {
        isEqual = false;
    }
    return isEqual;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListStat(ListPos l, ElType val)
{
    int i = 0;
    boolean notFound = true;

    if (isEmptyListStat(l))
    {
        return IDX_UNDEF;
    }
    else
    {
        while (i < lengthListStat(l) && notFound)
        {
            if (ELMTLS(l, i) == val)
            {
                notFound = false;
            }
            else
            {
                i++;
            }
        }
        if (!notFound)
        {
            return i;
        }
        else
        {
            return IDX_UNDEF;
        }
    }
}

/* ********** NILAI EKSTREM ********** */
void extremesListStat(ListPos l, ElType *max, ElType *min)
{
    int i;
    *max = ELMTLS(l, 0);
    *min = ELMTLS(l, 0);

    for (i = 1; i < lengthListStat(l); i++)
    {
        if (*max < ELMTLS(l, i))
        {
            *max = ELMTLS(l, i);
        }
        else if (*min > ELMTLS(l, i))
        {
            *min = ELMTLS(l, i);
        }
    }
}



/* ********** SORTING ********** */
void sortListStat(ListPos *l, boolean asc)
{
    int i, pass, temp, index;
    if (lengthListStat(*l) > 1)
    {
        for (pass = 0; pass < lengthListStat(*l); pass++)
        {
            index = pass;
            for (i = pass + 1; i < lengthListStat(*l); i++)
            {
                if (asc)
                {

                    if (ELMTLS(*l, index) > ELMTLS(*l, i))
                    {
                        index = i;
                    }
                }
                else
                {
                    if (ELMTLS(*l, index) < ELMTLS(*l, i))
                    {
                        index = i;
                    }
                }
            }
            if (index != pass)
            {
                temp = ELMTLS(*l, index);
                ELMTLS(*l, index) = ELMTLS(*l, pass);
                ELMTLS(*l, pass) = temp;
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastListStat(ListPos *l, ElType val)
{
    ELMTLS(*l, lengthListStat(*l)) = val;
}

void insertAtEmpty(ListPos *l, ElType val){
    int i=0;
    while(i < LSCAP){
        if(ELMTLS(*l, i) == VAL_UNDEF){
            ELMTLS(*l, i) = val;
            break;
        }
        else{
            i++;
        }
    }
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastListStat(ListPos *l, ElType *val)
{
    *val = ELMTLS(*l, lengthListStat(*l) - 1);
    ELMTLS(*l, lengthListStat(*l) - 1) = VAL_UNDEF;
}
