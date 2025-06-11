#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "mutfak.h"


int menu() {
    int secim;
    printf("\n\t     **MUTFAK EKRANI**\n\n");
    printf("\t 1 - OTOMATIK YEMEK GUNCELLE \n");
    printf("\t 2 - ATANMIS YEMEK LISTELE \n");
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

            case 1: otomatikYemekGuncelle(); break;
            case 2: atanmisYemekListele(); break;
            case 0: break;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim = menu();
    }

    return 0;
}
