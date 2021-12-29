//  Bunları 31ll_linkedList.c nin içine yapıştırırsanız çalışır.

void tersle(DUGUM_PTR *);

void tersle(DUGUM_PTR *basDugum) 
{
    if (!(*basDugum))
    {
        fprintf(stderr, "dugum kof.(tersle)\n");
        return;
    }
    if(((*basDugum)->siradaki))
    {
        DUGUM_PTR birinciD = (*basDugum), ikinciD = birinciD->siradaki;
        while (ikinciD)
        {
            DUGUM_PTR geciciD = ikinciD->siradaki;
            ikinciD->siradaki = birinciD;
            birinciD = ikinciD;
            ikinciD = geciciD;
        }
        (*basDugum)->siradaki = NULL;
        (*basDugum) = birinciD;
    }
}
