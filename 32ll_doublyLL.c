/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//  Tarih : 25/12/2021
//  Yazan : saUzu
//  Derlemek için ;
//  gcc -m64 -Wall -Wextra -Wpedantic -Werror -Wshadow -Wstrict-overflow -fno-strict-aliasing -O2 -std=c99 32ll_doublyLL.c -o 32ll_doublyLL
//
//  Fedora 35
//  gcc (GCC) 11.2.1
//  
//  -   gcc'de dikkat ederseniz -m64 işartlenerek 64-sa için compile edilmiştir. 32-sa için -m32 yazın.
//  -   ekle işlevliği, başa eklenmesi için 1 sona eklenmesi için düğüm sayısından bir fazlası olarak girilmesi gerekiyor.
//      eğer büyük sayı verilirse hata veriyor. 1 ila düğüm sayısı arasında bir sayı verirseniz o sıraya ekliyor.
//  -   koflama işlemi sondan ve baştan aynı anda koflayarak ilerliyor.
//  -   adaGore ve sirayaGore silme ve bulma işlemleri baştan ve sondan başlayarak çift yönlü işlem yapıyor.
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>
#include <string.h>
//#include <stdint.h>
#include <inttypes.h>
//#include <unistd.h>

typedef struct Dugum{
    uint8_t *isim;
    int_least32_t sayisi;
    struct Dugum *onceki;
    struct Dugum *sonraki;
} DUGUM, *DUGUM_PTR;

uint_least32_t dugumSayisi;

void kofla(DUGUM_PTR, DUGUM_PTR);
void yazdir(DUGUM_PTR);
void ekle(DUGUM_PTR *, DUGUM_PTR *, uint8_t *, int_least32_t, uint_least32_t);
void adaGoreSil(DUGUM_PTR *, DUGUM_PTR *, uint8_t *);
void sirayaGoreSil(DUGUM_PTR *, DUGUM_PTR *, uint_least32_t);
void adaGoreBul(DUGUM_PTR *, DUGUM_PTR *, uint8_t *);
void sirayaGoreBul(DUGUM_PTR *, DUGUM_PTR *, uint_least32_t);

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        fprintf(stderr, "Lutfen herhangi bir parametre eklemeden calistirin.\n");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "\n-\tParametre sayisi: %d\n", argc);
    fprintf(stdout, "-\tProgramin adi: %s\n", argv[0]);
    fprintf(stdout, "-----------------------------------------------\n");

    DUGUM_PTR basDugum = NULL;
    DUGUM_PTR kicDugum = NULL;
    //fprintf(stdout, "%" PRIuLEAST32 "\n", dugumSayisi);

    //          HATA DENETİMİ
    yazdir(basDugum);
    kofla(basDugum, kicDugum);
    ekle(&basDugum, &kicDugum, (uint8_t *)"qwer", 2222, 44);
    ekle(&basDugum, &kicDugum, (uint8_t *)"", 9999, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)" ", 9999, 1);
    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"qwer");
    //          BİTTİ
    fprintf(stdout, "\n");

    //fprintf(stdout, "ds: %" PRIuLEAST32 "\n", dugumSayisi);
    ekle(&basDugum, &kicDugum, (uint8_t *)"seyma", 4, 1);
    yazdir(basDugum);
    //fprintf(stdout, "ds: %" PRIuLEAST32 "\n", dugumSayisi);
    ekle(&basDugum, &kicDugum, (uint8_t *)"eray", 11, 2);
    ekle(&basDugum, &kicDugum, (uint8_t *)"gul", 26, 3);
    ekle(&basDugum, &kicDugum, (uint8_t *)"burak", 77, 4);
    ekle(&basDugum, &kicDugum, (uint8_t *)"eda", 90, 5);
    yazdir(basDugum);
    //fprintf(stdout, "ds: %" PRIuLEAST32 "\n", dugumSayisi);

    ekle(&basDugum, &kicDugum, (uint8_t *)"attila", 17, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)"cicek", 1, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)"hala", 88, 6);
    ekle(&basDugum, &kicDugum, (uint8_t *)"teyze", 88, 9);
    ekle(&basDugum, &kicDugum, (uint8_t *)"baba", 150, 1);
    yazdir(basDugum);
    fprintf(stdout, "\n");
    //fprintf(stdout, "ds: %" PRIuLEAST32 "\n", dugumSayisi);

    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"1234");
    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"hala");
    yazdir(basDugum);
    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"baba");
    yazdir(basDugum);
    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"teyze");
    yazdir(basDugum);
    ekle(&basDugum, &kicDugum, (uint8_t *)"gul", 88, 6);
    ekle(&basDugum, &kicDugum, (uint8_t *)"baba", 55, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)"baba", 150, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)"teyze", 88, 11);
    yazdir(basDugum);
    adaGoreSil(&basDugum, &kicDugum, (uint8_t *)"gul");
    sirayaGoreSil(&basDugum, &kicDugum, 2);
    sirayaGoreSil(&basDugum, &kicDugum, 1);
    yazdir(basDugum);
    sirayaGoreSil(&basDugum, &kicDugum, 6);
    sirayaGoreSil(&basDugum, &kicDugum, 8);
    yazdir(basDugum);

    ekle(&basDugum, &kicDugum, (uint8_t *)"bul", 55, 1);
    ekle(&basDugum, &kicDugum, (uint8_t *)"bul", 55, 4);
    ekle(&basDugum, &kicDugum, (uint8_t *)"bul", 55, 10);
    ekle(&basDugum, &kicDugum, (uint8_t *)"bul", 55, 7);
    yazdir(basDugum);
    adaGoreBul(&basDugum, &kicDugum, (uint8_t *)"bul");

    sirayaGoreBul(&basDugum, &kicDugum, 3);
    sirayaGoreBul(&basDugum, &kicDugum, 5);
    sirayaGoreBul(&basDugum, &kicDugum, 6);
    sirayaGoreBul(&basDugum, &kicDugum, 9);


    kofla(basDugum, kicDugum);
    return EXIT_SUCCESS;
}

