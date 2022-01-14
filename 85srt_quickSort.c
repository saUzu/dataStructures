/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//  Tarih : 14/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 85srt_quickSort.c -o 85srt_quickSort
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
void quickSort(uint_least16_t *, uint_least16_t/* , uint_least16_t, uint_least16_t */);

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
    quickSort(dizi, DIZI_UZUNLUGU/* , 0, DIZI_UZUNLUGU */);
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

void quickSort(uint_least16_t *dizi, uint_least16_t uzunluk/* , uint_least16_t baslangic, uint_least16_t bitis */)
{
    if (uzunluk == 0)
        return;
    uint_least16_t pivot = uzunluk - 1;
    for (uint_least16_t i = 0; i < pivot;)
    {
        if (dizi[i] > dizi[pivot])
        {
            uint_least16_t gecici = dizi[pivot - 1];
            dizi[pivot - 1] = dizi[i];
            dizi[i] = gecici;
            gecici = dizi[pivot];
            dizi[pivot] = dizi[pivot - 1];
            dizi[pivot - 1] = gecici;
            --pivot;
            //fprintf(stdout, "p: %" PRIuLEAST16 ", u: %" PRIdLEAST16 "\n", pivot, uzunluk);
        }
        else
            ++i;
    }
    //fprintf(stdout, "pS: %" PRIuLEAST16 ", uS: %" PRIdLEAST16 "\n\n", pivot, uzunluk );
    //return;
    /* fprintf(stdout, "d -> ");
    for (uint_least16_t i = 0; i < uzunluk; ++i)
    {
        fprintf(stdout, "%" PRIdLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n"); */
    quickSort(&dizi[pivot + 1], uzunluk - 1 - pivot);
    quickSort(&dizi[0], pivot);
    // quickSort(&dizi[baslangic], pivot - baslangic, baslangic, pivot - 1);
}