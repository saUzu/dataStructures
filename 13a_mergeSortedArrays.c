/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 2/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 13a_mergeSortedArrays.c -o 13a_mergeSortedArrays
//      gcc 9.1.0
//
//      - Hali hazırda küçükten büyüğe doğru sıralanmış iki diziyi tek bir diziye 
//          küçükten büyüğe olacak şekilde birleştiriyor.
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DIZIBIR 7
#define DIZIIKI 4

typedef struct BirlesmisDizi
{
    size_t uzunluk1;
    size_t uzunluk2;
    int *birlesmisDizi;
} BIRLESMIS_DIZI, *BD_PTR;

void birlestir(BD_PTR, int *, int *);
void diziYazdir(int *, char *, int);

int main(int argc, char **argv)
{
    //  Dizilerin içeriğinin bir önemi yok.
    //  burada rastgele atamalar yapıldı ancak küçükten büyüğe olacak şekilde olmasına dikkat edin.
    int *dizi1 = malloc(sizeof(int) * DIZIBIR);
    //int *dizi1 = malloc(-1);
    int *dizi2 = malloc(sizeof(int) * DIZIIKI);
    //int *dizi2 = malloc(-1);

    if (dizi1 == NULL)
    {
        perror("dizi1 icin malloc'ta hata oldu.\nHata\t");
        goto cikisA;
    }
    else if (dizi2 == NULL)
    {
        perror("dizi2 icin malloc'ta hata oldu. Hata\t");
        goto cikisA;
    }
    

    int toplamUzunluk = DIZIBIR + DIZIIKI;
    fprintf(stdout, "toplam uzunluk: %d\n", toplamUzunluk);

    dizi1[0] = 0;
    dizi1[1] = 3;
    dizi1[2] = 4;
    dizi1[3] = 31;
    dizi1[4] = 54;
    dizi1[5] = 67;
    dizi1[6] = 100;

    dizi2[0] = 4;
    dizi2[1] = 6;
    dizi2[2] = 30;
    dizi2[3] = 33;
    //  dizi atamaları bitti


    BD_PTR bd = malloc(sizeof bd);
    //BD_PTR bd = malloc(-1);
    if (bd == NULL)
    {
        perror("bd icin malloc'ta hata oldu.\nHata\t");
        goto cikisC;
    }
    bd->birlesmisDizi = malloc(sizeof(int) * toplamUzunluk);
    //bd->birlesmisDizi = malloc(-1);
    
    if (bd->birlesmisDizi == NULL)
    {
        perror("bd->birlesmisDizi icin malloc'ta hata oldu.\nHata\t");
        goto cikisB;
    }
    bd->uzunluk1 = DIZIBIR;
    bd->uzunluk2 = DIZIIKI;
    fprintf(stdout, "bd : %d | bd[0] : %d\n", sizeof bd->birlesmisDizi, sizeof bd->birlesmisDizi[0]);




    fprintf(stdout, "\n");
    diziYazdir(dizi1, "dizi1", DIZIBIR);
    diziYazdir(dizi2, "dizi2", DIZIIKI);
    birlestir(bd, dizi1, dizi2);
    fprintf(stdout, "\n");



    fprintf(stdout, "birlestirdikten sonra: ");
    for (int i = 0; i < (bd->uzunluk1 + bd->uzunluk2); i++)
    {
        fprintf(stdout, "%d ", bd->birlesmisDizi[i]);    
    }
    fprintf(stdout, "\n");

cikisB:
    free(bd->birlesmisDizi);
    bd->birlesmisDizi = NULL;
    if (bd->birlesmisDizi == NULL)
        fprintf(stdout, "bd->birlesmisDizi KOF\n");
cikisC:
    free(bd);
    bd = NULL;
    if (bd == NULL)
        fprintf(stdout, "bd KOF\n");
cikisA:
    free(dizi1);
    dizi1 = NULL;
    if (dizi1 == NULL)
        fprintf(stdout, "dizi1 KOF\n");
    free(dizi2);
    dizi2 = NULL;
    if (dizi2 == NULL)
        fprintf(stdout, "dizi2 KOF\n");
    return 0;
}


/*  - Dizileri sondan başa doğru olacak şekilde birleştiriyor. */
void birlestir(BD_PTR bd, int *dizi1, int *dizi2)
{
    int i = bd->uzunluk1 - 1, k = bd->uzunluk2 - 1, t = bd->uzunluk1 + bd->uzunluk2 - 1;
    while (1)
    {
        fprintf(stdout, "i:%d, k:%d, t:%d\n", i, k, t);
        if (i > -1 && k > -1 && t > -1)
        {
            if (dizi1[i] > dizi2[k])
            {
                bd->birlesmisDizi[t--] = dizi1[i--];
            }
            else if (dizi2[k] > dizi1[i])
            {
                bd->birlesmisDizi[t--] = dizi2[k--];
            }
            else if (dizi1[i] == dizi2[k])
            {
                bd->birlesmisDizi[t--] = dizi1[i--];
                bd->birlesmisDizi[t--] = dizi2[k--];
            }
            else
            {
                fprintf(stdout, "\n\n\t\tBilinmeyen bir hata olustu!\n\n");
                return;
            }
        }
        else if (i > -1 && t > -1)
        {
            bd->birlesmisDizi[t--] = dizi1[i--];
        }
        else if (k > -1 && t > -1)
        {
            bd->birlesmisDizi[t--] = dizi2[k--];
        }
        else
            break;
    }
}

void diziYazdir(int *dizi, char *isim, int uzunluk)
{
    fprintf(stdout, "%s\t: ", isim);
    for (int i = 0; i < uzunluk; i++)
    {
        fprintf(stdout, "%d ", dizi[i]);    
    }
    fprintf(stdout, "\n");
}