void kofla(DUGUM_PTR basDugum, DUGUM_PTR kicDugum)
{
    if (!basDugum && !kicDugum)
    {
        fprintf(stderr, " > dugum kof koflanamaz!\n");
        return;
    }
    fprintf(stdout, "\nDugum Sayisi:\t%" PRIuLEAST32 "\n", dugumSayisi);
    DUGUM_PTR sil;
    while (basDugum && kicDugum)
    {
        if(basDugum!=kicDugum && basDugum)
        {
            sil = basDugum;
            //fprintf(stdout, "%s ", sil->isim);
            basDugum = basDugum->sonraki;
            sil->onceki = NULL;
            sil->sonraki = NULL;
            free(sil->isim);
            free(sil);
            --dugumSayisi;
            fprintf(stdout, "kof - ");
        }
        if(kicDugum)
        {
            if (kicDugum == basDugum)
                basDugum = NULL;
            sil = kicDugum;
            //fprintf(stdout, "%s ", sil->isim);
            kicDugum = kicDugum->onceki;
            sil->onceki = NULL;
            sil->sonraki = NULL;
            free(sil->isim);
            free(sil);
            --dugumSayisi;
            fprintf(stdout, "kof - ");
        }
    }
    fprintf(stdout, "\nDugum Sayisi:\t%" PRIuLEAST32 "\n", dugumSayisi);
}

void yazdir(DUGUM_PTR dugum)
{
    if (!dugum)
    {
        fprintf(stderr, " > dugum kof, oge yokki yazak!\n");
        return;
    }
    fprintf(stdout, "- Yazdirilan ogeler:\t");
    for (DUGUM_PTR yazilacak = dugum; yazilacak != NULL; yazilacak = yazilacak->sonraki)
        fprintf(stdout, "(%s, %" PRIdLEAST32 ") - ", yazilacak->isim, yazilacak->sayisi);
    fprintf(stdout, "\n");
}

