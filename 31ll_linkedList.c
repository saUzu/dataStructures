/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 24/12/2021
//  Yazan : saUzu

//  Derlemek için ;
//  gcc -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 31ll_linkedList.c -o 31ll_linkedList
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//
//  -   arayaEkle işlevliği, diziler gibi sıfırdan değil 1'den  başlıyor.
//  -   sirayaGoreEKle işlevliği 1'den başlatıyor, 0'dan değil.
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct Dugum
{
    uint8_t *isim;
    int_fast16_t kactane;
    struct Dugum *siradaki;
} DUGUM, *DUGUM_PTR;

int_fast32_t dugumSayisi;

void ogeAta(DUGUM_PTR *, uint8_t *, int_fast16_t);
void basaEkle(DUGUM_PTR *, uint8_t *, int_fast16_t);
void arayaEkle(DUGUM_PTR *, uint8_t *, int_fast16_t, int_fast32_t);
void isimeGoreSil(DUGUM_PTR *, uint8_t *);
void sirayaGoreSil(DUGUM_PTR *, int_fast32_t);
void isimeGoreBul(DUGUM_PTR *, uint8_t *);
void sirayaGoreBul(DUGUM_PTR *, int_fast32_t);
void yazdir(DUGUM_PTR);
void kofla(DUGUM_PTR);


int main(int argc, char **argv)
{
    fprintf(stdout, "--------------------------------------------------------\n\n");
    fprintf(stdout, "Parametre Sayisi -->  %d\nProgramin Adi -->  %s\n", argc, argv[0]);
    fprintf(stdout, "--------------------------------------------------------\n\n");
    if (argc != 1)
    {
        fprintf(stderr, "Parametre girmeyiniz!\n");
        return 0;
    }

    DUGUM_PTR basDugum = NULL; //calloc(1, sizeof *basDugum);

    //-----------------------------------------HATA DENEMELERİ
    arayaEkle(&basDugum, (uint8_t *)"kek", 1313, 4);
    kofla(basDugum);
    basaEkle(&basDugum, (uint8_t *)"asd", 3131);
    isimeGoreSil(&basDugum, (uint8_t *)"hop");
    sirayaGoreSil(&basDugum, 5);
    isimeGoreBul(&basDugum, (uint8_t *)"asd");
    //-----------------------------------------BİTİŞ

    ogeAta(&basDugum, (uint8_t *)"ali", 31);

    //if (basDugum != NULL)
    //    fprintf(stdout, "ad: %s ve degeri: %" PRIdFAST16 "\n", basDugum->isim, basDugum->kactane);
    //else    fprintf(stdout, "kof olmus\n");

    ogeAta(&basDugum, (uint8_t *)"veli", 13);
    ogeAta(&basDugum, (uint8_t *)"leyla", 100);
    ogeAta(&basDugum, (uint8_t *)"eren", 540);

    yazdir(basDugum);

    basaEkle(&basDugum, (uint8_t *)"hatice", 874);
    yazdir(basDugum);

    arayaEkle(&basDugum, (uint8_t *)"selin", 65535, 4);
    yazdir(basDugum);

    //-------------------------------------HATA DENEMESİ
    arayaEkle(&basDugum, (uint8_t *)"kek", 1313, 100);
    isimeGoreSil(&basDugum, (uint8_t *)" ");
    isimeGoreSil(&basDugum, (uint8_t *)"ruhsar");
    sirayaGoreSil(&basDugum, 100);
    isimeGoreBul(&basDugum, (uint8_t *)" ");
    //-------------------------------------BİTİŞ

    isimeGoreSil(&basDugum, (uint8_t *)"hatice");
    yazdir(basDugum);
    ogeAta(&basDugum, (uint8_t *)"veli", 131);
    yazdir(basDugum);
    //-------------------------------------HATA DENEMESİ
    isimeGoreSil(&basDugum, (uint8_t *)"veli");
    //-------------------------------------BİTİŞ
    sirayaGoreSil(&basDugum, 1);
    yazdir(basDugum);
    sirayaGoreSil(&basDugum, 2);
    yazdir(basDugum);

    isimeGoreBul(&basDugum, (uint8_t *)"veli");
    sirayaGoreBul(&basDugum, 2);

    //free(basDugum);
    //basDugum = NULL;
    fprintf(stdout, "Dugum Sayisi:\t%" PRIdFAST32 "\n", dugumSayisi);
    kofla(basDugum);
    fprintf(stdout, "\nDugum Sayisi:\t%" PRIdFAST32 "\n", dugumSayisi);
    return 0;
}

