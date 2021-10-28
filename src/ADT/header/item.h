#ifndef __ITEM_H__
#define __ITEM_H__

#include "boolean.h"
#include "../../utillib.h"
// #include "point.h"

typedef enum TIPE_ITEM{
    NORMAL_ITEM = 'N',
    HEAVY_ITEM = 'H',
    PERISHABLE_ITEM = 'P',
    VIP_ITEM = 'V'
} TipeItem;

/* Definisi elemen dan koleksi objek */
typedef struct
{
    TipeItem tipe;
    char locAwal;  // Lokasi pickup
    char locAkhir; // Lokasi Drop off
    int waktudatang; // Waktu bisa di pickup
    int waktuSampai; // Waktu saat pertama kali dia masuk jika perishable
    float internalTime; // Waktu yang dikurangin waktu berjalan
} Item;

/* ********** SELEKTOR ********** */
#define ItemTipe(item) (item).tipe 
#define ItemLokasiPickup(item) (item).locAwal 
#define ItemLokasiDropoff(item) (item).locAkhir 
#define ItemWaktuDatang(item) (item).waktudatang 
#define ItemWaktuSampai(item) (item).waktuSampai 
#define ItemWaktuSkrng(item) (item).internalTime 

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create Item Pesanan */
void CreateItemPesanan(Item* item, TipeItem tipe, char lokasiPickup, char lokasiDropOff, int waktudatang, int waktusampai);
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
void printToDoItem(Item item);
/* I.S. Item terdefinisi, 
mencetak dalam format 
G -> F (Normal Item) *tanpa newline */

void printInProgressItem(Item item);

void readItem(Item* item, FILE* file);


#endif