void ekle(DUGUM_PTR *basDugum, DUGUM_PTR *kicDugum, uint8_t *adi, int_least32_t sayisi, uint_least32_t sirasi)
{
    if (memcmp(adi, " ", strlen((char *)adi)) == 0 || memcmp(adi, "", strlen((char *)adi)) == 0)
    {
        fprintf(stderr, " > adi bos eklenemez.(ekle)\n");
        return;
    }
    if (!(*basDugum) && (*kicDugum))
    {
        fprintf(stderr, " > kic dolu, basi kof nasil olur. Bu nasil hata anlamadik valla....(ekle)\n");
        return;
    }
    if (sirasi > dugumSayisi + 1)
    {
        fprintf(stderr, " > sira sayisi oge sayisindan fazla.(ekle)\n");
        return;
    }
    if (sirasi == 0)
    {
        fprintf(stderr, " > Sifirinci sira ne demek ben anlamamak..(ekle)(Basa eklemek icin 1 degerini girin)\n");
        return;
    }
    if (!(*basDugum) && !(*kicDugum))
    {
        (*basDugum) = calloc(1, sizeof *(*basDugum));
        if (!(*basDugum))
        {
            perror(" > basDugum icin alan olusturulamadi.(ekle)\nHata ");
            return;
        }
        (*basDugum)->isim = calloc(strlen((char *)adi), sizeof *((*basDugum)->isim));
        if (!((*basDugum)->isim))
        {
            perror(" > basDugum->isim icin alan olusturulamadi.(ekle)\nHata ");
            return;
        }
        memmove((*basDugum)->isim, adi, strlen((char *)adi));
        (*kicDugum) = calloc(1, sizeof *(*kicDugum));
        if (!(*kicDugum))
        {
            perror(" > kicDugum icin alan olusturulamadi.(ekle)\nHata ");
            free((*basDugum)->isim);
            free((*basDugum));
            return;
        }
        (*kicDugum)->isim = NULL;
        (*kicDugum)->sonraki = NULL;
        (*kicDugum)->onceki = (*basDugum);
        (*basDugum)->sayisi = sayisi;
        (*basDugum)->sonraki = (*kicDugum);
        dugumSayisi += 2;
        return;
    }
    if (!((*kicDugum)->isim))
    {
        (*kicDugum)->isim = calloc(strlen((char *)adi), sizeof *((*kicDugum)->isim));
        if(!((*kicDugum)->isim))
        {
            perror(" > kicDugum->isim icin alan olusturulamadi.(ekle)\nHata ");
            return;
        }
        memmove((*kicDugum)->isim, adi, strlen((char *)adi));
        //fprintf(stdout, "$$$$$\n");
        (*kicDugum)->sayisi = sayisi;
        return;
    }
    if (sirasi <= (dugumSayisi + 1) && ((*basDugum)->isim) && ((*kicDugum)->isim))
    {
        DUGUM_PTR geciciD;
        DUGUM_PTR eklenecekD = calloc(1, sizeof *eklenecekD);
        if(!eklenecekD)
        {
            perror(" > eklenecekD icin alan olusturulamadi.(ekle)\nHata ");
            return;
        }
        eklenecekD->isim = calloc(strlen((char *)adi), sizeof *(eklenecekD->isim));
        if (!(eklenecekD->isim))
        {
            perror(" > eklenecekD->isim alan olusturulamadi.(ekle)\nHata ");
            return;
        }
        memmove(eklenecekD->isim, adi, strlen((char *)adi));
        eklenecekD->sayisi = sayisi;
        if (sirasi <= (dugumSayisi / 2))
        {
            geciciD = (*basDugum);
            for (uint32_t i = 1; i < sirasi; ++i, geciciD = geciciD->sonraki);
            //fprintf(stdout, "adi1: %s\n", geciciD->isim);
            eklenecekD->sonraki = geciciD;
            if (sirasi == 1)
            {
                eklenecekD->onceki = NULL;
                (*basDugum) = eklenecekD;
            }   else    {
                eklenecekD->onceki = geciciD->onceki;
                geciciD->onceki->sonraki = eklenecekD;
            }
            geciciD->onceki = eklenecekD;
            ++dugumSayisi;
            eklenecekD = NULL;
            geciciD = NULL;
            return;
        }
        else if (sirasi > (dugumSayisi / 2))
        {
            geciciD = (*kicDugum);
            for (uint32_t i = dugumSayisi + 1; i > sirasi; --i, geciciD = geciciD->onceki);
            //fprintf(stdout, "adi2: %s, %" PRIdLEAST32 ", istenen: %s\n", geciciD->isim, dugumSayisi, adi);
            eklenecekD->onceki = geciciD;
            if (sirasi == (dugumSayisi + 1))
            {
                eklenecekD->sonraki = NULL;
                (*kicDugum) = eklenecekD;
            }   else    {
                eklenecekD->sonraki = geciciD->sonraki;
                geciciD->sonraki->onceki = eklenecekD;
            }
            geciciD->sonraki = eklenecekD;
            ++dugumSayisi;
            eklenecekD = NULL;
            geciciD = NULL;
            return;
        }
        //fprintf(stdout, "#####################\n");
        return;
    }
    
}

