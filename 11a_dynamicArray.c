/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//      Tarih : 27/11/2021
//      Yazan : saUzu
//      Derlemek için : gcc 11a_dynamicArray.c -o 11a_dynamicArray
//      gcc 9.1.0
//
//      GELİŞTİRİLEBİLİNECEK ALANLAR;
//  - Hata denetimi iyileştirilebilinir.
//  - Öğeye göre silmede string veya char ifadeleri gönderilebilineceğine dair hata denetimi yapılabilinir.
//  - Öğeye göre silmede birden fazla aynı öğe varsa ilk baştaki veya sonraki silinebilinir. (Şu anda sadece hata verip çıkıyor.)
/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//  DEFINE kısmı
#define DIZIUZUNLUGU 20

//  STRUCT kısmı
typedef struct DinamikDizi
{
    size_t uzunlugu;
    int *dDizi;
} DIZI, *DIZI_PTR;

//  İşlevlikleri(Function) tanımlama kısmı
int ogeAta(DIZI_PTR);
int sonaEkle(DIZI_PTR, int);
int basaEkle(DIZI_PTR, int);
int arayaEkle(DIZI_PTR, int, int);
int ogeSil(DIZI_PTR, int);
int siraSil(DIZI_PTR, int);

/*  Program başlangıcı  */
int main(int argc, char **argv)
{
    int hata;
    DIZI_PTR diziPtr = malloc(sizeof diziPtr);
    if (diziPtr == NULL)
        goto cikis1;

    //  -----------------------------------------------------------------------------------
    //  denenecek diziye başlangıç değerleri atama
    hata = ogeAta(diziPtr);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "struct'a ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "Dizinin uzunlugunu atamada hata oldu!\n");
        goto cikis1;
    case 2:
        fprintf(stderr, "Diziye oge atamada hata oldu!\n");
        goto cikis2;
    default:
        fprintf(stdout, "---------------------------------------------------------------\n");
        fprintf(stdout, "Anlasilmayan bir hata olustu!\n");
        goto cikis2;
        break;
    }
    fprintf(stdout, "dizi boyutu : %d | struct boyutu : %d\n", sizeof diziPtr->dDizi, sizeof diziPtr);

    fprintf(stdout, "Dizinin uzunlugu\t\t\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Dizinin ogeleri\t\t\t\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");
    

    //  -----------------SONA EKLE-----------------------------------------------------------
    fprintf(stdout, "---------------------------------------------------------------\n");
    hata = sonaEkle(diziPtr, 131);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "SE Dizi realloc basarili ve ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "SE Dizi reallocta hata oldu!\n");
        goto cikis2;
    default:
        fprintf(stdout, "---------------------------------------------------------------\n");
        fprintf(stdout, "Anlasilmayan bir hata olustu!\n");
        goto cikis2;
    }

    fprintf(stdout, "\neklenen : %d || hata : %d\n\n", diziPtr->dDizi[diziPtr->uzunlugu - 1], hata);

    fprintf(stdout, "Sona Eklenen Yeni Dizinin uzunlugu\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Sona Eklenen Yeni Dizinin ogeleri\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");



    //  -----------------BAŞA EKLE-----------------------------------------------------------
    fprintf(stdout, "---------------------------------------------------------------\n");
    hata = basaEkle(diziPtr, 31);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "BE Dizi realloc basarili ve ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "BE Dizi reallocta hata oldu!\n");
        goto cikis2;
    default:
        fprintf(stdout, "---------------------------------------------------------------\n");
        fprintf(stdout, "Anlasilmayan bir hata olustu!\n");
        goto cikis2;
    }

    fprintf(stdout, "\neklenen : %d || hata : %d\n\n", diziPtr->dDizi[0], hata);

    fprintf(stdout, "Basa Eklenen Yeni Dizinin uzunlugu\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Basa Eklenen Yeni Dizinin ogeleri\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");


    //  -----------------ARAYA EKLE-----------------------------------------------------------
    fprintf(stdout, "---------------------------------------------------------------\n");
    hata = arayaEkle(diziPtr, 231, 5);
    //hata = arayaEkle(diziPtr, 231, 17);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "AE Dizi realloc basarili ve ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "AE Dizi reallocta hata oldu!\n");
        goto cikis2;
    default:
        fprintf(stdout, "---------------------------------------------------------------\n");
        fprintf(stdout, "Anlasilmayan bir hata olustu!\n");
        goto cikis2;
    }

    fprintf(stdout, "\neklenen : %d || hata : %d\n\n", diziPtr->dDizi[5], hata);

    fprintf(stdout, "Araya Eklenen Yeni Dizinin uzunlugu\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Araya Eklenen Yeni Dizinin ogeleri\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n");
    fprintf(stdout, "\n");


    //  -----------------ÖĞE SİL-----------------------------------------------------------
    fprintf(stdout, "---------------------------------------------------------------\n");
    hata = ogeSil(diziPtr, 17);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "OS Dizi realloc basarili ve ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "OS Dizi reallocta hata oldu!\n");
        goto cikis2;
    case 2:
        fprintf(stderr, "OS aranan oge bulunamadi!\n");
        goto cikis2;
    case 3:
        fprintf(stderr, "OS aranan oge birden fazla var!\n");
        goto cikis2;
    default:
        fprintf(stdout, "---------------------------------------------------------------\n");
        fprintf(stdout, "Anlasilmayan bir hata olustu!\n");
        goto cikis2;
    }

    fprintf(stdout, "\noge ile silinen : %d || hata : %d\n\n", 17, hata);

    fprintf(stdout, "Ogesi Silinen Yeni Dizinin uzunlugu\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Ogesi Silinen Yeni Dizinin ogeleri\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n\n");


    //  -----------------SIRA SİL-----------------------------------------------------------
    fprintf(stdout, "---------------------------------------------------------------\n");
    hata = siraSil(diziPtr, 3);
    switch (hata)
    {
    case 0:
        fprintf(stdout, "SS Dizi realloc basarili ve ogeleri atandi!\n");
        break;
    case 1:
        fprintf(stderr, "SS Dizi reallocta hata oldu!\n");
        goto cikis2;
    default:
        goto cikis2;
    }

    fprintf(stdout, "\nsira ile silinen : %d || hata : %d\n\n", 3, hata);

    fprintf(stdout, "Sirasi Silinen Yeni Dizinin uzunlugu\t: %d\n",diziPtr->uzunlugu);
    fprintf(stdout, "Sirasi Silinen Yeni Dizinin ogeleri\t: ");
    for (int i = 0; i < diziPtr->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",diziPtr->dDizi[i]);
    };
    fprintf(stdout, "\n\n");



    fprintf(stdout, "---------------------------------------------------------------\n");
