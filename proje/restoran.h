#ifndef _RESTORAN_H
#define _RESTORAN_H
#include <stdbool.h>

#define MAX_UZUNLUK 30

struct Yemek {
    int ID;
    char yemekAdi[MAX_UZUNLUK];
    int fiyat;
    int hazirlama_suresi;
    char durum[MAX_UZUNLUK];
};

struct Siparis {
    char ID[MAX_UZUNLUK];
    char yemekAdi[MAX_UZUNLUK];
    int fiyat;
    char sipZamani[MAX_UZUNLUK];
    char hazirZamani[MAX_UZUNLUK];
    char kullaniciAdi[MAX_UZUNLUK];
};

void yemekleriListele();

void yemekEkle(struct Yemek yemekler[], int *yemek_sayisi);
void yemeklistesiKaydet(struct Yemek yemekler[], int yemek_sayisi);
int yemekEkleme();

void yemekGuncelle(struct Yemek yemekler[], int yemek_sayisi, int guncellenecek_ID);
int yemekGuncelleme();

void yemekSil(struct Yemek yemekler[], int* yemek_sayisi, int silinecek_ID);
int yemekSilme();

int siparisSayisi(FILE* siparislertxt);
int onay_red();

int gunlukRapor();

void analizler();
void gunlukKazanc();
void aylikKazanc();
void donemKazanc();
void enCokTuketim();

void asciSayisiBelirleme();

#endif

