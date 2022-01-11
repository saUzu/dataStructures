/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//  Tarih : 11/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 83srt_insertionSort.c -o 83srt_insertionSort
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

#define DIZI_UZUNLUGU 11

void yazdir(uint_least16_t *);
void insertionSort(uint_least16_t *);

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
    insertionSort(dizi);
    yazdir(dizi);

    free(dizi);
    return EXIT_SUCCESS;
}

void yazdir(uint_least16_t *dizi) 
{
    fprintf(stdout, "Dizi: ");
    for (uint_least16_t i = 0; i < DIZI_UZUNLUGU; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n");
}

void insertionSort(uint_least16_t *dizi)
{
    uint_least16_t baslangic = 0, bitis = 0, sayac = 1;
    do {
        for (uint_least16_t i = baslangic; i <= bitis; ++i)
        {
            if (dizi[sayac] < dizi[i])
            {
                uint_least16_t gecici = dizi[i];
                dizi[i] = dizi[sayac];
                dizi[sayac] = gecici;
            }
        }
        bitis = sayac++;
    } while (bitis < DIZI_UZUNLUGU - 1);
}