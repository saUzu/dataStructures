/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 06/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 34st_stackArray.c -o 34st_stackArray
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//  -   stack yapısını array ile uygulama.
//  -   push, pop ve peek işlevlikleri ile işlemler yapılabilir.
//  -   O(1) zaman karmaşıklığına sahiptir.
//
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>


typedef struct Stack{
    uint8_t **yiginDizi;
    int_fast32_t yiginUzunlugu;
    uint_fast32_t boyut;
} STACK, *STACK_PTR;

void kofla(STACK_PTR *);
void yazdir(STACK_PTR);
void push(STACK_PTR *, uint8_t *);
void pop(STACK_PTR *);
uint8_t *peek(STACK_PTR);

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

    STACK_PTR yigin = NULL;
    push(&yigin, (uint8_t *)"cicek");
    push(&yigin, (uint8_t *)"seyma");
    push(&yigin, (uint8_t *)"eray");
    push(&yigin, (uint8_t *)"gul");
    yazdir(yigin);

    pop(&yigin);
    yazdir(yigin);

    uint8_t *alinan = peek(yigin);
    fprintf(stdout, "alinan: %s\n", alinan);

    //fprintf(stdout, "%" PRIuFAST32 "\n", yigin->boyut);
    // fprintf(stdout, "-- %s --\n", yigin->yiginDizi[0]);

    //free(yigin->yiginDizi[0]);
    //free(yigin->yiginDizi);
    //free(yigin);
    
    kofla(&yigin);
    return EXIT_SUCCESS;
}

void kofla(STACK_PTR *yigin) 
{
    if (!(*yigin))
    {
        fprintf(stderr, "yigin zaten kof.(kofla)\n");
        return;
    }
    if ((*yigin))
    {
        fprintf(stdout, "\n--------------------------------------------------------------------------------------\n");
        fprintf(stdout, "yigin->yiginDizi koflaniyor.... %" PRIdFAST32 "\n", (*yigin)->yiginUzunlugu);
        for (int_fast32_t i = ((*yigin)->yiginUzunlugu - 1); i >= 0; --i)
        {
            free((*yigin)->yiginDizi[i]);
            fprintf(stdout, "kof - ");
        }
        free((*yigin)->yiginDizi);
        fprintf(stdout, "\nyigin->yiginDizi koflandi, ");
        free((*yigin));
        fprintf(stdout, "yigin koflandi.\n");
        return;
    }
}

void yazdir(STACK_PTR yigin)
{
    if (!yigin)
    {
        fprintf(stderr, "yigin bos yazdirilamaz.(yazdir)\n");
        return;
    }
    if (yigin)
    {
        fprintf(stdout, "yiginin icerigi: ");
        for (int_fast32_t i = 0; i < yigin->yiginUzunlugu - 1; ++i)
            fprintf(stdout, "%s - ", yigin->yiginDizi[i]);
        fprintf(stdout, "\n");
    }
}

void push(STACK_PTR *yigin, uint8_t *deger)
{
    if (memcmp(deger, "", strlen((char *)deger)) == 0 || memcmp(deger, " ", strlen((char *)deger) == 0))
    {
        fprintf(stderr, "degeri bos gonderdiniz.(push)\n");
        return;
    }
    if (!(*yigin))
    {
        (*yigin) = calloc(1, sizeof *(*yigin));
        if (!(*yigin))
        {
            perror("yigin icin alan olusturulamadi.(push)\tHata ");
            return;
        }
        (*yigin)->yiginDizi = calloc(1, sizeof *((*yigin)->yiginDizi));
        if (!((*yigin)->yiginDizi))
        {
            perror("yigin->yigizDizi icin alan acilamadi.(push)\tHata ");
            free((*yigin));
            return;
        }
        (*yigin)->yiginUzunlugu = 1;
        (*yigin)->boyut = 0;
    }
    if ((*yigin))
    {
        uint8_t *geciciDeger = calloc(strlen((char *)deger) + 1, sizeof *geciciDeger);
        if (!geciciDeger)
        {
            perror("yigin->yiginDizi[] icin alan olusturulamadi.(push)\tHata ");
            return;
        }
        memmove(geciciDeger, deger, strlen((char *)deger));
        uint8_t **diziP = realloc((*yigin)->yiginDizi, ((*yigin)->yiginUzunlugu + 1) * sizeof *((*yigin)->yiginDizi));
        if (!diziP)
        {
            fprintf(stderr, "yigin->dizi icin realloc ile alan acilamadi.(push)\n");
            return;
        }   else    (*yigin)->yiginDizi = diziP;
        (*yigin)->yiginDizi[((*yigin)->yiginUzunlugu) - 1] = geciciDeger;
        (*yigin)->yiginUzunlugu++;
        (*yigin)->boyut += strlen((char *)deger);
        return;
    }
}

void pop(STACK_PTR *yigin) 
{
    if (!(*yigin))
    {
        fprintf(stderr, "yigin zaten kof.(pop)\n");
        return;
    }
    if ((*yigin))
    {
        free((*yigin)->yiginDizi[(*yigin)->yiginUzunlugu - 1]);
        (*yigin)->yiginUzunlugu--;
        (*yigin)->yiginDizi[(*yigin)->yiginUzunlugu - 1] = NULL;

        return;
    }
}

uint8_t *peek(STACK_PTR yigin)
{
    return yigin->yiginDizi[yigin->yiginUzunlugu - 2];
}