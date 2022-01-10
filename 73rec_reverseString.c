/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 10/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 73rec_reverseString.c -o 73rec_reverseString
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//  ->  Burada bir hata yapmıştım. calloc kullanmadan doğrudan işlevliği çağırırken değeri atadım ve aynı işlevlik çalışmadı.
//      Bu bilgi burada kalsın ne olur ne olmaz.
//
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

uint8_t *tersle(uint8_t *, uint_least32_t);

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

    uint8_t *yazi;
    if (!(yazi = calloc(14, sizeof *yazi)))
    {
        perror("yazi icin alan olusturulamadi.\tHata ");
        return EXIT_FAILURE;
    }

    memmove(yazi, "yok daha neler", 14);

    fprintf(stdout, "tersi: %s\n", tersle(yazi, 0));

    free(yazi);
    return EXIT_SUCCESS;
}

uint8_t *tersle(uint8_t *yazi, uint_least32_t t)
{
    if (t >= (strlen((char *)yazi) / 2))
        return yazi;
    uint8_t gecici = yazi[strlen((char *)yazi) - t - 1];
    yazi[strlen((char *)yazi) - t - 1] = yazi[t];
    yazi[t] = gecici;
    return tersle(yazi, ++t);
}