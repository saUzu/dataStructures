/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 11/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_6_longestWord.c -o 14a_6_longestWord
//      gcc 9.1.0
//
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//      - algoritmasını kendim yazdım, bir yerden alınmamıştır.
//      - SA = BIT      KOF = NULL
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define GIRISUZUNLUGU 1025

void enUzunKelime(char *);

int main(int argc, char **argv)
{
    int ch;
    //char *giris = malloc(-1);
    char *giris = malloc(sizeof *giris * GIRISUZUNLUGU);
    if (giris == NULL)
    {
        perror("giris icin gereken mallocta hata oldu.\nHata");
        goto cikis;
    }

    if (fgets(giris, GIRISUZUNLUGU, stdin))
        if (sscanf(giris, "%c", &ch) == 1)
            enUzunKelime(giris);

cikis:
    free(giris);
    giris = NULL;
    if (giris == NULL)
        fprintf(stdout, "giris koflandi!\n");
    return 0;
}

void enUzunKelime(char *giris) 
{
    fprintf(stdout, "girilen yazi\t: %s\n", giris);
    char *kelime = malloc(sizeof *kelime * 30);
    char *geciciKelime = malloc(sizeof *geciciKelime * 30);
    memset(kelime, '\0', 30);
    memset(geciciKelime, '\0', 30);
    int sayac = 0;
    int k = 0;
    int i = 0;
    while (giris[i] != '\0')
    {   
        if ((giris[i] > 96 && giris[i] < 123) || (giris[i] > 64 && giris[i] < 91) || (giris[i]>47 && giris[i]<58))
        {
            geciciKelime[k++] = giris[i];
        }else{   
            if (sayac < k)
            {
                sayac = k;
                memcpy(kelime, geciciKelime, k);
                memset(geciciKelime, '\0', k);
                //fprintf(stdout, "kelime\t: %s\n", kelime);
            }
            k = 0;
        }
        ++i;
    }
    //fprintf(stdout, "\n");
    fprintf(stdout, "En uzun kelime\t: %s\nuzunlugu\t: %d\n", kelime,sayac);

    free(geciciKelime);
    geciciKelime = NULL;
    if(geciciKelime==NULL)
        fprintf(stdout, "geciciKelime koflandi!\n");
    free(kelime);
    kelime = NULL;
    if(kelime==NULL)
        fprintf(stdout, "kelime koflandi!\n");
}