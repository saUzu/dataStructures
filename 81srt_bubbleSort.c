/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//  Tarih : 11/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 81srt_bubbleSort.c -o 81srt_bubbleSort
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

void yazdir(uint_least16_t *);
void bubbleSort(uint_least16_t *);

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
    if (!(dizi = calloc(11, sizeof *dizi)))
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
    bubbleSort(dizi);
    yazdir(dizi);

    free(dizi);
    return EXIT_SUCCESS;
}

void yazdir(uint_least16_t *dizi) 
{
    fprintf(stdout, "Dizi: ");
    for (uint_least16_t i = 0; i < 11; ++i)
    {
        fprintf(stdout, "%" PRIuLEAST16 " - ", dizi[i]);
    }
    fprintf(stdout, "\n");
}

void bubbleSort(uint_least16_t *dizi) 
{
    uint_least8_t sayac;

    do {
        sayac = 0;
        for (uint16_t i = 0; i < 10; ++i)
        {
            if (dizi[i] > dizi[i + 1])
            {
                uint_least16_t gecici = dizi[i];
                dizi[i] = dizi[i + 1];
                dizi[i + 1] = gecici;
                ++sayac;
            }
        }
    } while (sayac);
}