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
            char b;
            int x,y;
            LOKASI P;
            MAP M1;
            DaftarLokasi DL;
            int i,j;
            PLAYER P1;
            x = getIntInputStream(file);
            y = getIntInputStream(file);
            P = MakeLOKASI('8',x,y,'h');
            int jmlBangunan = getIntInputStream(file);
            CreateDaftarLokasi(&DL, jmlBangunan+1);
            insertLast(&DL,P);
            createPlayer(&P1,ELMTLD(DL,0));
            for(i=0;i<jmlBangunan;i++){
                b = getCharInputStream(file);
                x = getIntInputStream(file);
                y = getIntInputStream(file);
                P = MakeLOKASI(b,x,y,'b');
                insertLast(&DL,P);
            }
            alokasiMAP(&M1,row,col,DL);
            mapBuilding(&M1);
            getAdjacent(&M1,file);
            updateStatus(&M1,P1);
            displayMAP(M1);
            printf("\n");
            displayReachable(M1);

            // TEST QUEUE
            printf("\n");
            Queue items;
            Tas Tas1;
            Item barang1;
            CreateTas(&Tas1);
            CreateQueue(&items);
            increaseCurrentMaxCapacity(&Tas1);
            readAllItem(&items, file);
            printf("Inp prog:\n");
            for (int i = IDX_HEAD(items); i <= IDX_TAIL(items) ; i++)
            {
                printf("%d. ", i+1);
                printInProgressItem(items.buffer[i]);
                printf("\n");
            }
            printf("To do:\n");
            for (int i = IDX_HEAD(items); i <= IDX_TAIL(items) ; i++)
            {
                printf("%d. ", i+1);
                printToDoItem(items.buffer[i]);
                printf("\n");
                push(&Tas1,(items).buffer[i]);
            }
            displayInProgress(Tas1);
            for(i = 0;i<5;i++){
                pop(&Tas1,&barang1);
            };

            
        }
        else if (isWordEQ(word, "2"))
        {
            printf("LOAD GAME!\n");
        }
        else
        {
            printf("SAMPAI JUMPA LAGI!\n");
        }
    }
    fclose(file);
    
    
    

    // printf("hasil get word stdin: ");
    // wordOutputStream(stdout, word, true);

    // char c = getCharSTDIN();
    // printf("hasil get char: %c\n", c);

    

    return 0;
}
