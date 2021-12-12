/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 9/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_5_rotateArray.c -o 14a_5_rotateArray
//      gcc 9.1.0
//
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//      - algoritmasını kendim yazdım, bir yerden alınmamıştır.
//      - SA = BIT      KOF = NULL
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DIZIUZUNLUGU 4

void dondur(int *, int);

int main(int argc, char **argv)
{
    //int *dizi = malloc(-1);
    int *dizi = malloc(sizeof *dizi * DIZIUZUNLUGU);
    if (dizi == NULL)
    {
        perror("dizi mallocta hata oldu.\nHata");
        goto cikis;
    }
    /* dizi[0] = 1;
    dizi[1] = 2;
    dizi[2] = 3;
    dizi[3] = 4;
    dizi[4] = 5;
    dizi[5] = 6;
    dizi[6] = 7;
    dizi[7] = 8;
    //dizi[8] = 9; */

    dizi[0] = -1;
    dizi[1] = -100;
    dizi[2] = 3;
    dizi[3] = 99;

    dondur(dizi, 2);

cikis:
    free(dizi);
    dizi = NULL;
    if(dizi==NULL)
        fprintf(stdout, "dizi koflandi!\n");
    return 0;  
}

void dondur(int *dizi, int d)
{
    int gecici = dizi[0], modu, kalan;

    if (d > DIZIUZUNLUGU)
        d %= DIZIUZUNLUGU;
    if (d == 0 || d == DIZIUZUNLUGU)
        return;
        

    //fprintf(stdout, "d: %d\n\n", d);
    fprintf(stdout, "Onceki\t: ");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
        fprintf(stdout, "%d ", dizi[i]);
    fprintf(stdout, "\n");

    for (int p1 = 0, i = 0, p2 = 0; p1 < d && p2 < DIZIUZUNLUGU;)
    {
        modu = (i + d) % DIZIUZUNLUGU;
        kalan = dizi[modu];
        dizi[modu] = gecici;
        gecici = kalan;
        i = modu;
        if (i == p1)
        {
            i = ++p1;
            gecici = dizi[i];
        }
        ++p2;
        //fprintf(stdout, "|%d,%d,%d| ", p1, i, p2);
    }
    //fprintf(stdout, "\nkalan= %d gecici: %d\n", kalan,gecici);

    fprintf(stdout, "Son\t: ");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
        fprintf(stdout, "%d ", dizi[i]);
    fprintf(stdout, "\n");
}