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

    printf("ID\tYemek Adi\tFiyati\t\tHazirlama Suresi (dk)\n");
    printf("--\t---------\t------\t\t---------------------\n");
    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &yemek.ID, yemek.yemekAdi, &yemek.fiyat, &yemek.hazirlama_suresi, yemek.durum) == 5) {
        if (strcmp(yemek.durum, "Mevcut") == 0) {
            printf("%d\t%s\t%.2f TL\t\t%d dk\n", yemek.ID, yemek.yemekAdi, yemek.fiyat, yemek.hazirlama_suresi);
        }
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

    yeni_yemek.ID = rand() % 100 + 1;

    printf("\n\nYemek adi: ");
    scanf(" %[^\n]s", yeni_yemek.yemekAdi);

    printf("Fiyat (TL): ");
    scanf("%f", &yeni_yemek.fiyat);

    printf("Hazirlanma suresi (dk): ");
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
        fprintf(yemeklistesitxt, "%d\t%s\t%.2f\t\t%d\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
}

void yemekEkleme()
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

    printf("\n\nYemek listesi %s dosyasina kaydedildi.\n", "yemeklistesi.txt");
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
            scanf("%f", &yemekler[i].fiyat);

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

    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &yemekler[yemek_sayisi].ID, yemekler[yemek_sayisi].yemekAdi,
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
        fprintf(yemeklistesitxt, "%d\t%s\t%.2f\t%d\t\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
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

    while (fscanf(yemeklistesitxt, "%d %[^\t] %f %d %[^\n]", &yemekler[yemek_sayisi].ID, yemekler[yemek_sayisi].yemekAdi,
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
        fprintf(yemeklistesitxt, "%d\t%s\t%.2f\t%d\t\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
    printf("\n\nYemek listesi guncellendi: yemeklistesi.txt\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");

    return 0;
}

void onay_red()
{

}

void gunlukRapor()
{

}

void analizler()
{

}

void asciSayisiBelirleme()
{

}



