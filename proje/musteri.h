#ifndef _MUSTERI_H
#define _MUSTERI_H

#define MAX_UZUNLUK 30

typedef struct Musteri {
    int ID, fiyat, hazirlama_suresi,yemekID, yemekBuldu;
    char yemekAdi[MAX_UZUNLUK], durum[MAX_UZUNLUK], tarih[MAX_UZUNLUK],
         saat[MAX_UZUNLUK], satir[100], kullaniciAdi[MAX_UZUNLUK], sifre[MAX_UZUNLUK];
    time_t siparisTarihi, hazirOlmaZamani;
} musteri ;


int MusteriUygulamasi();
int musteriEkrani();


void kayitOl();
int oturumAc();


void yemekleriListele();
void siparisAl();
void yeniSiparis();

int mevcutSiparis();

void oncekiSiparis();

#endif

