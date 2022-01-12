/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//  Tarih : 11/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 84srt_mergeSort.c -o 84srt_mergeSort
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define DIZI_UZUNLUGU 11

void yazdir(uint_least16_t *);
uint_least16_t *merge(uint_least16_t *, uint_least16_t, uint_least16_t *, uint_least16_t);
uint_least16_t *mergeSort(uint_least16_t *, uint_least16_t);

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        fprintf(stderr, "Lutfen herhangi bir parametre eklemeden calistirin.\n");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "\n-\tParametre sayisi: %d\n", argc);
    fprintf(stdout, "-\tProgramin adi: %s\n", argv[0]);
    fprintf(stdout, "-----------------------------------------------\n\n");

    uint_least16_t *dizi;
    if (!(dizi = calloc(DIZI_UZUNLUGU, sizeof *dizi)))
    {
        perror("dizi icin alan olusturulamadi.\tHata ");
        return EXIT_FAILURE;
    }

    dizi[0] = 99;
    dizi[1] = 44;
    dizi[2] = 6;
    dizi[3] = 2;
    dizi[4] = 1;
    dizi[5] = 5;
    dizi[6] = 63;
    dizi[7] = 87;
    dizi[8] = 283;
    dizi[9] = 4;
    dizi[10] = 0;

    yazdir(dizi);
    dizi = mergeSort(dizi, DIZI_UZUNLUGU);
    yazdir(dizi);

    free(dizi);
    return EXIT_SUCCESS;
}

void yazdir(uint_least16_t *dizi) 
{
    if (!dizi)
        return;
    fprintf(stdout, "Dizi: ");
    for (uint_least16_t i = 0; i < DIZI_UZUNLUGU; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n");
}

uint_least16_t *merge(uint_least16_t *dizi1, uint_least16_t u1, uint_least16_t *dizi2, uint_least16_t u2)
{
    uint_least16_t *dizi;
    if (!(dizi = calloc(u1 + u2, sizeof *dizi)))
    {
        perror("dizi icin alan bulunamadi.(merge)\tHata ");
        return NULL;
    }
    /* for (uint_least16_t i = 0; i < u1; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi1[i]);
    }
    fprintf(stdout, "\n");
    for (uint_least16_t i = 0; i < u2; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n"); */

    uint_least16_t sayac = 0;
    for (uint_least16_t i = 0, j = 0; sayac != (u1 + u2);)
    {
        if (i < u1 && j < u2)
        {   if (dizi1[i] < dizi2[j])
            {
                dizi[sayac++] = dizi1[i++];
            }
            else if (dizi1[i] > dizi2[j])
            {
                dizi[sayac++] = dizi2[j++];
            }
            else
            {
                dizi[sayac++] = dizi1[i++];
                dizi[sayac++] = dizi2[j++];
            }
        }
        else if (i < u1)
        {
            dizi[sayac++] = dizi1[i++];
        }
        else if (j < u2)
        {
            dizi[sayac++] = dizi2[j++];
        }
    }
    free(dizi1);
    free(dizi2);
    /* for (uint_least16_t i = 0; i < (u2 + u1); ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n\n"); */
    return dizi;
}

uint_least16_t *mergeSort(uint_least16_t *dizi, uint_least16_t uzunluk)
{
    if (!dizi)
        return NULL;
    if (uzunluk == 1)
    {
        return dizi;
    }

    /* for (uint_least16_t i = 0; i < uzunluk; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n"); */
    // fprintf(stdout, "\nu: %" PRIuLEAST16 ", o: %" PRIuLEAST16 "\n\n", uzunluk, dizi[0]);


    uint_least16_t u1 = ceil(uzunluk / 2.0);
    uint_least16_t *dizi1;
    if (!(dizi1 = calloc(u1, sizeof *dizi1)))
    {
        perror("dizi1 icin alan bulunamadi.(mergeSort)\t Hata ");
        return NULL;
    }
    for (uint_least16_t i = 0; i < u1; ++i)
    {
        dizi1[i] = dizi[i];
    }



    uint_least16_t u2 = uzunluk - u1;
    uint_least16_t *dizi2;
    if (!(dizi2 = calloc(u2, sizeof *dizi2)))
    {
        perror("dizi2 icin alan bulunamadi.(mergeSort)\t Hata ");
        free(dizi1);
        return NULL;
    }
    for (uint_least16_t i = u1, j = 0; j < u2 && i < uzunluk; ++i, ++j)
    {
        dizi2[j] = dizi[i];
    }
    
    /* fprintf(stdout, "\n1: ");
    for (uint_least16_t i = 0; i < u1; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi1[i]);
    }
    fprintf(stdout, "\n2: ");
    for (uint_least16_t i = 0; i < u2; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi2[i]);
    }
    fprintf(stdout, "\n"); */
    //return  mergeSort(dizi2, u2);

    return merge(mergeSort(dizi1, u1), u1, mergeSort(dizi2, u2), u2);
    // return dizi;
}