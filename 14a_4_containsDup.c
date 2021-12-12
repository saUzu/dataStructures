/*  ------------------------------------------------------------------- */
/*  ------------------------------------------------------------------- */
//
//      Tarih : 7/12/2021
//      Yazan : saUzu
//      Derlemek için : gcc 14a_4_containsDup.c -o 14a_4_containsDup
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

#define DIZIUZUNLUGU 10

typedef struct Oge
{
    int deger;
    int sayac;
    struct Oge *siradaki;
} OGE, *OGE_PTR;

void benzeriVarMi(int *);
void ogeleriAta(OGE_PTR, int *);

int main(int argc, char **argv)
{
    //int *dizi = malloc(-1);
    int *dizi = malloc(sizeof(int) * DIZIUZUNLUGU);
    if (dizi == NULL)
    {
        perror("dizi icin yapilan mallocta hata oldu.\nHata");
        goto cikis;
    }
    dizi[0] = 4;
    dizi[1] = -8564;
    dizi[2] = 7;
    dizi[3] = 3;
    dizi[4] = 1;
    dizi[5] = -5;
    dizi[6] = 11;
    dizi[7] = -245;
    dizi[8] = 7;
    dizi[9] = 8564;

    benzeriVarMi(dizi);

cikis:
    free(dizi);
    dizi = NULL;
    if(dizi == NULL)
        fprintf(stdout, "dizi koflandi!\n");
    return 0;
}

void ogeleriAta(OGE_PTR ogeDizisi, int *dizi)
{
    int modu;
    for (int i = 0; i < 1000; i++)
    {
        ogeDizisi[i].siradaki = NULL;
    }
    ogeDizisi[0].deger = 31;
    ogeDizisi[0].sayac = 13;
    OGE_PTR oge = &ogeDizisi[0];
    /* fprintf(stdout, "%p\n%p\n\n", ogeDizisi[0], oge);
    fprintf(stdout, "%p\n%p\n\n", &ogeDizisi[0], *oge);

    fprintf(stdout, "%d %d\n\n", oge->deger, oge->sayac); */

    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        modu = dizi[i] % 1000;
        if (modu < 0)
            modu *= (-1);
        //fprintf(stdout, "%d %d, ", dizi[i], modu);
        OGE_PTR geciciOge = &ogeDizisi[modu];

        OGE_PTR oge = malloc(sizeof(struct Oge));
        oge->deger = dizi[i];
        oge->sayac = 1;
        oge->siradaki = NULL;
        //fprintf(stdout, " |%d| ", oge->deger);
        while(1)
        {
            if (geciciOge->siradaki == NULL)
            {
                geciciOge->siradaki = oge;
                break;
            }
            else
            {   
                geciciOge = geciciOge->siradaki;
                if (geciciOge->deger == dizi[i])
                {
                    (geciciOge->sayac)++;
                    break;
                }
            }
        }
        //fprintf(stdout, "a:%d %d %d, ", ogeDizisi[modu].deger, ogeDizisi[modu].sayac, geciciOge->deger);
    }

    //fprintf(stdout, "\n\n%d %d\n\n", ogeDizisi[564].siradaki->siradaki->deger, ogeDizisi[564].siradaki->siradaki->sayac);

    //fprintf(stdout, "\n------------------- \n");
    for (int i = 0; i < DIZIUZUNLUGU; i++)
    {
        modu = dizi[i] % 1000;
        if (modu < 0)
            modu *= (-1);
        OGE_PTR geciciOge = &ogeDizisi[modu];
        while (geciciOge->siradaki != NULL)
        {
            geciciOge = geciciOge->siradaki;
            //fprintf(stdout, "%d %d, ",geciciOge->deger, geciciOge->sayac);
        }
        //free(geciciOge);
        //fprintf(stdout, "\n");
    }
    //fprintf(stdout, "\nqwerty \n");


}

void benzeriVarMi(int *dizi)
{
    OGE_PTR ogeDizisi = malloc(sizeof(struct Oge) * 1000);
    ogeleriAta(ogeDizisi, dizi);
    for (int i = 0; i < 1000; i++)
    {
        OGE_PTR geciciOge = &ogeDizisi[i];
        while (geciciOge->siradaki != NULL)
        {
            geciciOge = geciciOge->siradaki;
            if(geciciOge->sayac>1)
                fprintf(stdout, "BURASI IKI\n\n");
            fprintf(stdout, "i: %d deger: %d sayac: %d ||", i, geciciOge->deger, geciciOge->sayac);
            if(geciciOge->siradaki == NULL)
                fprintf(stdout, "\n");
        }
    }

    free(ogeDizisi);
    ogeDizisi = NULL;
    if (ogeDizisi == NULL)
        fprintf(stdout, "ogeDizisi koflandi!\n");
}