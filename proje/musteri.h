#ifndef _MUSTERI_H
#define _MUSTERI_H
#define maxSifre 6
#define maxKulAdi 100
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

//typedef struct Musteri {
//    int ID, fiyat, hazirlama_suresi,yemekID, yemekBuldu;
//    char yemekAdi[MAX_UZUNLUK], durum[MAX_UZUNLUK], tarih[MAX_UZUNLUK],
//         saat[MAX_UZUNLUK], satir[100], kullaniciAdi[MAX_UZUNLUK], sifre[MAX_UZUNLUK];
//    time_t siparisTarihi, hazirOlmaZamani;
//} musteri ;

struct Kontrol {
    int yemekID;
    char satir[100];
    char yemekAdi[30];
    float fiyat;
    int hazirlama_suresi;
    char durum[30];
    int yemekBuldu;
}kontrol;

struct Kullanici {
    int kulBuldu;
    int id;
    int klncID;
    char klncAdi[30];
    char kulAdi[maxKulAdi];
    char sifre[maxSifre];
    //toplam kullanici sayisi yazilacak
}kullanici;

//int MusteriUygulamasi();
//int musteriEkrani();
//void kayitOl();
//int oturumAc();
//void yemekleriListele();
//void siparisAl();
//void yeniSiparis();
//int mevcutSiparis();
//void oncekiSiparis();



int dosyaSatirSayi(const char *dosyaTXT);


void yemekleriListele();
void siparisAl();

void kullaniciKaydet();
void kullaniciGiris();
void yeniKullanici();

void yeniSiparis();
void mevcutSiparis();
void oncekiSiparis();


#endif
