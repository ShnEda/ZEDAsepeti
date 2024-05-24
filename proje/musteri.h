#ifndef _MUSTERI_H
#define _MUSTERI_H

typedef struct Musteri {
    int ID, fiyat, hazirlama_suresi,yemekID, yemekBuldu;
    char yemekAdi[30], durum[15], tarih[30],
         saat[30], satir[100], kullaniciAdi[15],
         sifre[8], sipID[10],sipZamani[30],hazZamani[30];
    time_t siparisTarihi, hazirOlmaZamani;
} musteri ;



int MusteriUygulamasi();
int musteriEkrani();

void kayitOl();
int oturumAc();

void yemekleriListele();
void siparisAl();
void yeniSiparis();

void mevcutSiparis();

void oncekiSiparis();

int dosyaSatirSayi(const char *dosyaTXT);

#endif
