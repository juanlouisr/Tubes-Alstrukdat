#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include "daftarlokasi.h"
#include "player.h"
#include "../originaladt/listdin.h"
#include "../../adtlib.h"
typedef struct {
   DaftarLokasi daftarlok ; /* Nama bangunan */ 
   char map[22][32];
   int row;
   int col;
   char adjacency[27][27];
} MAP;
#define ROW(M) (M).row
#define COL(M) (M).col
#define ELMTBLD(M,i) (M).daftarlok.buffer[(i)].Nama
#define ELMTX(M,i) (M).daftarlok.buffer[(i)].X
#define ELMTY(M,i) (M).daftarlok.buffer[(i)].Y
#define ELMTTP(M,i) (M).daftarlok.buffer[(i)].jenis
#define ELMTM(M,i,j) (M).map[(i)][(j)]
#define nEffBuilding(M) (M).daftarlok.nEff
#define ELMTADJ(M,i,j) (M).adjacency[(i)][(j)]
#define LOK(M,i) (M).daftarlok.buffer[(i)]

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

void getAdjacent(MAP *m, FILE *file);
//Assign input ADJ matrix

void updateStatus(MAP *m,PLAYER p);
//Update status dari bangunan

char getBuilding(MAP m,int x,int y);
//Mengembalikan nama bangunan dengan memasukan koordinat

int getIdxBld(char c);
//Mengembalikan index bangunan di daftar lokasi
#endif