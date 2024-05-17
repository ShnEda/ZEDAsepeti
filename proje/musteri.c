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
        return;
    }

    struct Yemek yemek;

    printf("ID\tYemek Adi\tFiyati\t\tHazirlama Suresi (dk)\n");
    printf("--\t---------\t------\t\t---------------------\n");
    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &yemek.ID, yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlama_suresi, yemek.durum) == 5) {
        if (strcmp(yemek.durum, "Mevcut") == 0) {
            printf("%d\t%s\t%.2f TL\t\t%d dk\n", yemek.ID, yemek.yemekAdi, yemek.fiyat, yemek.hazirlama_suresi);
        }
    }
    fclose(yemeklistesitxt);
}



void siparisAl()
{
    FILE* siparislertxt = fopen("siparisler.txt", "a");
    if (siparislertxt == NULL) {
        printf("Siparis dosyasi acilamadi!\n");
        return;
    }

    struct Siparis siparis;
    static int siparisID = 1; //siparis ID'si ayarlaniyor
    siparis.id = siparisID++;

    printf("\n\nYemek ID'sini giriniz: ");
    scanf("%d", &siparis.yemekID);


    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi dosyasi acilamadi!\n");
        fclose(siparislertxt);
        return;
    }

    kontrol.yemekBuldu = 0;
    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &kontrol.yemekID, kontrol.yemekAdi, &kontrol.fiyat, &kontrol.hazirlama_suresi, kontrol.durum) != EOF) {
        if (kontrol.yemekID == siparis.yemekID) {
            static int siparisID = 1; //siparis ID'si ayarlaniyor
            siparis.id = siparisID++;
            siparis.yemekID = kontrol.yemekID;
            strcpy(siparis.yemekAdi, kontrol.yemekAdi);
            siparis.fiyat = kontrol.fiyat;
            siparis.hazirlama_suresi = kontrol.hazirlama_suresi;
            kontrol.yemekBuldu = 1;
            break;
        }
    }
    fclose(yemeklistesitxt);


    if (!kontrol.yemekBuldu) {
        printf("\nHATA: Yemek ID'si %d olan yemek yemeklistesi.txt dosyasinda bulunamadi!\n", siparis.yemekID);
        fclose(siparislertxt);
        return siparisAl();
    }


    siparis.siparisTarihi = time(NULL); //siparis tarihi

    //siparisin ne zaman hazir olacagi
    time_t hazirOlmaZamani = siparis.siparisTarihi + (siparis.hazirlama_suresi * 60); // dakika cinsinden sureyi saniyeye cevir
    struct tm *hazirOlmaZamaniYapisi = localtime(&hazirOlmaZamani);
    char hazirOlmaZamaniStr[100];
    strftime(hazirOlmaZamaniStr, sizeof(hazirOlmaZamaniStr), "%c", hazirOlmaZamaniYapisi);
    char *siparisZamaniStr = ctime(&siparis.siparisTarihi);
    siparisZamaniStr[strlen(siparisZamaniStr) - 1] = '\0';


    fprintf(siparislertxt, "\nSP_%d\t\t%s\t\t%.2f TL    \t%s\t\t%s", siparis.id, siparis.yemekAdi, siparis.fiyat, siparisZamaniStr, hazirOlmaZamaniStr);
    printf("Siparis basariyla alindi ve kaydedildi!\n");

    fclose(siparislertxt);
}

void kullaniciKaydet(struct Kullanici kullanici)
{
    FILE* kullanicilarTxt = fopen("kullanicilar.txt", "w");
    if (kullanicilarTxt == NULL) {
        printf("Kullanicilar bulunamadi.");
        return;
    }
    fprintf(kullanicilarTxt, "%s %s", kullanici.kulAdi, kullanici.sifre);
    fclose(kullanicilarTxt);
}

void kullaniciGiris()
{
    FILE* klnclarTXT = fopen("kullanicilar.txt", "r");
    if (klnclarTXT == NULL) {
        printf("Kullanici dosyasi acilamadi!\n");
        fclose(klnclarTXT);
        return;
    }

    struct Kullanici klnc;
    static int klncID = 1; //siparis ID'si ayarlaniyor
    klnc.id = klncID++;

    printf("\n\nKullanici ID'sini giriniz: ");
    scanf("%d", &klnc.klncID);

    kullanici.kulBuldu = 0;//Duzenlemek gerekiyor, header'da bazi eklemeler yapilmali
    while (fscanf(klnclarTXT, "%d %[^\t]", &kullanici.klncID, kullanici.klncAdi) != EOF) {
        if (kullanici.klncID == klnc.klncID) {
            static int siparisID = 1; //kul ID'si ayarlaniyor
            klnc.id = siparisID++;
            klnc.klncID = kullanici.klncID;
            strcpy(klnc.klncAdi, kullanici.klncAdi);
            kullanici.kulBuldu = 1;
            break;
        }
    }

    fclose(klnclarTXT);
    if (!kullanici.kulBuldu) {
        printf("\nHATA: Kullanici ID'si bulunamadi!\n");
        fclose(klnclarTXT);
        return kullaniciGiris();
    }
}

void yeniKullanici(struct Kullanici *klnclar)
{
    int topKullanici = dosyaSatirSayi("kullanicilar.txt");
    printf("Kullanici Adi: ");
    scanf("%s", klnclar[topKullanici].kulAdi);//buradaki scanfler fscanf degildir diye dusunuyorum??
    printf("Sifreniz: ");
    scanf("%s", klnclar[topKullanici].sifre);

    kullaniciKaydet(klnclar[topKullanici]);
    (topKullanici)++;
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

int dosyaSatirSayi(const char *dosyaTXT)
{
    int satirSira=0;
    FILE *dosyamiz = fopen(dosyaTXT, "r");
    while (!feof(dosyamiz))
    {
        if (fgetc(dosyamiz) == '\n')
            satirSira++;
    }
    fclose(dosyamiz);
    return satirSira;
}