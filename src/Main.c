#include <stdio.h>
#include "adtlib.h"
#include "utillib.h"

int main()
{
    printLogo();
    printMenu();
    FILE* file = fopen("src/data/config.cfg", "r");
    if (file != NULL)
    {
        printf(">> ");
        Word word = getWordInputStream(stdin);

        if (isWordEQ(word, "1"))
        {
            printf("NEW GAME!\n");
                int row = getIntInputStream(file);
            int col = getIntInputStream(file);
            printf("row : %d, col : %d\n", row, col);
            int jmlBangunan = getIntInputStream(file);

            MAP M1;
            DaftarLokasi DL;
            CreateDaftarLokasi(&DL, jmlBangunan);
            int i;
            char b;
            int x,y;
            LOKASI P;
            for(i=0;i<jmlBangunan;i++){
                b = getCharInputStream(file);
                x = getIntInputStream(file);
                y = getIntInputStream(file);
                P = MakeLOKASI(b,x,y,'b');
                insertLast(&DL,P);
            }   
            alokasiMAP(&M1,10,15,DL);
            mapBuilding(&M1);
            displayMAP(M1);
            
        }
        else if (isWordEQ(word, "2"))
        {
            printf("LOAD GAME!\n");
        }
        else
        {
            fclose(file);
            printf("SAMPAI JUMPA LAGI!\n");
        }
    }
    
    
    

    // printf("hasil get word stdin: ");
    // wordOutputStream(stdout, word, true);

    // char c = getCharSTDIN();
    // printf("hasil get char: %c\n", c);

    

    return 0;
}