void adaGoreSil(DUGUM_PTR *basDugum, DUGUM_PTR *kicDugum, uint8_t *adi)
{
    //fprintf(stdout, "%s\n", adi);
    if (!(*basDugum) || !(*kicDugum))
    {
        fprintf(stderr, " > basDugum yada kicDugumden biri kof.(adaGoreSil)\n");
        return;
    }
    if (memcmp(adi, " ", strlen((char *)adi)) == 0 || memcmp(adi, "", strlen((char *)adi)) == 0)
    {
        fprintf(stderr, " > girilen ad bosluk. silinemez!(adaGoreSil)\n");
        return;
    }
    //uint32_t uzunluk = (strlen((char *)(*basDugum)->isim) <= strlen((char *)adi) ? strlen((char *)adi) : strlen((char *)(*basDugum)->isim));
    //fprintf(stdout, "uzunluk: %" PRId32 ", basDugum->isim:%ld, adi: %ld\n", uzunluk, strlen((char *)(*basDugum)->isim), strlen((char *)adi));
    //memcmp((*basDugum)->isim, adi, uzunluk);
    if ((*basDugum) && (*kicDugum))
    {
        DUGUM_PTR geciciD = (*basDugum);
        DUGUM_PTR silinecek;
        uint64_t uzunluk = 0;
        uint32_t sayac = 0;
        uint64_t adU = strlen((char *)adi);
        //fprintf(stdout, "asd : %s, %ld\n", adi, strlen((char *)geciciD->isim));
        while (geciciD)
        {
            uzunluk = (strlen((char *)geciciD->isim) <= adU ) ? adU : strlen((char *)geciciD->isim);
            if (memcmp(geciciD->isim, adi, uzunluk) == 0)
            {
                ++sayac;
                silinecek = geciciD;
            }
            geciciD = geciciD->sonraki;
        }
        switch (sayac)
        {
        case 0:
            fprintf(stdout, " > %s adina sahip bir oge bulunamadi.(adaGoreSil)\n", adi);
            geciciD = NULL;
            silinecek = NULL;
            return;
        case 1:
            if (silinecek->onceki && silinecek->sonraki)
            {
                geciciD = silinecek->onceki;
                geciciD->sonraki = silinecek->sonraki;
                silinecek->sonraki->onceki = geciciD;
                silinecek->onceki = NULL;
                silinecek->sonraki = NULL;
                --dugumSayisi;
                free(silinecek->isim);
                free(silinecek);
                geciciD = NULL;
                return;
            }
            else if (!silinecek->onceki && silinecek->sonraki)
            {
                (*basDugum) = silinecek->sonraki;
                (*basDugum)->onceki = NULL;
                silinecek->sonraki = NULL;
                free(silinecek->isim);
                free(silinecek);
                --dugumSayisi;
                geciciD = NULL;
                return;
            }
            else if (silinecek->onceki && !silinecek->sonraki)
            {
                // fprintf(stdout, "aaa: %s ve %s\n", (*kicDugum)->isim, silinecek->isim);
                // return;
                (*kicDugum) = silinecek->onceki;
                (*kicDugum)->sonraki = NULL;
                silinecek->onceki = NULL;
                free(silinecek->isim);
                free(silinecek);
                --dugumSayisi;
                geciciD = NULL;
                return;
            }   else    {
                fprintf(stderr, "bas ve kic dugum cok farkli degerlerde hata anlasilamadi.(adaGoreSil)\n");
                return;
            }
            return;
        default:
            fprintf(stderr, " > ayni isimden (%s) %" PRIuLEAST32 " tane vardir. Siraya gore silin.(adaGoreSil)\n", silinecek->isim, sayac);
            geciciD = NULL;
            silinecek = NULL;
            return;
        }
    }
}