void ogeAta(DUGUM_PTR *dugum, uint8_t *ad, int_fast16_t deger)
{
    if (deger > 65535)
    {
        fprintf(stdout, "deger 16salik degerden buyuk olamaz\n");
        return;
    }
    DUGUM_PTR yeniDugum = calloc(1, sizeof *yeniDugum);
    if (yeniDugum == NULL)
    {
        perror("ogeAta'da yeniDugum icin gereken alan acilamadi!\nHata:\t");
        return;
    }
    yeniDugum->isim = calloc(strlen((char *)ad) + 1, sizeof *(yeniDugum->isim));
    if (yeniDugum->isim == NULL)
    {
        perror("ogeAta'da yeniDugum->isim icin gereken alan acilamadi!\nHata:\t");
        free(yeniDugum);
        return;
    }
    memmove(yeniDugum->isim, ad, strlen((char *)ad) + 1);
    yeniDugum->kactane = deger;
    //fprintf(stdout, "adSO: %ld\n", strlen(ad[0]));
    //fprintf(stdout, "asd %s, %"PRIdFAST16" --1\n", yeniDugum->isim,yeniDugum->kactane);
    if (*dugum == NULL)
    {
        //fprintf(stdout, "kof\n");
        *dugum = yeniDugum;
        ++dugumSayisi;
        yeniDugum = NULL;
        return;
    }
    //fprintf(stdout, "asd\n");
    DUGUM_PTR gecici = (*dugum);
    while (1)
    {
        if (gecici->siradaki != NULL)
            gecici = gecici->siradaki;
        else
        {
            gecici->siradaki = yeniDugum;
            ++dugumSayisi;
            yeniDugum = NULL;
            gecici = NULL;
            return;
        }
    }
    free(yeniDugum->isim);
    free(yeniDugum);
    //if(ad[3] == '\0')
    //    fprintf(stdout, "kof2\n");
    //fprintf(stdout, "ad: %s, deger: %" PRIdFAST16 ", sizeofDeger: %ld, sizeofFast: %ld\n\n", ad, deger, sizeof deger, sizeof(int_fast16_t));
}

void basaEkle(DUGUM_PTR *dugum, uint8_t *ad, int_fast16_t deger) 
{
    if (deger > 65535)
    {
        fprintf(stdout, "deger 16salik degerden buyuk olamaz\n");
        return;
    }
    if ((*dugum) == NULL)
    {
        fprintf(stderr, "Dugum kof basa eklenemez!\n");
        return;
    }
    DUGUM_PTR yeniDugum = calloc(1, sizeof *yeniDugum);
    if (yeniDugum == NULL)
    {
        perror("basaEkle'de yeniDugum icin gereken alan acilamadi!\nHata:\t");
        return;
    }
    yeniDugum->isim = calloc(strlen((char *)ad) + 1, sizeof *(yeniDugum->isim));
    if (yeniDugum->isim == NULL)
    {
        perror("basaEkle'de yeniDugum->isim icin gereken alan acilamadi!\nHata:\t");
        free(yeniDugum);
        return;
    }
    memmove(yeniDugum->isim, ad, strlen((char *)ad) + 1);
    yeniDugum->kactane = deger;
    
    yeniDugum->siradaki = (*dugum);
    (*dugum) = yeniDugum;
    ++dugumSayisi;
    yeniDugum = NULL;
}

