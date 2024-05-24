#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "musteri.h"

musteri yeniKullanici, kullaniciGiris, mevcutKullanici, yemek, siparis, kontrol;

int siparisID = 0; //siparis ID'sini ayarliyor

int musteriUygulamasi(){
    int secim;
    printf("\n\t     **MUSTERI UYGULAMASI**\n\n");
    printf("\t 1 - KAYIT OL \n");
    printf("\t 2 - OTURUM AC \n");
    printf("\t 0 - PROGRAMI KAPAT \n\n");
    printf("\t Seciminiz     : ");
    scanf("%d", &secim);
    system("cls");
    return secim;
}

int musteriEkrani() {
    int secim2;
    printf("%s isimli kullanici hesabi..\n",mevcutKullanici.kullaniciAdi);
    printf("\n\t     **MUSTERI EKRANI**\n\n");
    printf("\t 1 - YENI SIPARIS \n");
    printf("\t 2 - MEVCUT SIPARIS DURUMLARI \n");
    printf("\t 3 - DAHA ONCEKI SIPARISLERIM \n");
    printf("\t 0 - MUSTERI UYGULAMASINA DON \n\n");
    printf("\t Seciminiz     : ");
    scanf("%d",&secim2);
    system("cls");
    return secim2;
}

void kayitOl() {
    printf("Kayit Olma Ekrani..\n\n");
    printf("Yeni kullanici adinizi giriniz (max 15 karakter): ");
    scanf("%s", yeniKullanici.kullaniciAdi);
    printf("Yeni sifrenizi giriniz (max 8 karakter): ");
    scanf(" %[^\n]s", yeniKullanici.sifre);

    FILE* kullanicilartxt = fopen("kullanicilar.txt", "a");

    fprintf(kullanicilartxt, "%s\t%s\n", yeniKullanici.kullaniciAdi, yeniKullanici.sifre);
    fclose(kullanicilartxt);
    printf("\nKaydiniz  basarili..\n\n");
    printf("Musteri uygulamasina donmek icin bir tusa basiniz..");
    getch();
    system("cls");
}

int oturumAc() {
    printf("Oturum Acma Ekrani..\n\n");
    printf("Mevcut kullanici adinizi giriniz: ");
    scanf("%s", kullaniciGiris.kullaniciAdi);
    printf("Mevcut sifrenizi giriniz: ");
    scanf(" %[^\n]s", kullaniciGiris.sifre);

    FILE* kullanicilartxt = fopen("kullanicilar.txt", "r");
    if (kullanicilartxt == NULL) {
        printf("kullanicilar.txt mevcut degil!!\n");
        return 0;
    }

    while (fscanf(kullanicilartxt, " %[^\t] %[^\n]", mevcutKullanici.kullaniciAdi, mevcutKullanici.sifre) == 2) {
        if (strcmp(kullaniciGiris.kullaniciAdi, mevcutKullanici.kullaniciAdi) == 0 &&
            strcmp(kullaniciGiris.sifre, mevcutKullanici.sifre) == 0) {
            siparisID++; //kullanici her degistiginde artiyor
            fclose(kullanicilartxt);
            printf("\n%s isimli kullanici girisi basarili..\n\n",mevcutKullanici.kullaniciAdi);
            printf("Musteri ekranina gitmek icin bir tusa basiniz..");
            getch();
            system("cls");
            return 1;
        }
    }

    fclose(kullanicilartxt);
    return 0;
}

void yemekleriListele()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
        return;
    }

    printf("ID\tYemek Adi\t\tFiyati\t\tHazirlama Suresi (dk)\n");
    printf("--\t---------\t\t------\t\t---------------------\n");
    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemek.ID, yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlama_suresi, yemek.durum) == 5) {
        if (strcmp(yemek.durum, "Mevcut") == 0) {
            printf("%d\t%s\t\t%d TL\t\t\t%d dk\n", yemek.ID, yemek.yemekAdi, yemek.fiyat, yemek.hazirlama_suresi);
        }
    }
    fclose(yemeklistesitxt);
}

