#include <stdio.h>
#include "../header/tas.h"

/* *** Konstruktor/Kreator *** */
void CreateTas(Tas *s)
/* I.S. sembarang; */
/* F.S. Membuat sebuah Tas S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */
{
    IDX_TOP(*s) = IDX_UNDEF;
    TasCap(*s) = TASCAP;
    hCount(*s) = 0;
}

/* ************ Prototype ************ */
boolean isEmptyTas(Tas s)
/* Mengirim true jika s kosong: lihat definisi di atas */
{
    return (IDX_TOP(s) == IDX_UNDEF);
}

boolean isFullTas(Tas s)
/* Mengirim true jika tabel penampung nilai s Tas penuh */
{
    return (IDX_TOP(s) == (TasCap(s) - 1));
}

/* ************ Menambahkan sebuah elemen ke Tas ************ */
void push(Tas *s, Item val)
/* Menambahkan val sebagai elemen Tas s */
/* I.S. s mungkin kosong, tabel penampung elemen Tas TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */
/* Jika tas penuh maka tidak terjadi apa" dan dimunculkan pesan "Maaf anda tas penuh, silahkan turunkan satu item terlebih dahulu"*/
{
    if(!isFullTas(*s)){
        IDX_TOP(*s)++;
        TOP(*s) = val;
        if(TOP(*s).tipe == 'V'){

        }else if(TOP(*s).tipe == 'H'){
            hCount(*s)++;
        };
    }else{
        printf("TAS SUDAH PENUH! HARAP KIRIMKAN BARANG TERLEBIH DAHULU!\n\n");
    }
}

/* ************ Menghapus sebuah elemen Tas ************ */
void pop(Tas *s, Item *val)
/* Menghapus val dari Tas s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */
{
    if(!isEmptyTas(*s)){
        *val = TOP(*s);
        if(TOP(*s).tipe == 'H'){
            hCount(*s)--;
        };
        IDX_TOP(*s) -= 1;
    }else{
        printf("TAS SUDAH KOSONG, TIDAK ADA YANG BISA DITURUNKAN!\n");
    }
}

void increaseCurrentMaxCapacity(Tas *s){
    TasCap(*s)++;
};

void senterPembesar(Tas *s){
    if(TasCap(*s) * 2 <= 100){
        TasCap(*s) *= 2; 
    }
    else{
        TasCap(*s) = 100; 
    }
}

void kainPembungkusWaktu(Tas *tas){
    Tas tempTas;
    boolean found = false;
    while(!isEmptyTas(*tas) && !found){
        Item item;
        pop(tas,&item);
        if(ItemTipe(item) == 'P'){
            ItemWaktuSkrng(item) = ItemWaktuSampai(item);
            found = true;
        }
        push(&tempTas,item);
    }
    while(!isEmptyTas(tempTas)){
        Item item;
        pop(&tempTas,&item);
        push(tas,item);
    }
}

boolean isContainItem(Tas tas, Item item){
    Item tmp;
    boolean ada = false;
    while(!isEmptyTas(tas) && !ada){
        pop(&tas,&tmp);
        if (IsItemSama(tmp, item)){
            ada = true;
        }
    }
    return ada;
};

void displayInProgress(Tas tas){
    printf("Pesanan yang sedang diantarkan: \n");
    Item tmp;
    int i = 1;
    while(!isEmptyTas(tas)){
        printf("%d. ",i++);
        pop(&tas,&tmp); 
        printInProgressItem(tmp);
        printf("\n");
    }
    
};

void hapusPerishable(Tas *tas){
    Tas tempTas;
    while(!isEmptyTas(*tas)){
        Item item;
        pop(tas,&item);
        if(ItemTipe(item) == 'P' && ItemWaktuSkrng(item) <= 0){
            continue;
        }
        else{
            push(&tempTas,item);
        }
    }
    while(!isEmptyTas(tempTas)){
        Item item;
        pop(&tempTas,&item);
        push(tas,item);
    }
}