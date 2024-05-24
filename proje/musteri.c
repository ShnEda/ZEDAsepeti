#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "musteri.h"

//#define MAX_UZUNLUK 30

//musteri yeniKullanici, kullaniciGiris, mevcutKullanici, yemek, siparis, kontrol;

//int siparisID = 0;

//int musteriUygulamasi(){
//    int secim;
//    printf("\n\t     **MUSTERI UYGULAMASI**\n\n");
//    printf("\t 1 - KAYIT OL \n");
//    printf("\t 2 - OTURUM AC \n");
//    printf("\t 0 - PROGRAMI KAPAT \n\n");
//    printf("\t Seciminiz     : ");
//    scanf("%d", &secim);
//    system("cls");
//    return secim;
//}

//int musteriEkrani() {
//    int secim2;
//    printf("\n\t     **MUSTERI EKRANI**\n\n");
//    printf("\t 1 - YENI SIPARIS \n");
//   printf("\t 2 - MEVCUT SIPARIS DURUMLARI \n");
//    printf("\t 3 - DAHA ONCEKI SIPARISLERIM \n");
//    printf("\t 0 - MUSTERI UYGULAMASINA DON \n\n");
//    printf("\t Seciminiz     : ");
//    scanf("%d",&secim2);
//    system("cls");
//    return secim2;
//}

//void kayitOl() {
//    printf("Kayit Olma Ekrani..\n\n");
//    printf("Yeni kullanici adinizi giriniz: ");
//    scanf(" %[^\n]s", yeniKullanici.kullaniciAdi);
//    printf("Yeni sifrenizi giriniz: ");
//    scanf(" %[^\n]s", yeniKullanici.sifre);
//
//    FILE* kullanicilartxt = fopen("kullanicilar.txt", "a");
//
//    fprintf(kullanicilartxt, "%s\t%s\n", yeniKullanici.kullaniciAdi, yeniKullanici.sifre);
//    fclose(kullanicilartxt);
//    printf("\nKaydiniz  basarili..\n\n");
//    printf("Musteri uygulamasina donmek icin bir tusa basiniz..");
//    getch();
//    system("cls");
//}
//
//int oturumAc() {
//    printf("Oturum Acma Ekrani..\n\n");
//    printf("Mevcut kullanici adinizi giriniz: ");
//    scanf(" %[^\n]s", kullaniciGiris.kullaniciAdi);
//    printf("Mevcut sifrenizi giriniz: ");
//    scanf(" %[^\n]s", kullaniciGiris.sifre);
//
//    FILE* kullanicilartxt = fopen("kullanicilar.txt", "r");
//    if (kullanicilartxt == NULL) {
//        printf("kullanicilar.txt mevcut degil!!\n");
//        return 0;
//    }
//
//    while (fscanf(kullanicilartxt, " %[^\t] %[^\n]", mevcutKullanici.kullaniciAdi, mevcutKullanici.sifre) == 2) {
//        if (strcmp(kullaniciGiris.kullaniciAdi, mevcutKullanici.kullaniciAdi) == 0 &&
//            strcmp(kullaniciGiris.sifre, mevcutKullanici.sifre) == 0) {
//            siparisID++; //kullanici her degistiginde artiyor
//            fclose(kullanicilartxt);
//            printf("\nGirisiniz basarili..\n\n");
//            printf("Musteri ekranina gitmek icin bir tusa basiniz..");
//            getch();
//            system("cls");
//            return 1;
//        }
//    }
//
//    fclose(kullanicilartxt);
//    return 0;
//}

void yemekleriListele()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi bulunamadi!\n");
        return;
    }

    struct Yemek yemek; //benim kodda bu kısma gerek kalmıyo

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
    //üstteki 3 satırı silebiliriz benim koda göre
    //siparis.ID = siparisID;

    printf("\n\nYemek ID'sini giriniz: ");
    scanf("%d", &siparis.yemekID);
    
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi dosyasi acilamadi!\n");
        fclose(siparislertxt);
        return;
    }

    kontrol.yemekBuldu = 0;
    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &kontrol.yemekID, kontrol.yemekAdi, &kontrol.fiyat, &kontrol.hazirlama_suresi, kontrol.durum) == 5) {
        if (kontrol.yemekID == siparis.yemekID) {
            static int siparisID = 1; //siparis ID'si ayarlaniyor
            siparis.id = siparisID++;
            //üstteki 2 satıra gerek yok benim kodda
            siparis.yemekID = kontrol.yemekID;
            strcpy(siparis.yemekAdi, kontrol.yemekAdi);
            siparis.fiyat = kontrol.fiyat;
            siparis.hazirlama_suresi = kontrol.hazirlama_suresi;
            kontrol.yemekBuldu = 1;
            break;
        }
    }
    fclose(yemeklistesitxt);

    if (kontrol.yemekBuldu == 0) {
        printf("\n%d ID'li yemek yemeklistesi.txt dosyasinda bulunamadi!\n", siparis.yemekID);
        fclose(siparislertxt);
        return siparisAl();
    }


    // siparis zamani (bu kısımlar benim koddan yorumdakiler açılınca olacak)
    siparis.siparisTarihi = time(NULL);
    struct tm *siparisZamaniYapisi = localtime(&siparis.siparisTarihi);
    char siparisZamaniStr[100];
    strftime(siparisZamaniStr, sizeof(siparisZamaniStr), "%m/%d/%Y %H:%M:%S", siparisZamaniYapisi);

    // hazir olma zamani (bu kısımlar benim koddan yorumdakiler açılınca olacak)
    siparis.hazirOlmaZamani = siparis.siparisTarihi + (siparis.hazirlama_suresi * 60); // dakika cinsinden süreyi saniyeye çevir
    struct tm *hazirOlmaZamaniYapisi = localtime(&siparis.hazirOlmaZamani);
    char hazirOlmaZamaniStr[100];
    strftime(hazirOlmaZamaniStr, sizeof(hazirOlmaZamaniStr), "%m/%d/%Y %H:%M:%S", hazirOlmaZamaniYapisi);

    fprintf(siparislertxt, "\nSP_%d\t\t%s\t\t%.2f TL    \t%s\t\t%s", siparis.id, siparis.yemekAdi, siparis.fiyat, siparisZamaniStr, hazirOlmaZamaniStr);
    printf("Siparis basariyla alindi ve kaydedildi!\n");
    //fprintf(siparislertxt, "SP_%d\t%s\t%d\t%s\t%s\t\t%s\n", siparis.ID, siparis.yemekAdi, siparis.fiyat, siparisZamaniStr, hazirOlmaZamaniStr, mevcutKullanici.kullaniciAdi);
    //printf("Siparis alindi!!\n");

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
    static int klncID = 1; //klnc ID'si ayarlaniyor
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


void yeniSiparis() //burası da benim kod
{
    char devam;

    yemekleriListele();

    do {
        siparisAl();
        printf("\nSiparise devam edecekseniz (E/e) tuslayiniz: ");
        scanf(" %c", &devam);
    } while (devam == 'E' || devam == 'e');

    printf("\nSiparis isleminiz sona erdi..\n");
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
    return satirSira;
}
