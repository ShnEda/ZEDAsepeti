#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "musteri.h"

int main() {

    int secim = musteriUygulamasi();
    while (secim!=0) {
        switch (secim) {
            case 1: kayitOl(); break;
            case 2:
                if (oturumAc()) {
                    int secim2 = musteriEkrani();
                    while(secim2!=0) {
                        switch(secim2) {
                            case 1: yeniSiparis(); break;
                            case 2: mevcutSiparis(); break;
                            case 3: oncekiSiparis(); break;
                            case 0: return musteriUygulamasi(); break;
                            default: printf("\nhatali secim yaptiniz ! \n"); break;
                        }
                        secim2 = musteriEkrani();
                    }
                }
                else {
                    printf("\nkullanici adi veya sifre hatali!!\n");
                    printf("\nAna menuye donmek icin bir tusa basiniz..");
                    getch();
                    system("cls");
                }

                break;
            case 0: return 0;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim = musteriUygulamasi();
    }

    return 0;
}
