#ifndef _RESTORAN_H
#define _RESTORAN_H
#include <stdbool.h>

#define MAX_UZUNLUK 30

struct Yemek {
    int ID;
    char yemekAdi[MAX_UZUNLUK];
    float fiyat;
    int hazirlama_suresi;
    char durum[MAX_UZUNLUK];
};

void yemekleriListele();

void yemekEkle(struct Yemek yemekler[], int *yemek_sayisi);
void yemeklistesiKaydet(struct Yemek yemekler[], int yemek_sayisi);
void yemekEkleme();

void yemekGuncelle(struct Yemek yemekler[], int yemek_sayisi, int guncellenecek_ID);
int yemekGuncelleme();

void yemekSil(struct Yemek yemekler[], int* yemek_sayisi, int silinecek_ID);
int yemekSilme();


void onay_red();
void gunlukRapor();
void analizler();
void asciSayisiBelirleme();

int menu();

#endif