cikis2:
    free(diziPtr->dDizi);
    diziPtr->dDizi = NULL;
    if(diziPtr->dDizi==NULL)
        fprintf(stdout, "ana DIZI null\n");
cikis1:
    free(diziPtr);
    diziPtr = NULL;
    if(diziPtr==NULL)
        fprintf(stdout, "ana STRUCT null\n");
    return 0;
};

//  Kodu denemek için gereken deneme dizisini oluşturma ve öğe atamasını yapıyor.
int ogeAta(DIZI_PTR dizi)
{
    dizi->uzunlugu = DIZIUZUNLUGU;
    if (dizi->uzunlugu != DIZIUZUNLUGU)
        return 1;
    dizi->dDizi=malloc(sizeof dizi->dDizi * DIZIUZUNLUGU);
    if (dizi->dDizi == NULL)
        return 1;
    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        dizi->dDizi[i] = i;
    };
    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        if(dizi->dDizi[i]!=i)
            return 2;
    };
    return 0;
};

//  Gönderilen dizinin sonuna gönderilen öğeyi ekliyor.
//  eğer eski dizinin adresi realloctan sonraki adrese eşit değilse öğe atamalarını baştan yapıyor.
int sonaEkle(DIZI_PTR dizi, int eklenecek)
{
    void *adresPtr;
    DIZI_PTR eskiDizi = malloc(sizeof eskiDizi);
    eskiDizi->uzunlugu = dizi->uzunlugu;
    eskiDizi->dDizi = malloc(sizeof eskiDizi->dDizi * eskiDizi->uzunlugu);
    size_t yeniUzunluk = eskiDizi->uzunlugu + 1;
    adresPtr = dizi->dDizi;
    //fprintf(stdout, "%p, %p, %p\n", adresPtr, dizi->dDizi, &dizi->dDizi[0]);

    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        eskiDizi->dDizi[i] = dizi->dDizi[i];
    };

    /* fprintf(stdout, "-----------------------------------\n");
    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",eskiDizi->dDizi[i]);
    };
    fprintf(stdout, "\n"); */

    dizi->dDizi = realloc(dizi->dDizi, sizeof yeniUzunluk * yeniUzunluk);
    dizi->uzunlugu = yeniUzunluk;
    

    if(dizi->dDizi==NULL)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        free(eskiDizi);
        eskiDizi = NULL;
        return 1;
    };
        

    if(adresPtr != dizi->dDizi)
    {
        for (int i = 0; i < eskiDizi->uzunlugu; i++)
        {
            dizi->dDizi[i] = eskiDizi->dDizi[i];
        };
        /* fprintf(stdout, "///////////////////////////////////////\n");
        for (int i = 0; i < dizi->uzunlugu; i++)
        {
            fprintf(stdout, "%d ", dizi->dDizi[i]);
        };
        fprintf(stdout, "\n"); */
    };
    dizi->dDizi[eskiDizi->uzunlugu] = eklenecek;


    //fprintf(stdout, "asd\n");
    free(eskiDizi->dDizi);
    eskiDizi->dDizi = NULL;
    if(eskiDizi->dDizi==NULL)
        fprintf(stdout, "sona eklenen eski DIZI null\n");
    free(eskiDizi);
    eskiDizi = NULL;
    if(eskiDizi==NULL)
        fprintf(stdout, "sona eklenen eski STRUCT null\n");
    return 0;
};

