#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "musteri.h"

void yemekleriListele()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi bulunamadi!\n");
        return 0;
    }

    printf("\tYemek Adi\t\t\tFiyati\t\tHazirlama Suresi (dk)\n");
    printf("\t---------\t\t\t------\t\t---------------------\n");
    while (fscanf(yemeklistesitxt," %[^\t] %f %d %[^\n]", yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlama_suresi, yemek.durum) == 4) {
        if (strcmp(yemek.durum, "Mevcut") == 0) { //yemek.durum ile "Mevcut" yazisini karsilasitiriyor. ayni ise 0 donduruyor.
            printf("\t%s\t\t\t%.2f TL\t\t%d dk\n", yemek.yemekAdi, yemek.fiyat, yemek.hazirlama_suresi);
        }
    }

    fclose(yemeklistesitxt);
}

void siparisAl()
{
    FILE* siparislertxt = fopen("siparisler.txt", "a");
    if (siparislertxt == NULL) {
        printf("Siparis dosyasi acilamadi!\n");
        return 0;
    }

    static int siparisID = 1; //siparis ID'si ayarlaniyor
    siparis.id = siparisID++;

    printf("\n\nYemek adini giriniz: ");
    scanf(" %[^\n]s", siparis.yemekAdi);


    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi dosyasi acilamadi!\n");
        fclose(siparislertxt);
        return 0;
    }

    kontrol.yemekBuldu = 0;
    while (fgets(kontrol.satir, sizeof(kontrol.satir), yemeklistesitxt)) {
        sscanf(kontrol.satir, " %[^\t] %f %d", kontrol.yemekAdi, &kontrol.fiyat, &kontrol.hazirlanmaSuresi);
        if (strncmp(siparis.yemekAdi, kontrol.yemekAdi, sizeof(siparis.yemekAdi)) == 0) {
            static int siparisID = 1; //siparis ID'si ayarlaniyor
            siparis.id = siparisID++;
            kontrol.yemekBuldu = 1;
            siparis.fiyat = kontrol.fiyat;
            siparis.hazirlanmaSuresi = kontrol.hazirlanmaSuresi;
            break;
        }
    }
    fclose(yemeklistesitxt);


    if (!kontrol.yemekBuldu) {
        printf("\nHATA: %s yemegi yemeklistesi.txt dosyasinda bulunamadi!\n", siparis.yemekAdi);
        fclose(siparislertxt);
        return siparisAl();
    }

    siparis.siparisTarihi = time(NULL); //siparis tarihi

    //siparisin ne zaman hazir olacagi
    time_t hazirOlmaZamani = siparis.siparisTarihi + (siparis.hazirlanmaSuresi * 60); // dakika cinsinden sureyi saniyeye cevir
    struct tm *hazirOlmaZamaniYapisi = localtime(&hazirOlmaZamani);
    char hazirOlmaZamaniStr[100];
    strftime(hazirOlmaZamaniStr, sizeof(hazirOlmaZamaniStr), "%c", hazirOlmaZamaniYapisi);
    char *siparisZamaniStr = ctime(&siparis.siparisTarihi);
    siparisZamaniStr[strlen(siparisZamaniStr) - 1] = '\0';


    fprintf(siparislertxt, "\nSP_%d\t\t\t%s\t\t\t%.2f TL\t\t\t%s\t\t\t%s", siparis.id, siparis.yemekAdi, siparis.fiyat, siparisZamaniStr, hazirOlmaZamaniStr);
    printf("Siparis basariyla alindi ve kaydedildi!\n");

    fclose(siparislertxt);
}

void yeniSiparis()
{
    yemekleriListele();
    siparisAl();
    printf("\nAna menuye donmek icin bir tusa basiniz..");
    getch();
    system("cls");
}

void mevcutSiparis()
{

}

void oncekiSiparis()
{

}
