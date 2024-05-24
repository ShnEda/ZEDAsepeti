#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "restoran.h"

#define MAX_UZUNLUK 30

void yemekleriListele()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Yemek listesi bulunamadi!\n");
        return;
    }

    struct Yemek yemek;

    printf("ID \tYemek Adi\t\tFiyati\t\tHazirlama Suresi (dk)\t\tDurum\n");
    printf("---\t---------\t\t------\t\t---------------------\t\t-----\n");
    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemek.ID, yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlama_suresi, yemek.durum) == 5) {
            printf("%d\t%s\t\t%d TL\t\t\t%d dk\t\t\t%s\n", yemek.ID, yemek.yemekAdi, yemek.fiyat, yemek.hazirlama_suresi,yemek.durum);
    }
    fclose(yemeklistesitxt);
}

void yemekEkle(struct Yemek yemekler[], int *yemek_sayisi)
{
    if (*yemek_sayisi >= MAX_UZUNLUK) {
        printf("Yemek listesi dolu!\n");
        return;
    }

    struct Yemek yeni_yemek;

    srand(time(NULL));

    yeni_yemek.ID = rand() % 500 + 100;  //yemeklerin ID leri ayarlaniyor

    printf("\n\nYemek adi                  : ");
    scanf(" %[^\n]s", yeni_yemek.yemekAdi);
    printf("Fiyat (TL)                 : ");
    scanf("%d", &yeni_yemek.fiyat);
    printf("Hazirlanma suresi (dk)     : ");
    scanf("%d", &yeni_yemek.hazirlama_suresi);
    printf("Durum (Mevcut/Mevcut Degil): ");
    scanf(" %[^\n]s", yeni_yemek.durum);

    yemekler[*yemek_sayisi] = yeni_yemek;
    (*yemek_sayisi)++;

}