//  Gönderilen dizinin başına gönderilen öğe ekleniyor.
//  adres denetimi yok burada
int basaEkle(DIZI_PTR dizi, int eklenecek)
{
    DIZI_PTR eskiDizi = malloc(sizeof eskiDizi);
    eskiDizi->uzunlugu = dizi->uzunlugu;
    eskiDizi->dDizi = malloc(sizeof eskiDizi->dDizi * eskiDizi->uzunlugu);
    //fprintf(stdout, "dizi boyutu : %d | struct boyutu : %d\n", sizeof eskiDizi->dDizi, sizeof eskiDizi);

    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        eskiDizi->dDizi[i] = dizi->dDizi[i];
    };
    /* fprintf(stdout, "Basa eklenecek eski dizi\t: ");
    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",eskiDizi->dDizi[i]);
    };
    fprintf(stdout, "\n"); */

    dizi->dDizi = realloc(dizi->dDizi, sizeof eskiDizi->uzunlugu * (eskiDizi->uzunlugu + 1));
    if (dizi->dDizi == NULL)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        free(eskiDizi);
        eskiDizi = NULL;
        return 1;
    };
    dizi->uzunlugu = eskiDizi->uzunlugu + 1;
    dizi->dDizi[0] = eklenecek;
    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        dizi->dDizi[i + 1] = eskiDizi->dDizi[i];
    };

    /* fprintf(stdout, "/////////////////////////////\nElemanlari\t: ");
    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        fprintf(stdout, "%d ",dizi->dDizi[i]);
    };
    fprintf(stdout, "\n"); */

    free(eskiDizi->dDizi);
    eskiDizi->dDizi = NULL;
    if(eskiDizi->dDizi==NULL)
        fprintf(stdout, "basa eklenen eski DIZI null\n");
    free(eskiDizi);
    eskiDizi = NULL;
    if(eskiDizi==NULL)
        fprintf(stdout, "basa eklenen eski STRUCT null\n");

    return 0;
};

