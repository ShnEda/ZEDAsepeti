#include <stdio.h>
#include <stdlib.h>

int menu() {
    int secim;
    printf("\n\t     **MUSTERI EKRANI**\n\n");
    printf("\t 1 - YENI SIPARIS \n");
    printf("\t 2 - MEVCUT SIPARIS DURUMLARI \n");
    printf("\t 3 - DAHA ONCEKI SIPARISLERIM \n");
    printf("\t 0 - PROGRAMI KAPAT \n\n");
    printf("\t Seciminiz     : ");
    scanf("%d",&secim);
    system("cls");
    return secim;
}

int main()
{
    // Buraya kullanici giris ekrani gelecek; oturum ac, giris yap gibi. + cikis yapmak istediginde yes no olabilir.
    int secim = menu();
    while(secim!=0) {
        switch(secim) {

            case 1: yeniSiparis(); break;
            case 2: mevcutSiparis(); break;
            case 3: oncekiSiparis(); break;
            case 0: break;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim = menu();
    }


    return 0;
}
