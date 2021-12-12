/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//      Tarih : 29/11/2021
//      Yazan : saUzu
//      Derlemek için : gcc 12a_reverseString.c -o 12a_reverseString
//      gcc 9.1.0
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct KullaniciGirisi
{
    size_t uzunlugu;
    char *kullaniciGirisi;
} KULLANICI_GIRISI, *KG_PTR;

int girisAl(KG_PTR);
void tersiniAl(KG_PTR);

int main(int argc, char **argv)
{
    int hata;
    KG_PTR kg = malloc(sizeof kg);
    if (kg == NULL)
    {
        perror("kg KOF cikti!\nHata\t");
        goto cikis1;
    }
    kg->kullaniciGirisi = malloc(sizeof kg->kullaniciGirisi * kg->uzunlugu);
    if (kg->kullaniciGirisi == NULL)
    {
        perror("kg->kullaniciGirisi KOF cikti!\nHata\t");
        goto cikis2;
    }

    kg->uzunlugu = 1024;

    hata = girisAl(kg);
    switch (hata)
    {
    case 0:
        //fprintf(stdout, "cumleyi alma ve ona gore MA olusturma basarili!!\n");
        break;
    case 1:
        fprintf(stdout, "MA'da hata oldu! hata\t: %d \n", hata);
        goto cikis2;

    default:
        fprintf(stdout, "Bilinmeyen bir hata oldu! hata\t: %d \n", hata);
        goto cikis2;
    }
    tersiniAl(kg);
    fprintf(stdout, "%s\n\n", kg->kullaniciGirisi, kg->uzunlugu);

cikis2:
    free(kg->kullaniciGirisi);
    kg->kullaniciGirisi = NULL;
    if (kg->kullaniciGirisi == NULL)
        fprintf(stdout, "kg->kullaniciGirisi KOF\n");
cikis1:
    free(kg);
    kg = NULL;
    if (kg == NULL)
        fprintf(stdout, "kg KOF\n");
    return 0;
}

int girisAl(KG_PTR kg)
{
    int giris;
    int sayac = 0;
    void *adresPTR;
    while (((giris = fgetc(stdin)) != EOF) && (giris != '\n') && sayac < kg->uzunlugu)
    {
        kg->kullaniciGirisi[sayac++] = giris;
    }
    kg->kullaniciGirisi[sayac] = '\0';

    adresPTR = kg->kullaniciGirisi;

    kg->kullaniciGirisi = realloc(kg->kullaniciGirisi, sizeof kg->kullaniciGirisi * sayac);
    if (adresPTR != kg->kullaniciGirisi)
        return 1;
    kg->uzunlugu = sayac;
    return 0;
}

void tersiniAl(KG_PTR kg)
{
    int gecici = 0;
    for (int i = 0, k = kg->uzunlugu - 1; i < k; i++, k--)
    {
        gecici = kg->kullaniciGirisi[i];
        kg->kullaniciGirisi[i] = kg->kullaniciGirisi[k];
        kg->kullaniciGirisi[k] = gecici;
    }
}