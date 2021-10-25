#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include "daftarlokasi.h"

typedef struct {
   DaftarLokasi daftarlok ; /* Nama bangunan */ 
   char map[22][32];
   int row;
   int col;
} MAP;
#define ROW(M) (M).row
#define COL(M) (M).col
#define ELMTBLD(M,i) (M).daftarlok.buffer[(i)].Nama
#define ELMTX(M,i) (M).daftarlok.buffer[(i)].X
#define ELMTY(M,i) (M).daftarlok.buffer[(i)].Y
#define ELMTM(M,i,j) (M).map[(i)][(j)]
#define nEffBuilding(M) (M).daftarlok.nEff


void alokasiMAP(MAP *m,int row, int col,DaftarLokasi lok);
//Alokasi besar map

void mapBuilding(MAP *m);
//Memasukan lokasi building

void updatePlayerLoc(MAP *m, LOKASI tujuan);
//Update lokasi palyer di map

void displayMAP(MAP m);
//Display map

boolean isIdxMapEff(MAP m, int i, int j);
//Return true jika index yang di akses efektif
#endif