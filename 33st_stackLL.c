/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 29/12/2021
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 33st_stackLL.c -o 33st_stackLL
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//  -   stack yapısını linked list ile uygulama.
//  -   push, pop ve peek işlevlikleri ile işlemler yapılabilir.
//  -   degere veya sıraya göre arama yapılabilinir. O(n) zaman karmaşıklığında olacaktır.
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

typedef struct Dugum{
    uint8_t *deger;
    struct Dugum *siradaki;
} DUGUM, *DUGUM_PTR;

void kofla(DUGUM_PTR *);
void yazdir(DUGUM_PTR);
void push(DUGUM_PTR *, uint8_t *);
void pop(DUGUM_PTR *);
DUGUM_PTR peek(DUGUM_PTR *);

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

    DUGUM_PTR basDugum = NULL;
    // ------- HATA DENETİMİ (HD)
    kofla(&basDugum);
    yazdir(basDugum);
    push(&basDugum, (uint8_t *)"");
    push(&basDugum, (uint8_t *)" ");
    // ------- HD BİTTİ
    fprintf(stdout, "\n");

    push(&basDugum, (uint8_t *)"igdir");
    push(&basDugum, (uint8_t *)"mersin");
    push(&basDugum, (uint8_t *)"ankara");
    push(&basDugum, (uint8_t *)"cankiri");
    yazdir(basDugum);
    pop(&basDugum);
    yazdir(basDugum);

    DUGUM_PTR getirilen = peek(&basDugum);
    fprintf(stdout, "getirilen oge: %s\n", getirilen->deger);
    if (getirilen)
        getirilen = NULL;

    kofla(&basDugum);
    return EXIT_SUCCESS;
}

void kofla(DUGUM_PTR *dugum) 
{
    if (!(*dugum))
    {
        fprintf(stderr, " > stack yok ortada la!(kofla)\n");
        return;
    }
    if((*dugum))
    {
        fprintf(stdout, "\nstack koflaniyor...\n");
        for (DUGUM_PTR geciciD = (*dugum); geciciD != NULL; geciciD = (*dugum))
        {
            (*dugum) = (*dugum)->siradaki;
            geciciD->siradaki = NULL;
            free(geciciD->deger);
            free(geciciD);
            fprintf(stdout, "kof - ");
        }
        fprintf(stdout, "\nstack koflandi.\n");
    }
    return;
}

void yazdir(DUGUM_PTR dugum) 
{
    if (!dugum)
    {
        fprintf(stderr, " > stack'te yazdirilacak bir sey yok!(yazdir)\n");
        return;
    }
    if (dugum)
    {
        fprintf(stdout, "stack ogeleri:\t");
        for (DUGUM_PTR yazilacak = dugum; yazilacak != NULL; yazilacak = yazilacak->siradaki)
            fprintf(stdout, "(%s) - ", yazilacak->deger);
        fprintf(stdout, "\n");
        return;
    }
}

void push(DUGUM_PTR *basDugum, uint8_t *deger)
{
    if (memcmp(deger, "", strlen((char *)deger)) == 0 || memcmp(deger, " ", strlen((char *)deger)) == 0)
    {
        fprintf(stderr, " > girilen deger bos.(push)\n");
        return;
    }
    if (!(*basDugum))
    {
        (*basDugum) = calloc(1, sizeof *(*basDugum));
        if (!(*basDugum))
        {
            perror("basDugum icin alan acilamadi.(push) - HATA ");
            return;
        }
        (*basDugum)->deger = calloc(strlen((char *)deger), sizeof *((*basDugum)->deger));
        if (!((*basDugum)->deger))
        {
            perror("basDugum->deger icin alan acilamadi.(push) - HATA \n");
            free((*basDugum));
            return;
        }
        memcpy((*basDugum)->deger, deger, strlen((char *)deger));
        // fprintf(stdout, "%ld, %ld\n", sizeof(*basDugum)->deger, sizeof *((*basDugum)->deger));
        // free((*basDugum)->deger);
        // free((*basDugum));
        return;
    }
    else if ((*basDugum))
    {
        DUGUM_PTR eklenecek;
        if (!(eklenecek = calloc(1, sizeof *eklenecek)))
        {
            perror("eklenecek icin yer acilamadi.(push) - HATA ");
            return;
        }
        if (!(eklenecek->deger = calloc(strlen((char *)deger), sizeof *(eklenecek->deger))))
        {
            perror("eklenecek->deger icin yer acilamadi.(push) - HATA ");
            free(eklenecek);
            return;
        }
        // fprintf(stdout, "%ld, %ld\n", sizeof eklenecek->deger, sizeof *(eklenecek->deger));
        memcpy(eklenecek->deger, deger, strlen((char *)deger));
        eklenecek->siradaki = (*basDugum);
        (*basDugum) = eklenecek;
        // free(eklenecek->deger);
        // free(eklenecek);
        return;
    }
    fprintf(stderr, "buraya hic gelmemeliydi. Bu nasil hata lan!(push)\n");
    return;
}

void pop(DUGUM_PTR *basDugum)
{
    if (!(*basDugum))
    {
        fprintf(stderr, " > stack kof neyi popluyon?(pop)\n");
        return;
    }
    if ((*basDugum))
    {
        DUGUM_PTR silinecek = (*basDugum);
        (*basDugum) = (*basDugum)->siradaki;
        silinecek->siradaki = NULL;
        free(silinecek->deger);
        free(silinecek);
        return;
    }
    fprintf(stderr, "buraya hic gelmemeliydi. Bu nasil hata lan!(pop)\n");
    return;
}

DUGUM_PTR peek(DUGUM_PTR *basDugum) 
{

    if (!(*basDugum))
    {
        fprintf(stderr, " > stack kof neyi popluyon?(peek)\n");
        return NULL;
    }
    if ((*basDugum))
    {
        return (*basDugum);
    }
    fprintf(stderr, "buraya hic gelmemeliydi. Bu nasil hata lan!(peek)\n");
    return NULL;
}