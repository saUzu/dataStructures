/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 6/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_3_moveZeroes.c -o 14a_3_moveZeroes
//      gcc 9.1.0
//
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//      - algoritmasını kendim yazdım, bir yerden alınmamıştır.
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DIZIUZUNLUGU 9

void sifirKaydir(int *);

int main(int argc, char **argv)
{
    //int *dizi = malloc(-1);
    int *dizi = malloc(sizeof(int) * DIZIUZUNLUGU);
    if (dizi == NULL)
    {
        perror("dizi icin malloc olusturulamadi!\nHata");
        goto cikis1;
    }
    dizi[0] = 0;
    dizi[1] = 1;
    dizi[2] = 0;
    dizi[3] = 3;
    dizi[4] = 12;
    dizi[5] = 0;
    dizi[6] = 0;
    dizi[7] = 4;
    dizi[8] = 7;

    fprintf(stdout, "Dizi ogeleri\t: ");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        fprintf(stdout, "%d ", dizi[i]);
    }
    fprintf(stdout, "\n");

    sifirKaydir(dizi);

    fprintf(stdout, "dizili hali\t: ");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        fprintf(stdout, "%d ", dizi[i]);
    }
    fprintf(stdout, "\n");


cikis1:
    free(dizi);
    dizi = NULL;
    if (dizi == NULL)
        fprintf(stdout, "dizi KOF\n");
    return 0;
}

void sifirKaydir(int *dizi) 
{
    int gecici, s = 0, i = 0;

    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        if (dizi[i] == 0 && dizi[s] != 0)
            s = i;
        else if(dizi[i]!=0)
        {
            gecici = dizi[s];
            dizi[s++] = dizi[i];
            dizi[i] = gecici;
        }
    }
}