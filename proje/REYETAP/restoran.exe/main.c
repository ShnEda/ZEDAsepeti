#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "restoran.h"

int menu() {
    int secim;
    printf("\n\t     **RESTORAN EKRANI**\n\n");
    printf("\t 1 - YEMEKLERI LISTELE \n");
    printf("\t 2 - YEMEK EKLEME \n");
    printf("\t 3 - YEMEK GUNCELLEME \n");
    printf("\t 4 - YEMEK SILME \n");
    printf("\t 5 - YENI SIPARIS ONAY/RED \n");
    printf("\t 6 - GUNLUK RAPOR GORUNTULEME \n");
    printf("\t 7 - ANALIZLER \n");
    printf("\t 8 - ASCI SAYISI BELIRLEME \n");
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
            case 1: printf("Yemek Listesi..\n\n"); yemekleriListele();
                    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
                    getch();
                    system("cls");
                    break;
            case 2: yemekEkleme(); break;
            case 3: yemekGuncelleme(); break;
            case 4: yemekSilme(); break;
            case 5: onay_red(); break;
            case 6: gunlukRapor(); break;
            case 7: analizler(); break;
            case 8: asciSayisiBelirleme(); break;
            case 0: break;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim = menu();
    }
    return 0;
}
