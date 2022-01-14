/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 14/01/2022
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 91srch_bfs.c -o 91srch_bfs
//
//  Fedora 35
//  gcc (GCC) 11.2.1
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

typedef struct Oge{
    uint_least16_t deger;
    struct Oge *sag;
    struct Oge *sol;
} OGE, *OGE_PTR;

typedef struct{
    OGE_PTR kok;
} BST, *BST_PTR;

BST_PTR ilkAtama(uint_least16_t);
void kofla(OGE_PTR);
OGE_PTR ogeOlustur(uint_least16_t);
void ekle(OGE_PTR, uint_least16_t);
void bfsYazdir(OGE_PTR, uint_least16_t);
void bfs(OGE_PTR, uint_least16_t);

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

    BST_PTR bst = ilkAtama(5);
    ekle(bst->kok, 8);
    ekle(bst->kok, 6);
    ekle(bst->kok, 2);
    ekle(bst->kok, 0);
    ekle(bst->kok, 4);
    ekle(bst->kok, 9);
    ekle(bst->kok, 7);
    ekle(bst->kok, 3);
    ekle(bst->kok, 10);
    ekle(bst->kok, 1);

    bfsYazdir(bst->kok, 4);

    kofla(bst->kok);
    free(bst);
    fprintf(stdout, "\n");
    return EXIT_SUCCESS;
}

BST_PTR ilkAtama(uint_least16_t deger) 
{
    BST_PTR bst;
    if (!(bst = calloc(1, sizeof *bst)))
    {
        perror("bst icin yeterli alan bulunamadi.(ilkAtama)\tHata ");
        return NULL;
    }
    OGE_PTR oge;
    if (!(oge = calloc(1, sizeof *oge)))
    {
        perror("oge icin alan bulunamadi.(ilkAtama)\tHata ");
        free(bst);
        return NULL;
    }
    oge->deger = deger;
    oge->sag = NULL;
    oge->sol = NULL;
    bst->kok = oge;
    return bst;
}

void kofla(OGE_PTR oge) 
{
    if (oge->sag)
    {
        kofla(oge->sag);
        oge->sag = NULL;
    }
    if (oge->sol)
    {
        kofla(oge->sol);
        oge->sol = NULL;
    }
    if (!oge->sag && !oge->sol)
    {
        fprintf(stdout, "(%" PRIuLEAST16 ")kof - ", oge->deger);
        free(oge);
    }
}

OGE_PTR ogeOlustur(uint_least16_t deger) 
{
    OGE_PTR yeniOge;
    if (!(yeniOge = calloc(1, sizeof *yeniOge)))
    {
        perror("yeniOge icin alan bulunamadi.(ogeOlustur)\tHata ");
        return NULL;
    }
    yeniOge->deger = deger;
    yeniOge->sag = NULL;
    yeniOge->sol = NULL;
    return yeniOge;
}

void ekle(OGE_PTR oge, uint_least16_t deger)
{
    if (oge->deger < deger)
    {   if (oge->sag == NULL)
        {
            oge->sag = ogeOlustur(deger);
            return;
        }   else    ekle(oge->sag, deger);
        return;
    }
    else if (oge->deger > deger)
    {   if (oge->sol == NULL)
        {
            oge->sol = ogeOlustur(deger);
            return;
        }   else    ekle(oge->sol, deger);
        return;
    }
    else
    {
        fprintf(stderr, "Boyle bir oge zaten var.(ekle)\n");
        return;
    }
}

void bfsYazdir(OGE_PTR oge, uint_least16_t seviye) 
{
    if (!oge)
        return;
    for (uint_least16_t i = 1; i <= seviye; ++i)
    {
        //fprintf(stdout, "%" PRIdLEAST16 "\n", i);
        bfs(oge, i);
    }
    fprintf(stdout, "\n");
}

void bfs(OGE_PTR oge, uint_least16_t seviye)
{
    if (!oge)
        return;
    if (seviye == 1)
    {
        fprintf(stdout, "%" PRIdLEAST16 " - ", oge->deger);
        return;
    }
    else if(seviye>1)
    {
        if (oge->sol)
            bfs(oge->sol, seviye - 1);
        if (oge->sag)
            bfs(oge->sag, seviye - 1);
    }
}