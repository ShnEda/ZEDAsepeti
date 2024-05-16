#ifndef _MUSTERI_H
#define _MUSTERI_H
#include <stdbool.h>

struct Yemek {
    int ID;
    char yemekAdi[30];
    float fiyat;
    int hazirlama_suresi;
    bool durum[30];
};

struct Siparis {
    int id;
    int yemekID;
    char yemekAdi[30];
    float fiyat;
    int hazirlama_suresi;
    time_t siparisTarihi;
};

struct Kontrol {
    int yemekID;
    char satir[100];
    char yemekAdi[30];
    float fiyat;
    int hazirlama_suresi;
    char durum[30];
    int yemekBuldu;
}kontrol;



void yemekleriListele();
void siparisAl();


void yeniSiparis();
void mevcutSiparis();
void oncekiSiparis();
int menu();

#endif
