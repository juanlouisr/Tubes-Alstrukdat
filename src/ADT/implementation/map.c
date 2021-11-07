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
    CreateDaftarLokasi(&REACH(*m),nEffBuilding(*m));
};
//Memasukan lokasi building

char getBuilding(MAP m,int x,int y){
    int i;
    for(i=0;i<nEffBuilding(m);i++){
        if(ELMTX(m,i) == x && ELMTY(m,i) == y){
            return ELMTBLD(m,i);
        };
    }
};

int getIdxBld(char c,MAP M){
    for(int i=0;i<nEffBuilding(M);i++){
        if(ELMTBLD(M,i) == c){
            return i;
        }
    }
};

void displayMAP(MAP m){
    int i,j;
    for(i=0;i<ROW(m)+2;i++){
        for(j=0;j<COL(m)+2;j++){
            if(ELMTM(m,i,j) != '*' && ELMTM(m,i,j) != ' '){
                int idx;
                idx = getIdxBld(ELMTM(m,i,j),m);
                if(ELMTTP(m,idx) == 'm'){
                    print_yellow(ELMTM(m,i,j));
                }else if(ELMTTP(m,idx) == 'd'){
                    print_blue(ELMTM(m,i,j));
                }else if(ELMTTP(m,idx) == 'p'){
                    print_red(ELMTM(m,i,j));
                }else if(ELMTTP(m,idx) == 'r'){
                    print_green(ELMTM(m,i,j));
                }else{
                    printf("%c",ELMTM(m,i,j));
                }
            }else{
                printf("%c",ELMTM(m,i,j));
            }
            
        }
        printf("\n");
    }
};

void displayReachable(MAP m){
    int i;
    printf("Tempat yang bisa dicapai: \n");
    for(i=0;i<neffReach(m);i++){
        printf("%d. ",i+1);
        TulisLOKASI(ELMTLD(REACH(m),i));
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

void clearReachable(MAP *m){
    ElTypeDL tmp;
    while(!isEmpty(REACH(*m))){
        deleteLast(&REACH(*m),&tmp);
    }
};

void displayAdjacent(MAP m){
    int i,j;
    for(i=0;i<18;i++){
        for(j=0;j<18;j++){
            printf("%c",ELMTADJ(m,i,j));
        }
        printf("\n");
    }
}

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