void arayaEkle(DUGUM_PTR *dugum, uint8_t *ad, int_fast16_t deger, int_fast32_t sira) 
{  
    if (deger > 65535)
    {
        fprintf(stdout, "deger 16salik degerden buyuk olamaz\n");
        return;
    }
    if ((*dugum) == NULL)
    {
        fprintf(stderr, "Dugum kof! Ara yokki ekleyek!!\n");
        return;
    }
    if (dugumSayisi < sira || sira < 1)
    {
        fprintf(stderr, "Oyle bir sira yok!\nVerilen Sira:\t%" PRIdFAST32 ", Dugum Sayisi:\t%" PRIdFAST32 "\n", sira, dugumSayisi);
        return;
    }
    if (sira == 1)
    {
        fprintf(stderr, "Basa eklenemez!\n");
        return;
    }
    //fprintf(stdout, "%s, %" PRIdFAST16 ", %s, %" PRIdFAST16 ", %" PRIdFAST32 "\n", (*dugum)->isim, (*dugum)->kactane, ad, deger, sira);
    DUGUM_PTR yeniDugum = calloc(1, sizeof *yeniDugum);
    if (yeniDugum == NULL)
    {
        perror("arayaEkle'de yeniDugum icin gereken alan acilamadi!\nHata:\t");
        return;
    }
    yeniDugum->isim = calloc(strlen((char *)ad) + 1, sizeof *(yeniDugum->isim));
    if (yeniDugum->isim == NULL)
    {
        perror("arayaEkle'de yeniDugum->isim icin gereken alan acilamadi!\nHata:\t");
        free(yeniDugum);
        return;
    }
    memmove(yeniDugum->isim, ad, strlen((char *)ad) + 1);
    yeniDugum->kactane = deger;

    DUGUM_PTR geciciDugum = (*dugum);
    while (--sira > 1)
        geciciDugum = geciciDugum->siradaki;

    yeniDugum->siradaki = geciciDugum->siradaki;
    geciciDugum->siradaki = yeniDugum;
    ++dugumSayisi;

    yeniDugum = NULL;
    geciciDugum = NULL;
    if(yeniDugum)
        free(yeniDugum);
    if(geciciDugum)
        free(geciciDugum);
}

void isimeGoreSil(DUGUM_PTR *dugum, uint8_t *ad)
{
    if ((*dugum) == NULL)
    {
        fprintf(stderr, "Dugum kof silinecek bir sey yok!\n");
        return;
    }
    if (memcmp(ad, " ", strlen((char *)ad)) == 0)
    {
        fprintf(stderr, "isimeGoreSil'deki 'ad' bosluk ve eklenemez!\n");
        return;
    }   
    DUGUM_PTR geciciDugum = (*dugum);
    DUGUM_PTR silinecekDugum = NULL;
    int32_t sayac = 0;
    int32_t sira = 0;    
    if (memcmp((*dugum)->isim, ad, strlen((char *)ad)) == 0)
    {
        silinecekDugum = (*dugum);
        geciciDugum = (*dugum)->siradaki;
        (*dugum) = geciciDugum;
        silinecekDugum->siradaki = NULL;
        --dugumSayisi;
        free(silinecekDugum->isim);
        free(silinecekDugum);
        return;
    }
    while (geciciDugum != NULL)
    {
        if (memcmp(geciciDugum->isim, ad, strlen((char *)ad)) == 0)
        {
            if (++sayac > 1)
            {
                fprintf(stderr, "Ayni isimde birden fazla deger var lutfen sirasina göre siliniz!\n");
                geciciDugum = NULL;
                silinecekDugum = NULL;
                return;
            }
            silinecekDugum = geciciDugum;
        }
        if (sayac < 1)
            ++sira;
        geciciDugum = geciciDugum->siradaki;
    }
    if (sayac == 0)
    {
        fprintf(stderr, "%s isime gore herhangi bir ogeye rastlanilamadi!\n", ad);
        geciciDugum = NULL;
        silinecekDugum = NULL;
        return;
    }
    //fprintf(stdout, "BULUNACAK ->\tsira: %" PRId32 ",isim: %s, sayac: %" PRId32 "\n", sira, silinecekDugum->isim, sayac);
    if (sayac == 1)
    {
        for (sayac = 0, geciciDugum = (*dugum); sayac < sira; geciciDugum = geciciDugum->siradaki, sayac++);
        //fprintf(stdout, "BULUNAN\t->\tisim: %s, deger: %" PRIdFAST16 "\n", geciciDugum->isim, geciciDugum->kactane);
        geciciDugum->siradaki = geciciDugum->siradaki->siradaki;
        --dugumSayisi;
        fprintf(stdout, "%s isimli ogeyi silmede basarili olundu!\n", silinecekDugum->isim);
        silinecekDugum->siradaki = NULL;
        free(silinecekDugum->isim);
        free(silinecekDugum);
    }
}

