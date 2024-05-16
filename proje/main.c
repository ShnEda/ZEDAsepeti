#include <stdio.h>
#include <stdlib.h>

int menu() {
    int secim;
    printf("\n\t     **RESTORAN EKRANI**\n\n");
    printf("\t 1 - YEMEK EKLEME \n");
    printf("\t 2 - YEMEK GUNCELLEME \n");
    printf("\t 3 - YEMEK SILME \n");
    printf("\t 4 - YENI SIPARIS ONAY/RED \n");
    printf("\t 5 - GUNLUK RAPOR GORUNTULEME \n");
    printf("\t 6 - ANALIZLER \n");
    printf("\t 7 - ASCI SAYISI BELIRLEME \n");
    printf("\t 0 - PROGRAMI KAPAT \n\n");
    printf("\t Seciminiz     : ");
    scanf("%d",&secim);
    system("cls");
    return secim;
}

int main() {

    int secim = menu();
    while(secim!=0) {
        switch(secim) {

            case 1: yemekEkleme(); break;
            case 2: yemekGuncelleme(); break;
            case 3: yemekSilme(); break;
            case 4: onay_red(); break;
            case 5: gunlukRapor(); break;
            case 6: analizler(); break;
            case 7: asciSayisiBelirleme(); break;
            case 0: break;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim = menu();
    }


    return 0;
}
