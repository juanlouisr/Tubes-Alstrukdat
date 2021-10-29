#ifndef MAP_H
#define MAP_H
#include "lokasi.h"
#include "daftarlokasi.h"

typedef struct {
   DaftarLokasi daftarlok ; /* Nama bangunan */ 
   char map[22][32];
   int row;
   int col;
   char adjacency[27][27];
   DaftarLokasi reachable;
} MAP;
#define ROW(M) (M).row
#define COL(M) (M).col
#define ELMTBLD(M,i) (M).daftarlok.buffer[(i)].Nama
#define ELMTX(M,i) (M).daftarlok.buffer[(i)].X
#define ELMTY(M,i) (M).daftarlok.buffer[(i)].Y
#define ELMTTP(M,i) (M).daftarlok.buffer[(i)].jenis
#define ELMTM(M,i,j) (M).map[(i)][(j)]
#define REACH(M) (M).reachable
#define nEffBuilding(M) (M).daftarlok.nEff
#define neffReach(m) (m).reachable.nEff
#define ELMTADJ(M,i,j) (M).adjacency[(i)][(j)]
#define LOK(M,i) (M).daftarlok.buffer[(i)]

void alokasiMAP(MAP *m,int row, int col,DaftarLokasi lok);
//Alokasi besar map

void mapBuilding(MAP *m);
//Memasukan lokasi building

void displayMAP(MAP m);
//Display map

boolean isIdxMapEff(MAP m, int i, int j);
//Return true jika index yang di akses efektif

void getAdjacent(MAP *m, FILE *file);
//Assign input ADJ matrix

char getBuilding(MAP m,int x,int y);
//Mengembalikan nama bangunan dengan memasukan koordinat

int getIdxBld(char c);
//Mengembalikan index bangunan di daftar lokasi

void displayReachable(MAP m);
//Menuliskan tempat yang bisa dicapai

void clearReachable(MAP *m);
//Menghapus matrix reachable
#endif