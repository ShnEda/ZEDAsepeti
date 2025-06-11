#ifndef _RESTORAN_H
#define _RESTORAN_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

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
    char tarih[10];
};

struct Asci {
    char asciAdi[MAX_UZUNLUK];
};

int menu();

void yemekleriListele()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
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

void yemekEkleme()
{
    printf("Yemek Ekleme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    struct Yemek yeniYemek;
    char devam;

    srand(time(NULL));

    do{
        yeniYemek.ID = rand() % 500 + 100;  //yemeklerin ID leri ayarlaniyor
        printf("\n\nYemek adi                  : ");
        scanf(" %[^\n]s", yeniYemek.yemekAdi);
        printf("Fiyat (TL)                 : ");
        scanf("%d", &yeniYemek.fiyat);
        printf("Hazirlanma suresi (dk)     : ");
        scanf("%d", &yeniYemek.hazirlama_suresi);
        printf("Durum (Mevcut/Mevcut Degil): ");
        scanf(" %[^\n]s", yeniYemek.durum);

        FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "a");

        fprintf(yemeklistesitxt, "%d\t%s\t%d\t%d\t%s\n",yeniYemek.ID ,yeniYemek.yemekAdi, yeniYemek.fiyat, yeniYemek.hazirlama_suresi, yeniYemek.durum);
        fclose(yemeklistesitxt);

        printf("\nBaska bir yemek eklemek istiyor musunuz? (E/H): ");
        scanf(" %c", &devam);
    }while(devam == 'E' || devam == 'e');

    printf("\n\nYemek ekleme islemi basarili..\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

int yemekSayisi()
{
    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
        return 0;
    }

    struct Yemek yemekler[MAX_UZUNLUK];
    int yemekSayisi = 0;

    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemekler[yemekSayisi].ID, yemekler[yemekSayisi].yemekAdi,
                  &yemekler[yemekSayisi].fiyat, &yemekler[yemekSayisi].hazirlama_suresi, yemekler[yemekSayisi].durum) == 5) {
        yemekSayisi++;
    }
    fclose(yemeklistesitxt);
    return yemekSayisi;
}

