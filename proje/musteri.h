#ifndef _MUSTERI_H
#define _MUSTERI_H
#include <stdbool.h>

struct Yemek {
    char yemekAdi[100];
    float fiyat;
    int hazirlama_suresi;
    bool durum[100];
}yemek;

struct Siparis {
    int id;
    char yemekAdi[100];
    float fiyat;
    time_t siparisTarihi;
    int hazirlanmaSuresi;
}siparis;

struct Kontrol {
    char satir[100];
    char yemekAdi[100];
    float fiyat;
    int hazirlanmaSuresi;
    int yemekBuldu;
}kontrol;



void yemekleriListele();
void siparisAl();



void yeniSiparis();
void mevcutSiparis();
void oncekiSiparis();
int menu();

#endif