void siparisAl()
{
    FILE* siparislertxt = fopen("siparisler.txt", "a");

    siparis.ID = siparisID;

    printf("\n\nYemek ID'sini giriniz: ");
    scanf("%d", &siparis.yemekID);

    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
        fclose(siparislertxt);
        return;
    }

    kontrol.yemekBuldu = 0;
    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &kontrol.yemekID, kontrol.yemekAdi, &kontrol.fiyat, &kontrol.hazirlama_suresi, kontrol.durum) == 5) {
        if (kontrol.yemekID == siparis.yemekID) {
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

    // siparis zamani
    siparis.siparisTarihi = time(NULL);
    struct tm *siparisZamaniYapisi = localtime(&siparis.siparisTarihi);
    char siparisZamaniStr[100];
    strftime(siparisZamaniStr, sizeof(siparisZamaniStr), "%m/%d/%Y %H:%M:%S", siparisZamaniYapisi);

    // hazir olma zamani
    siparis.hazirOlmaZamani = siparis.siparisTarihi + (siparis.hazirlama_suresi * 60); // dakika cinsinden süreyi saniyeye çevir
    struct tm *hazirOlmaZamaniYapisi = localtime(&siparis.hazirOlmaZamani);
    char hazirOlmaZamaniStr[100];
    strftime(hazirOlmaZamaniStr, sizeof(hazirOlmaZamaniStr), "%m/%d/%Y %H:%M:%S", hazirOlmaZamaniYapisi);

    fprintf(siparislertxt, "SP_%d\t%s\t%d\t%s\t%s\t\t%s\n", siparis.ID, siparis.yemekAdi, siparis.fiyat, siparisZamaniStr, hazirOlmaZamaniStr, mevcutKullanici.kullaniciAdi);
    printf("Siparis alindi!!\n");

    fclose(siparislertxt);
}

void yeniSiparis()
{
    char devam;
    printf("Yeni Siparis ekrani..\n\n");

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
    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    printf("Mevcut Siparis ekrani..\n\n");
    printf("ID\tYemek Adi\t\tFiyat\t\tKalan Sure\tKullanici Adi\n");
    printf("--\t---------\t\t-----\t\t----------\t-------------\n");

    time_t simdiki_zaman;
    time(&simdiki_zaman);

    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.sipID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazZamani, siparis.kullaniciAdi) == 6 ) {
        if(strcmp(kullaniciGiris.kullaniciAdi, siparis.kullaniciAdi) == 0) {
            struct tm hazir_zamani;
            sscanf(siparis.hazZamani, "%d/%d/%d %d:%d:%d", &hazir_zamani.tm_mon, &hazir_zamani.tm_mday, &hazir_zamani.tm_year, &hazir_zamani.tm_hour, &hazir_zamani.tm_min, &hazir_zamani.tm_sec);

            // tm_mon 0-11 aralığında olduğu için 1 eksiltiyoruz
            hazir_zamani.tm_mon -= 1;
            hazir_zamani.tm_year -= 1900;

            time_t hazir_zamani_t = mktime(&hazir_zamani);

            if (hazir_zamani_t > simdiki_zaman) {
                int kalanSure = (hazir_zamani_t - simdiki_zaman) / 60;
                printf("%s\t%s\t\t%d TL\t\t%d dk\t\t%s\n",siparis.sipID, siparis.yemekAdi, siparis.fiyat, kalanSure, siparis.kullaniciAdi);
            }
        }
    }

    fclose(aktiftxt);

    printf("\nMusteri ekranina gitmek icin bir tusa basiniz..");
    getch();
    system("cls");
}

void oncekiSiparis()
{
    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    printf("Onceki Siparis ekrani..\n\n");
    printf("ID\tYemek Adi\t\tFiyat\t\tSiparis Zamani\t\tTeslim Zamani\t\tKullanici Adi\n");
    printf("--\t---------\t\t-----\t\t--------------\t\t-------------\t\t-------------\n");

    time_t simdiki_zaman;
    time(&simdiki_zaman);

    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.sipID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazZamani, siparis.kullaniciAdi) == 6) {
        if(strcmp(kullaniciGiris.kullaniciAdi, siparis.kullaniciAdi) == 0) {
            struct tm hazir_zamani;
            sscanf(siparis.hazZamani, "%d/%d/%d %d:%d:%d", &hazir_zamani.tm_mon, &hazir_zamani.tm_mday, &hazir_zamani.tm_year, &hazir_zamani.tm_hour, &hazir_zamani.tm_min, &hazir_zamani.tm_sec);

            // tm_mon 0-11 aralığında olduğu için 1 eksiltiyoruz
            hazir_zamani.tm_mon -= 1;
            hazir_zamani.tm_year -= 1900;

            time_t hazir_zamani_t = mktime(&hazir_zamani);
            if (hazir_zamani_t < simdiki_zaman) {
                printf("%s\t%s\t\t%d TL\t\t%s\t%s\t%s\n",siparis.sipID, siparis.yemekAdi, siparis.fiyat, siparis.sipZamani, siparis.hazZamani, siparis.kullaniciAdi);
            }
        }
    }

    fclose(aktiftxt);

    printf("\nMusteri ekranina gitmek icin bir tusa basiniz..");
    getch();
    system("cls");
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
