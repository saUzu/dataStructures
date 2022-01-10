/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 07/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 35q_queue.c -o 35q_queue
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//  -   Queue yapisini Singly linked list ile uygulaması.  
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
    struct Dugum *sonraki;
} DUGUM, *DUGUM_PTR;

typedef struct Sira{
    DUGUM_PTR basDugum;
    DUGUM_PTR kicDugum;
    uint_fast32_t uzunlugu;
} SIRA, *SIRA_PTR;

void kofla(SIRA_PTR *);
void yazdir(SIRA_PTR);
void enqueue(SIRA_PTR *, uint8_t *);
void dequeue(SIRA_PTR *);
DUGUM_PTR peek(SIRA_PTR);

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

    SIRA_PTR sira = calloc(1, sizeof *sira);
    if (!sira)
    {
        perror("sira icin alan olusturulamadi.\tHata ");
        return EXIT_FAILURE;
    }
    kofla(&sira);

    enqueue(&sira, (uint8_t *)"cicek");
    //dequeue(&sira);
    enqueue(&sira, (uint8_t *)"seyma");
    yazdir(sira);
    dequeue(&sira);
    enqueue(&sira, (uint8_t *)"eray");
    // fprintf(stdout, "sira->basDugum->deger: %s\n", sira->basDugum->deger);
    yazdir(sira);
    //dequeue(&sira);
    //dequeue(&sira);

    DUGUM_PTR ilkDugum = peek(sira);
    fprintf(stdout, "ilk dugum: %s\n", ilkDugum->deger);

    //free(sira->basDugum->deger);
    //free(sira->basDugum);
    //free(sira);

    kofla(&sira);
    free(sira);
    return EXIT_SUCCESS;
}

void kofla(SIRA_PTR *sira) 
{
    if (!(*sira)->basDugum)
    {
        fprintf(stderr, "sira kof zaten.(kofla)\n");
        return;
    }
    if ((*sira))
    {
        fprintf(stdout, "\n---------------------------------------------------------------------------\n");
        for (DUGUM_PTR geciciD = (*sira)->basDugum; geciciD != NULL; geciciD = (*sira)->basDugum)
        {
            (*sira)->basDugum = (*sira)->basDugum->sonraki;
            geciciD->sonraki = NULL;
            free(geciciD->deger);
            free(geciciD);
            fprintf(stdout, "kof - ");
        }
        fprintf(stdout, "\t## -> sira koflandi!");
        fprintf(stdout, "\n");
    }
}

void yazdir(SIRA_PTR sira) 
{
    if (!sira->basDugum)
    {
        fprintf(stderr, "sira'nin ici kof.(yazdir)\n");
        return;
    }   else    {
        fprintf(stdout, "sira'nin icerigi: ");
        for (DUGUM_PTR geciciD = sira->basDugum; geciciD != NULL; geciciD = geciciD->sonraki)
            fprintf(stdout, "%s - ", geciciD->deger);
        fprintf(stdout, "\n");
    }
}

void enqueue(SIRA_PTR *sira, uint8_t *deger) 
{
    //fprintf(stdout, "%s\n", deger);
    if (!(*sira))
    {
        fprintf(stderr, "sira kof.(enqueue)\n");
        return;
    }

    DUGUM_PTR eklenecekD = calloc(1, sizeof *eklenecekD);
    if (!eklenecekD)
    {
        perror("(enqueue)eklenecekD icin alan acilamadi.\tHata ");
        return;
    }
    eklenecekD->deger = calloc(strlen((char *)deger), sizeof eklenecekD->deger);
    if (!eklenecekD->deger)
    {
        perror("(enqueue)eklenecekYazi icin alan acilamadi.\tHata ");
        free(eklenecekD);
        return;
    }
    //fprintf(stdout, "boyut: %ld\n", sizeof eklenecekD->deger);
    memmove(eklenecekD->deger, deger, strlen((char *)deger));
    //fprintf(stdout, ".deger: %s\n", eklenecekD->deger);
    if (!(*sira)->basDugum && !(*sira)->kicDugum)
    {
        (*sira)->basDugum = eklenecekD;
        (*sira)->kicDugum = eklenecekD;
        //fprintf(stdout, "bas ve kic dugum kof\n");
        //free(eklenecekD->deger);
        //free(eklenecekD);
        return;
    }   else    {
        (*sira)->kicDugum->sonraki = eklenecekD;
        (*sira)->kicDugum = eklenecekD;
    }
}

void dequeue(SIRA_PTR *sira) 
{
    if (!(*sira)->basDugum)
    {
        fprintf(stderr, "sira zaten kof.(dequeue)\n");
        return;
    }
    DUGUM_PTR geciciD = (*sira)->basDugum;
    if ((*sira)->basDugum == (*sira)->kicDugum)
    {
        (*sira)->basDugum = NULL;
        (*sira)->kicDugum = NULL;
        }   else    {
        (*sira)->basDugum = (*sira)->basDugum->sonraki;
    }
    geciciD->sonraki = NULL;
    free(geciciD->deger);
    free(geciciD);
    return;
}

DUGUM_PTR peek(SIRA_PTR sira) 
{
    return sira->basDugum;
}
