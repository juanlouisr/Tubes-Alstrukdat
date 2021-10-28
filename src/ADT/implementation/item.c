#include "../header/item.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create Item Pesanan */
void CreateItemPesanan(Item* item, TipeItem tipe, char lokasiPickup, char lokasiDropOff, int waktudatang, int waktusampai)
/* I.S.item bebas, tipe 'N', 'H', 'V', atau 'P' */
/* lokasi pickup valid terdefinisi dalam listdinamis lokasi */
/* lokasi pickup valid terdefinisi dalam listdinamis lokasi */
/* waktu datang bilangan positif  */
{
    ItemTipe(*item) = tipe;
    ItemLokasiPickup(*item) = lokasiPickup;
    ItemLokasiDropoff(*item) = lokasiDropOff;
    ItemWaktuDatang(*item) = waktudatang;
    ItemWaktuSampai(*item) = waktusampai;
    ItemWaktuSkrng(*item) = waktusampai;
}

/* ********** OPERASI RELASIONAL ********** */
boolean IsItemSama(Item item1, Item item2)
/* I.S. item1 dan item2 terdefinisi */
/* menghasilkan true jika tipe, lokasi awal, 
lokasi akhir, dan waktu datang sama */
{
    return ItemTipe(item1) == ItemTipe(item2) &&
        ItemLokasiPickup(item1) == ItemLokasiPickup(item2) &&
        ItemLokasiDropoff(item1) == ItemLokasiDropoff(item2) &&
        ItemWaktuDatang(item1) == ItemWaktuDatang(item2);

}

/* ********** OPERASI  ********** */
void printToDoItem(Item item)
/* I.S. Item terdefinisi, 
mencetak dalam format 
G -> F (Normal Item) *tanpa newline */
{
    printf("%c -> %c (", ItemLokasiPickup(item), ItemLokasiDropoff(item));
    switch (ItemTipe(item))
    {
    case 'N':
        printf("Normal Item)");
        break;
    case 'H':
        printf("Heavy Item)");
        break;
    case 'V':
        printf("VIP Item)");
        break;
    case 'P':
        printf("Perishable Item, sisa waktu %d)", item.waktuSampai);
        break;

    default:
        printf("(?? Item)");
        break;
    }
}

void printInProgressItem(Item item)
{
    
    switch (ItemTipe(item))
    {
    case 'N':
        printf("Normal Item");
        break;
    case 'H':
        printf("Heavy Item");
        break;
    case 'V':
        printf("VIP Item");
        break;
    case 'P':
        printf("Perishable Item, sisa waktu %d", item.waktuSampai);
        break;

    default:
        printf("?? Item)");
        break;
    }
    printf(" (Tujuan: %c)", item.locAkhir);
}

void readItem(Item* item, FILE* file)
{
    int waktuDatang = getIntInputStream(file);
    int waktuSampai = 0;
    char locAwal = getCharInputStream(file);
    char locAkhir = getCharInputStream(file);
    char tipe = getCharInputStream(file);
    if (tipe == PERISHABLE_ITEM)
    {
        waktuSampai = getIntInputStream(file);
    }
    CreateItemPesanan(item, tipe, locAwal, locAkhir, waktuDatang, waktuSampai);
}