void sirayaGoreSil(DUGUM_PTR *basDugum, DUGUM_PTR *kicDugum, uint_least32_t sirasi)
{
    if (sirasi > dugumSayisi)
    {
        fprintf(stderr, " > girilen sira, dugumSayisindan fazla.(sirayaGoreSil)\n");
        return;
    }
    if (!(*basDugum) || !(*kicDugum))
    {
        fprintf(stderr, " > basDugum yada kicDugum'den biri kof.(sirayaGoreSil)\n");
        return;
    }
    if (sirasi == 0)
    {
        fprintf(stderr, "sirasi 0(sifir) olamaz.(sirayaGoreSil)\n");
        return;
    }
    if ((*basDugum) && (*kicDugum) && sirasi <= dugumSayisi && sirasi != 0)
    {
        DUGUM_PTR geciciD, silinecek;
        if (sirasi == 1)
        {
            silinecek = (*basDugum);
            (*basDugum) = silinecek->sonraki;
            (*basDugum)->onceki = NULL;
            silinecek->sonraki = NULL;
            free(silinecek->isim);
            free(silinecek);
            --dugumSayisi;
            return;
        }
        else if (sirasi == dugumSayisi)
        {
            silinecek = (*kicDugum);
            (*kicDugum) = silinecek->onceki;
            (*kicDugum)->sonraki = NULL;
            silinecek->onceki = NULL;
            free(silinecek->isim);
            free(silinecek);
            --dugumSayisi;
            return;
        }
        else if (sirasi <= (dugumSayisi / 2))
        {
            geciciD = (*basDugum);
            for (uint32_t i = 1; i < sirasi && geciciD != NULL; ++i, geciciD = geciciD->sonraki);
            
        }
        else if (sirasi > (dugumSayisi / 2))
        {
            geciciD = (*kicDugum);
            for (uint32_t i = dugumSayisi; i > sirasi && geciciD != NULL; --i, geciciD = geciciD->onceki);
        }
        silinecek = geciciD;
        fprintf(stdout, "bulunan1 %s, %" PRIuLEAST32 "\n", silinecek->isim, silinecek->sayisi);
        geciciD = silinecek->onceki;
        geciciD->sonraki = silinecek->sonraki;
        silinecek->sonraki->onceki = geciciD;
        silinecek->sonraki = NULL;
        silinecek->onceki = NULL;
        --dugumSayisi;
        return;
    }
}