void yemeklistesiKaydet(struct Yemek yemekler[], int yemek_sayisi)
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "a");
    if (yemeklistesitxt == NULL) {
        printf("Dosya acilirken hata olustu!\n");
        return;
    }
    for (int i = 0; i < yemek_sayisi; i++) {
        fprintf(yemeklistesitxt, "%d\t%s\t%d\t\t%d\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
}

int yemekEkleme()
{
    struct Yemek yemekler[MAX_UZUNLUK];
    int yemek_sayisi = 0;
    char devam;

    printf("Yemek Ekleme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    do {
        yemekEkle(yemekler, &yemek_sayisi);


        printf("\nBaska bir yemek eklemek istiyor musunuz? (E/H): ");
        scanf(" %c", &devam);
    } while (devam == 'E' || devam == 'e');

    yemeklistesiKaydet(yemekler, yemek_sayisi);

    printf("\n\nYemek ekleme basarili..\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");

    return 0;
}

void yemekGuncelle(struct Yemek yemekler[], int yemek_sayisi, int guncellenecek_ID)
{
    for (int i = 0; i < yemek_sayisi; i++) {
        if (yemekler[i].ID == guncellenecek_ID) {
            printf("\n\nYeni yemek adi: ");
            scanf(" %[^\n]s", yemekler[i].yemekAdi);

            printf("Yeni fiyat (TL): ");
            scanf("%d", &yemekler[i].fiyat);

            printf("Yeni hazirlanma suresi (dk): ");
            scanf("%d", &yemekler[i].hazirlama_suresi);

            printf("Yeni durum (Mevcut/Mevcut Degil): ");
            scanf(" %[^\n]s", yemekler[i].durum);

            printf("\n\nYemek bilgileri guncellendi!\n");
            return;
        }
    }
    printf("ID numarasi bulunamadi!\n");
}

int yemekGuncelleme()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Dosya acilirken hata olustu!\n");
        return 1;
    }

    struct Yemek yemekler[MAX_UZUNLUK];
    int yemek_sayisi = 0;

    printf("Yemek Guncelleme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemekler[yemek_sayisi].ID, yemekler[yemek_sayisi].yemekAdi,
                  &yemekler[yemek_sayisi].fiyat, &yemekler[yemek_sayisi].hazirlama_suresi, yemekler[yemek_sayisi].durum) != EOF) {
        yemek_sayisi++;
    }

    fclose(yemeklistesitxt);

    int guncellenecek_ID;
    printf("\n\nGuncellenecek yemek ID'sini girin: ");
    scanf("%d", &guncellenecek_ID);

    yemekGuncelle(yemekler, yemek_sayisi, guncellenecek_ID);

    // Yemekleri dosyaya kaydet
    yemeklistesitxt = fopen("yemeklistesi.txt", "w");
    if (yemeklistesitxt == NULL) {
        printf("Dosya acilirken hata olustu!\n");
        return 1;
    }

    for (int i = 0; i < yemek_sayisi; i++) {
        fprintf(yemeklistesitxt, "%d\t%s\t%d\t%d\t\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
    printf("\n\nYemek listesi guncellendi: yemeklistesi.txt\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");

    return 0;
}


void yemekSil(struct Yemek yemekler[], int* yemek_sayisi, int silinecek_ID)
{
    for (int i = 0; i < *yemek_sayisi; i++) {
        if (yemekler[i].ID == silinecek_ID) {
            // Silinecek yemeði listenin sonundaki yemeðin bilgileriyle deðiþtir
            yemekler[i] = yemekler[(*yemek_sayisi) - 1];
            (*yemek_sayisi)--;
            printf("\n\nYemek bilgileri silindi!\n");
            return;
        }
    }
    printf("ID numarasi bulunamadi!\n");
}


int yemekSilme()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("Dosya acilirken hata olustu!\n");
        return 1;
    }

    struct Yemek yemekler[MAX_UZUNLUK];
    int yemek_sayisi = 0;
    printf("Yemek Silme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemekler[yemek_sayisi].ID, yemekler[yemek_sayisi].yemekAdi,
                  &yemekler[yemek_sayisi].fiyat, &yemekler[yemek_sayisi].hazirlama_suresi, yemekler[yemek_sayisi].durum) != EOF) {
        yemek_sayisi++;
    }

    fclose(yemeklistesitxt);

    int silinecek_ID;
    printf("\n\nSilinecek yemek ID'sini girin: ");
    scanf("%d", &silinecek_ID);

    yemekSil(yemekler, &yemek_sayisi, silinecek_ID);

    // Yemekleri dosyaya kaydet
    yemeklistesitxt = fopen("yemeklistesi.txt", "w");
    if (yemeklistesitxt == NULL) {
        printf("Dosya acilirken hata olustu!\n");
        return 1;
    }

    for (int i = 0; i < yemek_sayisi; i++) {
        fprintf(yemeklistesitxt, "%d\t%s\t%d\t%d\t\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
    printf("\n\nYemek listesi guncellendi: yemeklistesi.txt\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");

    return 0;
}

int onay_red()
{
    FILE* siparislertxt = fopen("siparisler.txt", "r");
    if (siparislertxt == NULL) {
        printf("Dosya açılırken hata oluştu!\n");
        return 1;
    }

    struct Siparis siparis;

    while (fscanf(siparislertxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani,
                  siparis.hazirZamani, siparis.kullaniciAdi) == 6) {

        printf("%s\t%s\t%d TL\t%s\t%s\t%s\n", siparis.ID, siparis.yemekAdi, siparis.fiyat, siparis.sipZamani,
                  siparis.hazirZamani, siparis.kullaniciAdi);
        printf("\nBu siparisi onayliyorsaniz (O/o) tuslayiniz, ");
        printf("reddediyorsaniz (R/r) tuslayiniz: ");
        char cevap;
        scanf(" %c", &cevap);

        if (cevap == 'o' || cevap == 'O') {
            FILE* aktiftxt = fopen("aktif.txt","a");
            fprintf(aktiftxt, "%s\t%s\t%d\t%s\t%s\t%s\n",siparis.ID, siparis.yemekAdi, siparis.fiyat, siparis.sipZamani,
                  siparis.hazirZamani, siparis.kullaniciAdi);
            fclose(aktiftxt);
            printf("Islem onaylandi!\n");
        }
        else if (cevap == 'r' || cevap == 'R') {
            printf("Islem reddedildi!\n");
        }
        else {
            printf("Gecersiz cevap! O/o veya R/r girin.\n");
        }
    }

    fclose(siparislertxt);
    FILE* siparislertxt0 = fopen("siparisler.txt", "w");
    fclose(siparislertxt0);
    printf("\n\nIslem tamamlandi!\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");

    return 0;
}

void gunlukRapor()
{
    //velev ki adam 23.59 da siparis verdi. siparis verilen gun kabul edilecek.
    //aktif.txt yi okuyarak girilen tarihe gore yapacak..
}

void analizler()
{
    //Gunluk Kazanc:
        //aktif.txt yi ac
        //kullanicidan ay/gun/yil al
        //sonra fiyatlari cekip toplayip degiskene ekliyecek
    //En cok satilan yemek:
        //yemeklistesi.txt yi ac
        //yemeklerin adlarini ve fiyatlarini cek
        //siparisler.txt yi ac
        //yemeklerin adlarini cek
        //yemeklerin adlarini karsilastir
        //en cok satilan yemegi bul
     //En cok siparis veren kullanici:
        //siparisler.txt yi ac
        //kullanicilarin adlarini cek
        //kullanicilarin adlarini karsilastir
        //en cok siparis veren kullanicinin adini bul
     //En cok kazanci olan gun:
        //aktif.txt yi ac
        //tarihleri cek
        //tarihleri karsilastir
        //en cok kazanci olan gunu bul
}

void asciSayisiBelirleme()
{
    //


}
