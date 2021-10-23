#ifndef __ITEM_H__
#define __ITEM_H__

#include "boolean.h"
// #include "point.h"

/* Definisi elemen dan koleksi objek */
typedef struct
{
    char tipe;
    char locAwal;   // bingung mau pake Point aja atau char
    char locAkhir; // bingung mau pake Point aja atau char
    int waktudatang;
    int waktuSampai;
} Item;

/* ********** SELEKTOR ********** */
#define ItemTipe(item) (item).tipe 
#define ItemLokasiPickup(item) (item).locAwal 
#define ItemLokasiDropoff(item) (item).locAkhir 
#define ItemWaktuDatang(item) (item).waktudatang 
#define ItemWaktuSampai(item) (item).waktuSampai 

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create Item Pesanan */
void CreateItemPesanan(Item* item, char tipe, char lokasiPickup, char lokasiDropOff, int waktudatang, int waktusampai);
/* I.S.item bebas, tipe 'N', 'H', 'V', atau 'P' */
/* lokasi pickup valid terdefinisi dalam listdinamis lokasi */
/* lokasi pickup valid terdefinisi dalam listdinamis lokasi */
/* waktu datang bilangan positif  */

/* ********** OPERASI RELASIONAL ********** */
boolean IsItemSama(Item item1, Item item2);
/* I.S. item1 dan item2 terdefinisi */
/* menghasilkan true jika tipe, lokasi awal, 
lokasi akhir, dan waktu datang sama */

/* ********** OPERASI  ********** */
void PrintItem(Item item);
/* I.S. Item terdefinisi, 
mencetak dalam format 
G -> F (Normal Item) *tanpa newline */

#endif