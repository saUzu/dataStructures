/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 10/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 72rec_fibonacci.c -o 72rec_fibonacci
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint_least32_t fibonacci(uint_least32_t, uint_least32_t, uint_least32_t);

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

    fprintf(stdout, "sonuc: %" PRIuLEAST32 "\n", fibonacci(7, 0, 1));

    return EXIT_SUCCESS;
}

uint_least32_t fibonacci(uint_least32_t deger, uint_least32_t sonuc, uint_least32_t yardimci)
{
    uint_least32_t onceki = sonuc;
    if (deger == 0)
        return sonuc;
    sonuc += yardimci;
    yardimci = onceki;
    return fibonacci(--deger, sonuc, yardimci);
}