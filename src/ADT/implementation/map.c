#include <stdio.h>
#include <stdlib.h>
#include "../header/map.h"
#include "../../utillib.h"

void alokasiMAP(MAP *m,int row, int col,DaftarLokasi lok){
    (*m).daftarlok = lok;
    ROW(*m) = row;
    COL(*m) = col;
    int i,j;
    for(i=0;i<ROW(*m)+2;i++){
        for(j=0;j<COL(*m)+2;j++){
            if(i==0 || i==ROW(*m)+1 || j==0 || j==COL(*m)+1){
                ELMTM(*m,i,j) = '*';
            }else{
                ELMTM(*m,i,j) = ' ';
            }
            
        }
    }
};
//Alokasi besar map

void mapBuilding(MAP *m){
    int i;
    for(i=0;i<nEffBuilding(*m);i++){
        ELMTM(*m,ELMTX(*m,i),ELMTY(*m,i)) = ELMTBLD(*m,i);
    }
};
//Memasukan lokasi building

void displayMAP(MAP m){
    int i,j;
    for(i=0;i<ROW(m)+2;i++){
        for(j=0;j<COL(m)+2;j++){
            printf("%c",ELMTM(m,i,j));
        }
        printf("\n");
    }
};

boolean isIdxMapEff(MAP m,int i,int j){
    return (i>0&&i<=ROW(m))&&(j>0&&j<=COL(m));
};

void getAdjacent(MAP *m,FILE *file){
    int i,j;
    for(i=0;i<nEffBuilding(*m);i++){
        for(j=0;j<nEffBuilding(*m);j++){
            ELMTADJ(*m,i,j) = getCharInputStream(file);
        }
    }
};



// int main(void){
//     MAP M1;
//     DaftarLokasi DL;
//     CreateDaftarLokasi(&DL,17);
//     int i;
//     char b;
//     int x,y;
//     LOKASI P;
//     for(i=0;i<17;i++){
//         scanf(" %c",&b);
//         scanf("%d",&x);
//         scanf("%d",&y);
//         P = MakeLOKASI(b,x,y,'b');
//         insertLast(&DL,P);
//     }   
//     alokasiMAP(&M1,10,15,DL);
//     mapBuilding(&M1);
//     displayMAP(M1);
//     return 0;
// }
//Display map