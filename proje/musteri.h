#ifndef _MUSTERI_H
#define _MUSTERI_H
#define maxSifre 6
#define maxKulAdi 100
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

struct Kullanici {
    char kulAdi[maxKulAdi];
    char sifre[maxSifre];
};


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


void yemekleriListele();
void siparisAl();


void kullaniciKaydet();
void kullaniciGiris();
void yeniSiparis();
void mevcutSiparis();
void oncekiSiparis();
int menu();


#endif

