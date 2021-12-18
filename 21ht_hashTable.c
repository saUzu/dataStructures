/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//      Tarih : 13/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 21ht_hashTable.c -o 21ht_hashTable
//      gcc 9.1.0
//
//      -   hash işlemini çok basitte tuttum. ilk 2 harfin int olarak karşılığını toplayıp 100'e modluyor,
//          elde kalan sayı ise indexini belirtiyor. 0'dan küçük veya 100den büyükse hata olarak döndürüp bitiriyor.
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct Veri{
    int veri;
    char *anahtar;
} VERI, *VERI_PTR;

void ogeYazdir(VERI_PTR);
int hashIslemi(char *);
void ekle(VERI_PTR, char *, int);
void silme(VERI_PTR, char *);
void ogeGetir(VERI_PTR, char *);

int main(int argc,char **argv)
{
    VERI_PTR veriler = calloc(100, sizeof *veriler);

    ekle(veriler, "ali", 1000);
    ekle(veriler, "aLa", 2000);
    ekle(veriler, "mehmet", 35);
    ekle(veriler, "eren", 33);
    ekle(veriler, "Lokum", 87);

    ogeYazdir(veriler);

    silme(veriler, "abi");
    silme(veriler, "ali");
    ogeYazdir(veriler);

    ogeGetir(veriler, "meh");

    for (int i = 0; i < 100; i++)
    {
        if (veriler[i].anahtar != NULL)
        {
            /* if(i==5)
                fprintf(stdout, "\n|%d|\n",i); */
            free(veriler[i].anahtar);
            veriler[i].anahtar = NULL;
            veriler[i].veri = 0;
        }
    }
    free(veriler);
    veriler = NULL;
    if (veriler == NULL)
        fprintf(stdout, "veriler koflandi!\n");
    return 0;
}

void ogeYazdir(VERI_PTR veriler) 
{
    for (int i = 0; i < 100; i++)
    {
        if (veriler[i].anahtar != NULL)
            fprintf(stdout, "Anahtar: %s, Veri: %d\n", veriler[i].anahtar, veriler[i].veri);
    }
}

int hashIslemi(char *anahtar)
{
    int hashli = (anahtar[0] + anahtar[1]) % 100;
    //fprintf(stdout, "anahtar: %c + %c = %d\n", anahtar[0], anahtar[1], a);
    return hashli;
}

void ekle(VERI_PTR veriler, char *anahtar,int veri)
{
    int hashli;
    if (!(hashli = hashIslemi(anahtar)) || hashli > 99)
    {
        fprintf(stderr, "hashlemede hata oldu. Hash degeri: %d\n", hashli);
        return;
    }
    //fprintf(stdout, "oldu! %d\n", a);

    //fprintf(stdout, "yazi: %s. boyutu: %d\n", anahtar, strlen(anahtar));
    if (veriler[hashli].anahtar == NULL)
    {
        veriler[hashli].veri = veri;
        veriler[hashli].anahtar = calloc(strlen(anahtar), sizeof veriler[hashli].anahtar);
        //veriler[a].anahtar = malloc(-1);
        if (veriler[hashli].anahtar == NULL)
        {
            perror("veriler[].anahtar malloc ile ayrilanamadi!\nHata");
            return;
        }
        memmove(veriler[hashli].anahtar, anahtar, strlen(anahtar));
        fprintf(stdout, "Anahtar : %s ve degeri : %d eklendi!\n", veriler[hashli].anahtar, veriler[hashli].veri);
    }
    else
    {
        fprintf(stderr, "%s adina sahip zaten bir anahtar var!\n", anahtar);
        return;
    }
    /* if (veriler[a].anahtar == NULL)
        fprintf(stdout, "veriler[%d].anahtar kof\n", a); */
}

void silme(VERI_PTR veriler, char *anahtar) 
{
    int hashli;
    if (!(hashli = hashIslemi(anahtar)) || hashli > 99)
    {
        fprintf(stdout, "Hashlemede hata oldu. Hash degeri: %d\n", hashli);
        return;
    }
    //fprintf(stdout, "%d ve %s\n", hashli, veriler[hashli].anahtar);
    if (veriler[hashli].anahtar != NULL && memcmp(anahtar, veriler[hashli].anahtar, strlen(anahtar)) == 0)
    {
        veriler[hashli].veri = 0;
        free(veriler[hashli].anahtar);
        veriler[hashli].anahtar = NULL;
        if (veriler[hashli].anahtar != NULL)
        {
            fprintf(stderr, "veriler[].anahtar koflanamadi!\n");
            return;
        }else
            fprintf(stdout, "'%s' anahtari basarili bir sekilde silindi.\n", anahtar);
    }else{
        fprintf(stderr, "Boyle bir anahtara sahip veri yok! (Aranan anahtar: '%s')\n", anahtar);
        return; }
}

void ogeGetir(VERI_PTR veriler, char *anahtar)
{
    int hashli;
    if (!(hashli = hashIslemi(anahtar)) || hashli > 99)
    {
        fprintf(stderr, "Hashlemede hata oldu. Hash degeri: %d\n", hashli);
        return;
    }
    if (veriler[hashli].anahtar != NULL && memcmp(anahtar, veriler[hashli].anahtar, strlen(anahtar)) == 0)
        fprintf(stdout, "Aranan anahtar: %s, Aranan veri: %d\n", veriler[hashli].anahtar, veriler[hashli].veri);
    else{
        fprintf(stderr, "Getirilemedi..! Boyle bir anahtara sahip veri yok! (Aranan anahtar: '%s')\n", anahtar);
        return; }
}