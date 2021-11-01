/* File : Tas.h */
/* Definisi ADT Tas dengan representasi array secara eksplisit dan alokasi statik */
/* TOP adalah alamat elemen puncak */

#ifndef TAS_H
#define TAS_H

#include "boolean.h"
#include "item.h"

#define IDX_UNDEF -1
#define TASCAP 3

typedef Item ElTypeItm;
typedef struct
{
  ElTypeItm buffer[100]; /* tabel penyimpan elemen */
  int idxTop;            /* alamat TOP: elemen puncak */
  int currentMaxCapacity;
  short heavyCount;
} Tas;

/* ********* AKSES (Selektor) ********* */
/* Jika s adalah Tas, maka akses elemen : */
#define IDX_TOP(s) (s).idxTop
#define TOP(s) (s).buffer[(s).idxTop]
#define TasCap(s) (s).currentMaxCapacity
#define hCount(s) (s).heavyCount
/* *** Konstruktor/Kreator *** */
void CreateTas(Tas *s);
/* I.S. sembarang; */
/* F.S. Membuat sebuah tas S kosong dengan kondisi sbb: */
/* - Index top bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah s kosong */

/* ************ Prototype ************ */
boolean isEmptyTas(Tas s);
/* Mengirim true jika s kosong: lihat definisi di atas */
boolean isFullTas(Tas s);
/* Mengirim true jika tabel penampung nilai s Tas penuh */

/* ************ Menambahkan sebuah elemen ke Tas ************ */
void push(Tas *s, Item val);
/* Menambahkan val sebagai elemen Tas s */
/* I.S. s mungkin kosong, tabel penampung elemen Tas TIDAK penuh */
/* F.S. val menjadi TOP yang baru,IDX_TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Tas ************ */
void pop(Tas *s, Item *val);
/* Menghapus val dari Tas s */
/* I.S. s tidak mungkin kosong */
/* F.S. val adalah nilai elemen TOP yang lama, IDX_TOP berkurang 1 */

void increaseCurrentMaxCapacity(Tas *s);
/* I.S. max cap dari tas terdefinisi*/
/* F.S. max cap dari tas bertambah 1*/

void senterPembesar(Tas *s);

boolean isContainItem(Tas tas, Item item);
//Mengembalikan true jika item ada di dalam tas dan false jika tidak

void displayInProgress(Tas tas);
// Menunjukan barang teratas pada tas serta lokasi tujuannya
#endif
