/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 2/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_1_twoSum.c -o 14a_1_twoSum
//      gcc 9.1.0
//
//      - malloc(-1) olanlar malloc hata denemesi için varlar.
//
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUYUKSAYI 100000
#define DIZI 3
#define BULUNACAKSAYI 6

void toplamBul(int *, int *);

int main(int argc, char **argv)
{
    int *dizi = malloc(sizeof(int) * DIZI);
    //int *dizi = malloc(-1);
    if (dizi == NULL)
    {
        perror("dizi icin malloc'ta sorun oldu.\nHata\t");
        goto cikis2;
    }
    
    int *bulunan = malloc(sizeof(int) * 2); // sonuç her zaman 2 sayı döndüreceği için sabit.
    //int *bulunan = malloc(-1);
    if (bulunan == NULL)
    {
        perror("bulunan icin malloc'ta sorun oldu.\nHata\t");
        goto cikis1;
    }
    //  topları bu kadar edecek iki sayı olmaması için olabildiğince büyük bir sayı ataması yaptım.
    bulunan[0] = BUYUKSAYI;
    bulunan[1] = BUYUKSAYI;

    //  deneme verisi 1, yukarıdaki global değişkenleri ona göre değiştirin DIZI 4, BULUNACAKSAYI 9
    /* dizi[0] = 2;
    dizi[1] = 7;
    dizi[2] = 11;
    dizi[3] = 15; */

    //  deneme verisi 2, yukarıdaki global değişkenleri ona göre değiştirin DIZI 3, BULUNACAKSAYI 6
    dizi[0] = 3;
    dizi[1] = 2;
    dizi[2] = 4;

    fprintf(stdout, "\nBulunacak sayi\t: %d\nDizi Ogeleri\t: ", BULUNACAKSAYI);
    for (int i = 0; i < DIZI; i++)
    {
        fprintf(stdout, "%d ", dizi[i]);
    }
    fprintf(stdout, "\n");


    //  istenen sayıyı bulma bulma
    toplamBul(dizi, bulunan);

    if (bulunan[0] == 10000 && bulunan[1] == 10000)
        fprintf(stdout, "oyle iki sayi bulunamadi!\n");
    else
        fprintf(stdout, "toplamlari %d olan sayilarin oge sirasi\t: %d ve %d\n", BULUNACAKSAYI, bulunan[0], bulunan[1]);

//  temizlik işlemleri
    fprintf(stdout, "-------------------------------------------------\n\n");
cikis1:
    free(bulunan);
    bulunan = NULL;
    if (bulunan == NULL)
        fprintf(stdout, "bulunan KOF\n");
cikis2:
    free(dizi);
    dizi = NULL;
    if (dizi == NULL)
        fprintf(stdout, "dizi KOF\n");
    return 0;
}


//  eğer dizinin i'li öğesi BULUNACAKSAYI'dan büyükse eksili bir değer dönderecek ve 
//  for döngüsünü çalıştırmayacak
void toplamBul(int *dizi, int *bulunan)
{
    int bulunacakSayi;
    for (int i = 0; i < DIZI; i++)
    {
        bulunacakSayi = BULUNACAKSAYI - dizi[i];
        for (int k = 0; k < DIZI && bulunacakSayi > 0; k++)
        {
            if (k != i && dizi[k] == bulunacakSayi)
            {
                bulunan[0] = i;
                bulunan[1] = k;
                return;
            }
        }
    }
    
};