void sirayaGoreSil(DUGUM_PTR *dugum, int_fast32_t sira)
{
    if ((*dugum) == NULL)
    {
        fprintf(stderr, "Dugum kof neyi silicen!!\n");
        return;
    }
    if (dugumSayisi < sira || sira < 1)
    {
        fprintf(stderr, "Girdigin sira yok la yok!\n");
        return;
    }
    //fprintf(stdout, "%s, %" PRIdFAST32 "\n", (*dugum)->isim, sira);
    DUGUM_PTR geciciDugum = (*dugum);
    DUGUM_PTR silinecekDugum;
    if (sira == 1)
    {
        silinecekDugum = (*dugum);
        geciciDugum = (*dugum)->siradaki;
        (*dugum) = geciciDugum;
        --dugumSayisi;
        fprintf(stdout, "%s isimli ve %" PRIdFAST32 ". siradaki oge silindi\n", silinecekDugum->isim, sira);
        geciciDugum = NULL;
        silinecekDugum->siradaki = NULL;
        free(silinecekDugum->isim);
        free(silinecekDugum);
        return;
    }
    int_fast32_t sayac = 1;
    geciciDugum = (*dugum);
    for (; sayac < sira - 1; geciciDugum = geciciDugum->siradaki, ++sayac);
    //fprintf(stdout, "%s, %" PRIdFAST32 " asd\n", geciciDugum->isim, sayac);
    silinecekDugum = geciciDugum->siradaki;
    geciciDugum->siradaki = geciciDugum->siradaki->siradaki;
    --dugumSayisi;
    silinecekDugum->siradaki = NULL;
    free(silinecekDugum->isim);
    free(silinecekDugum);
    return;
}

void isimeGoreBul(DUGUM_PTR *dugum, uint8_t *ad)
{
    if ((*dugum) == NULL)
    {
        fprintf(stderr, "isimeGoreBul'da dugum kof cikti.\n");
        return;
    }
    if (memcmp(ad, " ", strlen((char *)ad)) == 0)
    {
        fprintf(stderr, "verilen ad bos. Eklenemez!\n");
        return;
    }
    DUGUM_PTR geciciDugum = (*dugum);
    int32_t sayac = 1;
    for (; geciciDugum != NULL; geciciDugum = geciciDugum->siradaki, sayac++)
    {
        if(memcmp(geciciDugum->isim, ad, strlen((char *)ad)) == 0)
        {
            fprintf(stdout, "Aranan isim: %s, ve sirasi: %" PRId32 "\n", geciciDugum->isim, sayac);
            sayac = 0;
        }
    }
    geciciDugum = NULL;
    return;
}

void sirayaGoreBul(DUGUM_PTR *dugum, int_fast32_t sira) 
{
    fprintf(stdout, "%" PRIdFAST32 ", %s\n", sira, (*dugum)->isim);
    if ((*dugum) == NULL)
    {
        fprintf(stdout, "sirayaGoreBul'daki dugum kof!\n");
        return;
    }
    DUGUM_PTR geciciDugum = (*dugum);
    int32_t sayac = 1;
    for (; sayac < sira; geciciDugum = geciciDugum->siradaki, ++sayac);
    fprintf(stdout, "Aranan sira: %" PRId32 ", isim: %s\n", sayac, geciciDugum->isim);
    geciciDugum = NULL;
    return;
}

void yazdir(DUGUM_PTR dugum)
{
    for (; dugum != NULL; dugum = dugum->siradaki)
    {
        fprintf(stdout, "(%s, %" PRIdFAST16 ") - ", dugum->isim, dugum->kactane);
    }
    fprintf(stdout, "\n");
}

void kofla(DUGUM_PTR dugum)
{
    if (dugum == NULL)
    {
        fprintf(stderr, "Dugum zaten kof, koflanamaz!\n");
        return;
    }
    while(1)
    {
        DUGUM_PTR ptr;
        ptr = dugum;
        dugum = dugum->siradaki;
        ptr->siradaki = NULL;
        free(ptr);
        --dugumSayisi;
        fprintf(stdout, "kof - ");
        if (dugum == NULL)
            return;
    }
}



/*  

                        YAPILACAKLAR
-   ##-BİTTİ-##     malloclar ve calloclar "kof döndürüyor mu?" denetimi yapılacak! 
-   ##-BİTTİ-##     isime göre silme
-   ##-BİTTİ-##     sıraya göre silme
-   ##-BİTTİ-##     sırası verilen öğeye erişim sağlanacak
-   ##-BİTTİ-##     ismi verilen öğeye erişim sağlanacak

*/