void yemekGuncelleme()
{
    printf("Yemek Guncelleme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    struct Yemek yemekler[MAX_UZUNLUK];
    int yemek_sayisi = yemekSayisi(), guncellenecek_ID, kontrol = 0, i=0;

    printf("\n\nGuncellenecek yemek ID'sini girin: ");
    scanf("%d", &guncellenecek_ID);

    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
        return;
    }
    FILE* gecicitxt = fopen("gecici.txt", "w");

    while (fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemekler[i].ID, yemekler[i].yemekAdi, &yemekler[i].fiyat, &yemekler[i].hazirlama_suresi, yemekler[i].durum) == 5) {
        if (yemekler[i].ID == guncellenecek_ID) {
            printf("\n\nYeni yemek adi: ");
            scanf(" %[^\n]s", yemekler[i].yemekAdi);
            printf("Yeni fiyat (TL): ");
            scanf("%d", &yemekler[i].fiyat);
            printf("Yeni hazirlanma suresi (dk): ");
            scanf("%d", &yemekler[i].hazirlama_suresi);
            printf("Yeni durum (Mevcut/Mevcut Degil): ");
            scanf(" %[^\n]s", yemekler[i].durum);
            kontrol = 1;
        }
        fprintf(gecicitxt, "%d\t%s\t%d\t%d\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat, yemekler[i].hazirlama_suresi, yemekler[i].durum);
    }

    fclose(yemeklistesitxt);
    fclose(gecicitxt);

    if(kontrol == 0) {
        printf("ID numarasi bulunamadi!\n");
        remove("gecici.txt");
        printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
        getch();
        system("cls");
        return;
    }

    remove("yemeklistesi.txt");
    rename("gecici.txt", "yemeklistesi.txt");

    printf("\n\nYemek bilgileri guncellendi!\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void yemekSilme()
{
    printf("Yemek Silme Ekrani..\n\n");
    printf("Mevcut Yemek Listesi..\n\n");
    yemekleriListele();

    struct Yemek yemekler[MAX_UZUNLUK];
    int yemek_sayisi = yemekSayisi(), silinecek_ID, kontrol = 0;

    printf("\n\nSilinecek yemek ID'sini girin: ");
    scanf("%d", &silinecek_ID);

    FILE* yemeklistesitxt = fopen("yemeklistesi.txt", "r");
    if (yemeklistesitxt == NULL) {
        printf("yemeklistesi.txt mevcut degil!!\n");
        return;
    }
    FILE* gecicitxt = fopen("gecici.txt", "w");

    for (int i = 0; i < yemek_sayisi; i++) {
        fscanf(yemeklistesitxt, "%d %[^\t] %d %d %[^\n]", &yemekler[i].ID, yemekler[i].yemekAdi, &yemekler[i].fiyat, &yemekler[i].hazirlama_suresi, yemekler[i].durum);
        if (yemekler[i].ID == silinecek_ID) {
            kontrol = 1;
        } else {
            fprintf(gecicitxt, "%d\t%s\t%d\t%d\t%s\n", yemekler[i].ID, yemekler[i].yemekAdi, yemekler[i].fiyat,
                    yemekler[i].hazirlama_suresi, yemekler[i].durum);
        }
    }

    fclose(yemeklistesitxt);
    fclose(gecicitxt);

    if (kontrol == 0) {
        printf("ID numarasi bulunamadi!\n");
        remove("gecici.txt");
        printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
        getch();
        system("cls");
        return;
    }

    remove("yemeklistesi.txt");
    rename("gecici.txt", "yemeklistesi.txt");

    printf("\n\nYemek bilgileri silindi!\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void onay_red()
{
    FILE* siparislertxt = fopen("siparisler.txt", "r");
    if (siparislertxt == NULL) {
        printf("siparisler.txt mevcut degil!!\n");
        return;
    }
    printf("Onay/Red ekrani..\n\n");

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
    siparislertxt = fopen("siparisler.txt", "w");
    fclose(siparislertxt);
    printf("\n\nIslem tamamlandi!\n");
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void gunlukRapor()
{
    char istenenTarih[20];
    int sayac = 0;
    printf("Gunluk Rapor ekrani..\n\n");
    printf("Istenen tarihi giriniz [lutfen (aa/gg/yyyy) formatinda olsun]: ");
    scanf(" %[^\n]", istenenTarih);

    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }
    printf("\n\n");
    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        if (strstr(siparis.sipZamani, istenenTarih) != NULL) {
            printf("%s\t%s\t%d TL\t%s\t%s\t%s\n", siparis.ID, siparis.yemekAdi, siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi);
            sayac++;
        }
    }

    printf("\n%s tarihli gune ait %d adet siparis kaydi vardir.\n", istenenTarih, sayac);
    fclose(aktiftxt);
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void gunlukKazanc()
{
    char istenenTarih[20];
    int toplam=0;
    printf("Gunluk Kazanc ekrani..\n\n");
    printf("Istenen tarihi giriniz [lutfen (aa/gg/yyyy) formatinda olsun]: ");
    scanf(" %[^\n]", istenenTarih);

    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }
    printf("\n\n");
    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        if (strstr(siparis.sipZamani, istenenTarih) != NULL) {
            toplam += siparis.fiyat;
        }
    }

    printf("%s tarihli gunun kazanci %d TL'dir\n", istenenTarih, toplam);
    fclose(aktiftxt);
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void aylikKazanc()
{
    char istenenAy[20];
    int toplam=0;
    printf("Aylik Kazanc ekrani..\n\n");
    printf("Istenen ayi giriniz [lutfen (aa/) formatinda olsun]: ");
    scanf(" %[^\n]", istenenAy);

    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }
    printf("\n\n");
    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        if (strstr(siparis.sipZamani, istenenAy) != NULL) {
            toplam += siparis.fiyat;
        }
    }

    printf("%s tarihli ayin kazanci %d TL'dir\n", istenenAy, toplam);
    fclose(aktiftxt);
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void donemKazanc()
{
    char basTarih[20], sonTarih[20];
    struct tm basZamani = {0};
    struct tm sonZamani = {0};
    int toplam = 0;

    printf("Donem Kazanci ekrani..\n");
    printf("\nBaslangic tarihi giriniz [lutfen (aa/gg/yyyy) formatinda olsun]: ");
    scanf("%s", basTarih);
    printf("\nBitis tarihi giriniz [lutfen (aa/gg/yyyy) formatinda olsun]: ");
    scanf("%s", sonTarih);

    sscanf(basTarih, "%d/%d/%d", &basZamani.tm_mday, &basZamani.tm_mon, &basZamani.tm_year);
    basZamani.tm_mon -= 1;
    basZamani.tm_year -= 1900;

    sscanf(sonTarih, "%d/%d/%d", &sonZamani.tm_mday, &sonZamani.tm_mon, &sonZamani.tm_year);
    sonZamani.tm_mon -= 1;
    sonZamani.tm_year -= 1900;

    time_t basTarihsan = mktime(&basZamani); // Baslangic tarihinin saniyesi
    time_t sonTarihsan = mktime(&sonZamani) + 86399; // Bitis tarihinin saniyesi (1 gün ekledik)

    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        struct tm sipZamani = {0};
        sscanf(siparis.sipZamani, "%d/%d/%d %d:%d:%d", &sipZamani.tm_mday, &sipZamani.tm_mon, &sipZamani.tm_year, &sipZamani.tm_hour, &sipZamani.tm_min, &sipZamani.tm_sec);
        sipZamani.tm_mon -= 1;
        sipZamani.tm_year -= 1900;

        time_t sipTarihsan = mktime(&sipZamani); // Sipariþ tarihinin saniyesi

        if (difftime(sipTarihsan, basTarihsan) >= 0 && difftime(sipTarihsan, sonTarihsan) <= 0) {
            toplam += siparis.fiyat;
        }
    }

    fclose(aktiftxt);
    printf("\n%s - %s tarihleri arasindaki kazanc %d TL'dir\n", basTarih, sonTarih, toplam);
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

void enCokTuketilenYemek()
{
    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    char yemekler[100][100];
    int yemekSayilari[100] = {0};
    int yemekAdeti = 0;

    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        int i, yemekBuldu = 0;
        for (i = 0; i < 100; i++) { //yemegi ilk gordugunde kaydediyor
            if (yemekler[i][0] == '\0') {
                strcpy(yemekler[i], siparis.yemekAdi);
                yemekSayilari[i]++;
                yemekAdeti = 1;
                yemekBuldu = 1;
                break;
            }
            if (strcmp(siparis.yemekAdi, yemekler[i]) == 0) { //her gordugunde artiyiriyor
                yemekSayilari[i]++;
                yemekAdeti++;
                yemekBuldu = 1;
                break;
            }
        }
        if (yemekBuldu == 0) { // Yemekler dizisi dolduysa donguden cik
            printf("yemekler dizisi doldu!!\n");
            break;
        }
    }

    int enCokSatilan = 0;
    for (int i = 1; i < 100; i++) {
        if (yemekSayilari[i] > yemekSayilari[enCokSatilan]) {
            enCokSatilan = i;
        }
    }
    printf("En Cok Tuketilen Yemek\t\t\tAdeti\n");
    printf("----------------------\t\t\t-----\n");
    printf("%s\t\t\t\t%d\n\n",yemekler[enCokSatilan],yemekAdeti);
    fclose(aktiftxt);
}

void enKazancliGun()
{
    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    struct Siparis siparisler[100],siparis;
    int siparisSayisi = 0;

    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {

        struct Siparis yeni_siparis;
        strcpy(yeni_siparis.tarih, siparis.sipZamani);
        yeni_siparis.fiyat = siparis.fiyat;

        siparisler[siparisSayisi] = yeni_siparis;
        siparisSayisi++;
    }

    int toplamFiyatlar[100] = {0};
    for (int i = 0; i < siparisSayisi; i++) { //her gunun toplam fiyatini hesaplar
        for (int j = i; j < siparisSayisi; j++) {
            if (strcmp(siparisler[i].tarih, siparisler[j].tarih) == 0)
                toplamFiyatlar[i] += siparisler[j].fiyat;
        }
    }

    int enYuksekFiyat = 0;
    int index = 0;
    for (int i = 0; i < siparisSayisi; i++) {
        if (toplamFiyatlar[i] > enYuksekFiyat) {
            enYuksekFiyat = toplamFiyatlar[i];
            index = i;
        }
    }

    printf("En Kazancli Gun\t\t\t\tKazanc\n");
    printf("---------------\t\t\t\t------\n");
    printf("%s\t\t\t\t%d TL\n\n",siparisler[index].tarih, enYuksekFiyat);
    fclose(aktiftxt);
}

void enCokSiparisVerenKullanici()
{
    FILE* aktiftxt = fopen("aktif.txt", "r");
    if (aktiftxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    char kullanicilar[100][100];
    int kullaniciSayisi[100] = {0};
    int sipAdeti = 0;

    struct Siparis siparis;
    while (fscanf(aktiftxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", siparis.ID, siparis.yemekAdi, &siparis.fiyat, siparis.sipZamani, siparis.hazirZamani, siparis.kullaniciAdi) == 6) {
        int i, kullaniciBuldu = 0;
        for (i = 0; i < 100; i++) { //kullaniciyi ilk gordugunde kaydediyor
            if (kullanicilar[i][0] == '\0') {
                strcpy(kullanicilar[i], siparis.kullaniciAdi);
                kullaniciSayisi[i]++;
                sipAdeti = 1;
                kullaniciBuldu = 1;
                break;
            }
            if (strcmp(siparis.kullaniciAdi, kullanicilar[i]) == 0) { //her gordugunde artiyiriyor
                kullaniciSayisi[i]++;
                sipAdeti++;
                kullaniciBuldu = 1;
                break;
            }
        }
        if (kullaniciBuldu == 0) { // kullanicilar dizisi dolduysa donguden cik
            printf("kullanicilar dizisi doldu!!\n");
            break;
        }
    }

    int enCokKullanici = 0;
    for (int i = 1; i < 100; i++) {
        if (kullaniciSayisi[i] > kullaniciSayisi[enCokKullanici]) {
            enCokKullanici = i;
        }
    }

    printf("En Cok Siparis Veren Kullanici\t\tSiparis Miktari\n");
    printf("------------------------------\t\t---------------\n");
    printf("%s\t\t\t\t\t%d\n\n",kullanicilar[enCokKullanici],sipAdeti);
    fclose(aktiftxt);
}

void enCokTuketim()
{
    printf("En Cok Tuketim ekrani..\n\n\n");
    enCokTuketilenYemek();
    enKazancliGun();
    enCokSiparisVerenKullanici();

    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

int analizler()
{
    int secim3;
    printf("Analiz ekrani..\n\n");
    printf("\t 1 - GUNLUK KAZANC \n");
    printf("\t 2 - AYLIK KAZANC \n");
    printf("\t 3 - DONEM KAZANCI \n");
    printf("\t 4 - EN COK TUKETIM \n");
    printf("\t 0 - RESTORAN EKRANINA DON \n");
    printf("\n\t Seciminiz     : ");
    scanf("%d",&secim3);
    system("cls");

    while(secim3!=0) {
        switch(secim3) {

            case 1: gunlukKazanc(); break;
            case 2: aylikKazanc(); break;
            case 3: donemKazanc(); break;
            case 4: enCokTuketim(); break;
            case 0: return menu(); break;
            default: printf("hatali secim yaptiniz ! \n"); break;
        }
        secim3 = analizler();
    }
    return 0;
}

void asciSayisiBelirleme()
{

    int asciSayisi;
    printf("Asci Sayisi Belirleme ekrani..\n\n");
    printf("Asci sayisini giriniz: ");
    scanf("%d", &asciSayisi);

    FILE* ascilartxt = fopen("ascilar.txt","w");

    struct Asci ascilar[asciSayisi];
    int sira = 1;
    for(sira;sira<=asciSayisi;sira++)
    {
        snprintf(ascilar[sira].asciAdi,sizeof(ascilar[sira].asciAdi), "A%d", sira);
        fprintf(ascilartxt, "%s\n" ,ascilar[sira].asciAdi);
    }

    fclose(ascilartxt);
    printf("\n%d adet asci basari ile kaydedildi.",asciSayisi);
    printf("\n\nAna menuye donmek icin herhangi bir tusa basiniz..");
    getch();
    system("cls");
}

#endif