//  Gönderilen diziye, eklenecek yere gönderilen öğe ekleniyor.
//  eklenecek yere kadar olan yere kadar diziye atama yapıyor daha sonra
//  oraya yeni öğeyi ekliyor sonra kalan verileri yazmaya devam ediyor.
int arayaEkle(DIZI_PTR dizi, int eklenecek, int buraya)
{
    DIZI_PTR eskiDizi = malloc(sizeof eskiDizi);
    eskiDizi->uzunlugu = dizi->uzunlugu;
    eskiDizi->dDizi = malloc(sizeof eskiDizi->dDizi * eskiDizi->uzunlugu);

    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        eskiDizi->dDizi[i] = dizi->dDizi[i];
    };

    /* fprintf(stdout, "!!!!!!!!!!!!\t: ");
    for (int i = 0; i < eskiDizi->uzunlugu; i++)
    {
        fprintf(stdout, "%d ", eskiDizi->dDizi[i]);
    };
    fprintf(stdout, "\n"); */

    dizi->dDizi = realloc(dizi->dDizi, sizeof dizi->dDizi * (dizi->uzunlugu + 1));
    if (dizi->dDizi == NULL)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        free(eskiDizi);
        eskiDizi = NULL;
        return 1;
    };
    dizi->uzunlugu = dizi->uzunlugu + 1;

    for (int i = 0; i < buraya; i++)
    {
        dizi->dDizi[i] = eskiDizi->dDizi[i];
    };
    dizi->dDizi[buraya] = eklenecek;
    for (int i = (buraya + 1); i < dizi->uzunlugu; i++)
    {
        dizi->dDizi[i] = eskiDizi->dDizi[i - 1];
    };

    free(eskiDizi->dDizi);
    eskiDizi->dDizi = NULL;
    if(eskiDizi->dDizi==NULL)
        fprintf(stdout, "araya eklenen eski DIZI null\n");
    free(eskiDizi);
    eskiDizi = NULL;
    if(eskiDizi==NULL)
        fprintf(stdout, "araya eklenen eski STRUCT null\n");
    return 0;
};

  
int ogeSil(DIZI_PTR dizi, int silinecek)
{
    DIZI_PTR eskiDizi = malloc(sizeof eskiDizi);
    eskiDizi->uzunlugu = dizi->uzunlugu - 1;
    eskiDizi->dDizi = malloc(sizeof eskiDizi->dDizi * eskiDizi->uzunlugu);
    //fprintf(stdout, "silinecek : %d\n", silinecek);

    int sayac = 0;
    for (int i = 0, k = 0; i < dizi->uzunlugu; i++)
    {
        if (dizi->dDizi[i] == silinecek)
        {
            ++sayac;
            continue;
        }
        else    eskiDizi->dDizi[k++] = dizi->dDizi[i];
    };
    if (sayac == 0) 
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        if(eskiDizi->dDizi == NULL)
            fprintf(stdout,"oge sil eski DIZI null\n");
        free(eskiDizi);
        eskiDizi = NULL;
        if(eskiDizi == NULL)
            fprintf(stdout,"oge sil eski STRUCT null\n");
        return 2;
    };
    if (sayac > 1)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        if(eskiDizi->dDizi == NULL)
            fprintf(stdout,"oge sil eski DIZI null\n");
        free(eskiDizi);
        eskiDizi = NULL;
        if(eskiDizi == NULL)
            fprintf(stdout,"oge sil eski STRUCT null\n");
        return 3;
    };;
    dizi->dDizi = realloc(dizi->dDizi, sizeof dizi->dDizi * eskiDizi->uzunlugu);
    if (dizi->dDizi == NULL)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        free(eskiDizi);
        eskiDizi = NULL;
        return 1;
    };
    dizi->uzunlugu = eskiDizi->uzunlugu;
    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        dizi->dDizi[i] = eskiDizi->dDizi[i];
    };
    /* fprintf(stdout, "%d -- ================\t\t\t: ", dizi->uzunlugu);
    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        fprintf(stdout, "%d ", dizi->dDizi[i]);
    };
    fprintf(stdout, "\n"); */

    free(eskiDizi->dDizi);
    eskiDizi->dDizi = NULL;
    if(eskiDizi->dDizi == NULL)
        fprintf(stdout,"oge sil eski DIZI null\n");
    free(eskiDizi);
    eskiDizi = NULL;
    if(eskiDizi == NULL)
        fprintf(stdout,"oge sil eski STRUCT null\n");
    return 0;
};

int siraSil(DIZI_PTR dizi, int sira)
{
    DIZI_PTR eskiDizi = malloc(sizeof eskiDizi);
    eskiDizi->uzunlugu = dizi->uzunlugu - 1;
    eskiDizi->dDizi = malloc(sizeof eskiDizi->dDizi * eskiDizi->uzunlugu);
    //fprintf(stdout, "%d\n", sira);

    for (int i = 0, k = 0; i < dizi->uzunlugu; i++)
    {
        if (i == sira)  continue;
        else    eskiDizi->dDizi[k++] = dizi->dDizi[i];
    };

    dizi->dDizi = realloc(dizi->dDizi, sizeof dizi->dDizi * eskiDizi->uzunlugu);
    if (dizi->dDizi == NULL)
    {
        free(eskiDizi->dDizi);
        eskiDizi->dDizi = NULL;
        free(eskiDizi);
        eskiDizi = NULL;
        return 1;
    };
    dizi->uzunlugu = eskiDizi->uzunlugu;

    for (int i = 0; i < dizi->uzunlugu; i++)
    {
        dizi->dDizi[i] = eskiDizi->dDizi[i];
    };

    free(eskiDizi->dDizi);
    eskiDizi->dDizi = NULL;
    if(eskiDizi->dDizi == NULL)
        fprintf(stdout,"sira sil eski DIZI null\n");
    free(eskiDizi);
    eskiDizi = NULL;
    if(eskiDizi == NULL)
        fprintf(stdout,"sira sil eski STRUCT null\n");
    return 0;
};