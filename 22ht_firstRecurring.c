/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//      Tarih : 14/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 22ht_firstRecurring.c -o 22ht_firstRecurring
//      gcc 9.1.0
//
//      -   hash işlemini sadece gelen sayinin 1000'li modunu döndürüyor.
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct Veri{
    int veri;
    int anahtar;
} VERI, *VERI_PTR;

int hashIslemi(int);
void tekrariBul(int *dizi, int uzunluk);

int main(int argc,char **argv)
{
    //int dizi[] = {2, 5, 1, 2, 3, 5, 1, 2, 4};
    //int dizi[] = {2, 1, 1, 2, 3, 5, 1, 2, 4};
    int dizi[] = {2, 3, 4, 5};
    int uzunluk = sizeof dizi / sizeof *dizi;
    //fprintf(stdout, "%d\n", uzunluk);

    tekrariBul(dizi, uzunluk);

    return 0;
}

int hashIslemi(int anahtar)
{
    if ((anahtar %= 1000) > -1 || anahtar < 1000)
        return anahtar;
    else
        return -1;
}

void tekrariBul(int *dizi, int uzunluk)
{
    VERI_PTR hashDizisi = calloc(1000, sizeof *hashDizisi);
    //fprintf(stdout, "a: %d\n", hashDizisi[874].veri);
    for (int i = 0, hashli; i < uzunluk; i++)
    {
        hashli = hashIslemi(dizi[i]);
        if (hashDizisi[hashli].veri != dizi[i] && hashDizisi[hashli].anahtar != hashli)
        {
            hashDizisi[hashli].anahtar = hashli;
            hashDizisi[hashli].veri = dizi[i];
        }
        else
        {
            fprintf(stderr, "%d sayisi tekrar eden sayidir! Sira: %d\n", dizi[i], i);
            goto cikis;
        }
        
    }
    fprintf(stdout, "oyle bir sayi bulunamadi.\n");

cikis:
    free(hashDizisi);
    hashDizisi = NULL;
    if (!hashDizisi)
        fprintf(stdout, "hashDizisi koflandi!\n");
}