void adaGoreBul(DUGUM_PTR *basDugum, DUGUM_PTR *kicDugum, uint8_t *adi) 
{
    if (!(*basDugum) || !(*kicDugum))
    {
        fprintf(stderr, "basDugum yada kicDugum kof!(adaGoreBul)\n");
        return;
    }
    if (memcmp(adi, "", strlen((char *)adi)) == 0 || memcmp(adi, " ", strlen((char *)adi)) == 0)
    {
        fprintf(stderr, "aranacak olan ad bos.(adaGoreBul)\n");
        return;
    }
    DUGUM_PTR bas = (*basDugum), kic = (*kicDugum);
    uint32_t basSayac = 1, kicSayac = dugumSayisi;
    while (bas && kic)
    {
        if (bas != kic && bas)
        {
            if (memcmp(bas->isim, adi, ((strlen((char *)adi) <= strlen((char *)bas->isim)) ? strlen((char *)bas->isim) : strlen((char *)adi))) == 0)
            {
                fprintf(stdout, "ada gore aranan adi: %s, sayisi: %" PRIdLEAST32 ", sirasi: %" PRIu32 "\n", bas->isim, bas->sayisi, basSayac);
            }
            bas = bas->sonraki;
            ++basSayac;
        }
        if (basSayac == kicSayac)
            return;
        if (kic)
        {
            if (memcmp(kic->isim, adi, ((strlen((char *)adi) <= strlen((char *)kic->isim)) ? strlen((char *)kic->isim) : strlen((char *)adi))) == 0)
            {
                fprintf(stdout, "ada gore aranan adi: %s, sayisi: %" PRIdLEAST32 ", sirasi: %" PRIu32 "\n", kic->isim, kic->sayisi, kicSayac);
            }
            kic = kic->onceki;
            --kicSayac;
        }
        
    }
    return;
}

void sirayaGoreBul(DUGUM_PTR *basDugum, DUGUM_PTR *kicDugum, uint_least32_t sirasi) 
{
    if (!(*basDugum) || !(*kicDugum))
    {
        fprintf(stderr, "basDugum yada kicDugum kof!(adaGoreBul)\n");
        return;
    }
    if (sirasi > dugumSayisi || sirasi == 0)
    {
        fprintf(stderr, " > girilen sira sayisi kabul edilemez.(sirayaGoreBul)\n");
        return;
    }
    if (sirasi <= dugumSayisi)
    {
        if (sirasi <= (dugumSayisi / 2))
        {
            DUGUM_PTR geciciD = (*basDugum);
            for (uint32_t i = 1; i < sirasi && geciciD; ++i, geciciD = geciciD->sonraki);
            fprintf(stdout, "siraya gore bulunan adi: %s, sayisi: %" PRIdLEAST32 "\n", geciciD->isim, geciciD->sayisi);
            geciciD = NULL;
            return;
        }
        else if (sirasi > (dugumSayisi / 2))
        {
            DUGUM_PTR geciciD = (*kicDugum);
            for (uint32_t i = dugumSayisi; i > sirasi && geciciD; --i, geciciD = geciciD->onceki);
            fprintf(stdout, "siraya gore bulunan adi: %s, sayisi: %" PRIdLEAST32 "\n", geciciD->isim, geciciD->sayisi);
            geciciD = NULL;
            return;
        }
    }   else    {
        fprintf(stdout, "bu nasil hata lan! hic bir sey olmasada kesin bir sey olmus!\n");
        return;
    }
}
/*
                YAPILACAKLAR
    -   ##-BİTTİ-##     başlı, kıçlı yaptık ama kıçı kullanmadım. Düzeltilecek!
    -   ##-BİTTİ-##     ekleme işi girilen sayıya göre yapılacak! başa, kıça, arasına
    -   ##-BİTTİ-##     silme işi ada ve sıraya göre olacak
    -   ##-BİTTİ-##     bulma işlemi ada ve sıraya göre olacak
*/