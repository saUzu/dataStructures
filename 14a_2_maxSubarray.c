/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 4/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_2_maxSubarray.c -o 14a_2_maxSubarray
//      gcc 9.1.0
//
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//      - algoritmasını kendim yazdım, bir yerden alınmamıştır.
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define DIZIUZUNLUGU 9
#define BULUNACAKSAYI 6

int toplamBul(int *, int *);

int main(int argc, char **argv)
{

    //int *dizi=malloc(-1);
    int *dizi = malloc(sizeof(int) * DIZIUZUNLUGU);
    if (dizi == NULL)
    {
        perror("dizi malloc ile olusturulamadi!\nHata\t");
        goto cikis1;
    }
    dizi[0] = -2;
    dizi[1] = 1;
    dizi[2] = -3;
    dizi[3] = 4;
    dizi[4] = -1;
    dizi[5] = 2;
    dizi[6] = 1;
    dizi[7] = -5;
    dizi[8] = 4;

    int *topluDizi = malloc(sizeof(int) * DIZIUZUNLUGU);
    //int *toplananDizi = malloc(-1);
    if (topluDizi == NULL)
    {
        perror("topluDizi malloc ile olusturulamadi!\nHata\t");
        goto cikis2;
    }


    fprintf(stdout, "bulunacak sayi\t: %d\n", BULUNACAKSAYI);
    fprintf(stdout, "Dizinin ogeleri\t: ");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        fprintf(stdout, "%d ", dizi[i]);
    }
    fprintf(stdout, "\n\n");

    int hata = toplamBul(dizi, topluDizi);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "realloc basarili!\n");
        break;
    case 1:
        fprintf(stderr, "reallocta hata oldu!\n");
        break;
    case 2:
    fprintf(stderr, "realloc aynı adresi gondermedi hata oldu!\n");
        break;
    default:
        break;
    }

    fprintf(stdout, "#############################################\n");
cikis2:
    free(topluDizi);
    topluDizi = NULL;
    if (topluDizi == NULL)
        fprintf(stdout, "topluDizi KOF\n");
cikis1:
    free(dizi);
    dizi = NULL;
    if (dizi == NULL)
        fprintf(stdout, "dizi KOF\n");
    return 0;
}

int toplamBul(int *dizi, int *toplamDizi)
{
    void *adresPTR = toplamDizi;
    int geciciToplam = 0, genelToplam = -32000;
    int baslangic = 0, bitis = 0;
    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        geciciToplam += dizi[i];
        if (geciciToplam <= dizi[i])
        {
            geciciToplam = 0;
            geciciToplam += dizi[i];
            baslangic = i;
        }
        if (genelToplam <= geciciToplam){
            genelToplam = geciciToplam;
            bitis = i + 1;
        }
    }
    fprintf(stdout, "baslangic: %d, bitis: %d\n", baslangic, bitis);
    fprintf(stdout, "ptr: %d, dizi: %d\n", adresPTR, toplamDizi);
    for (int i = baslangic, k = 0; i < bitis; i++, k++)
        toplamDizi[k] = dizi[i];
    toplamDizi = realloc(toplamDizi, sizeof(int) * abs(bitis - baslangic));
    if (toplamDizi == NULL)
        return 1;
    if (adresPTR != toplamDizi)
        return 2;
    for (int i = 0; i < abs(bitis - baslangic); i++)
        fprintf(stdout, "%d, ", toplamDizi[i]);
    fprintf(stdout, "\ngenel toplam: %d, baslangic: %d, bitis: %d\n", genelToplam, baslangic, bitis);
    return 0;
};