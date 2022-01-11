/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//  Tarih : 11/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 82srt_selectionSort.c -o 82srt_selectionSort
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
void selectionSort(uint_least16_t *);

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
    selectionSort(dizi);
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

void selectionSort(uint_least16_t *dizi)
{
    uint_least16_t enKucuk, enKucukSira = 0, ilerleme = 0;
    do
    {
        enKucuk = dizi[ilerleme];
        for (uint16_t i = ilerleme; i < DIZI_UZUNLUGU; ++i)
        {
            if (dizi[i] < enKucuk)
            {
                enKucuk = dizi[i];
                enKucukSira = i;
            }
        }
        //fprintf(stdout, "%" PRIuLEAST16 " - %" PRIuLEAST16 " - %" PRIuLEAST16 "\n", enKucuk, enKucukSira, ilerleme);
        uint_least16_t gecici = dizi[ilerleme];
        dizi[ilerleme] = enKucuk;
        dizi[enKucukSira] = gecici;
        // fprintf(stdout, " - %" PRIuLEAST16 "", ilerleme);
        //return;
    } while (++ilerleme < DIZI_UZUNLUGU);
}