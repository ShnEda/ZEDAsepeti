#ifndef _MUTFAK_H
#define _MUTFAK_H

#define MAX_UZUNLUK 30

struct Mutfak {
    int fiyat,yemekID, yemekBuldu;
    char yemekAdi[30], durum[15], kullaniciAdi[15], sifre[8],
    sipID[10],sipZamani[30],hazZamani[30], asciAdi[10];
    time_t siparisTarihi, hazirOlmaZamani;
};

int enKucukBulma(int* dizi, int diziBoyutu)
{
    int enKucuk = INT_MAX;
    for(int i = 0; i < diziBoyutu; i++)
    {
        if(dizi[i] < enKucuk)
        {
            enKucuk = dizi[i];
        }
    }
    return enKucuk;
}

int asciSayisi()
{
    FILE* ascilartxt = fopen("ascilar.txt", "r");
    if (ascilartxt == NULL) {
        printf("ascilar.txt mevcut degil!!\n");
        return 0;
    }

    struct Mutfak mutfak;
    int asci_Sayisi = 0;

    while (fscanf(ascilartxt, " %[^\n]", mutfak.asciAdi) == 1) {
        asci_Sayisi++;
    }
    fclose(ascilartxt);
    return asci_Sayisi;
}

void otomatikYemekGuncelle() {
    FILE* aktifSiptxt = fopen("aktif.txt", "r");
    if (aktifSiptxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    int asci_Sayisi = asciSayisi();
    int kalanSureler[asci_Sayisi];
    for(int i = 0; i < asci_Sayisi; i++) {
        kalanSureler[i] = 200;
    }

    struct Mutfak mutfak;
    struct tm hazir_zamani;
    time_t hazir_zamani_t, simdiki_zaman;
    while (fscanf(aktifSiptxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", mutfak.sipID, mutfak.yemekAdi, &mutfak.fiyat, mutfak.sipZamani, mutfak.hazZamani, mutfak.kullaniciAdi) == 6) {
        memset(&hazir_zamani, 0, sizeof(hazir_zamani));
        sscanf(mutfak.hazZamani, "%d/%d/%d %d:%d:%d", &hazir_zamani.tm_mon, &hazir_zamani.tm_mday, &hazir_zamani.tm_year, &hazir_zamani.tm_hour, &hazir_zamani.tm_min, &hazir_zamani.tm_sec);

        hazir_zamani.tm_mon -= 1;
        hazir_zamani.tm_year -= 1900;

        hazir_zamani_t = mktime(&hazir_zamani);
        time(&simdiki_zaman);

        if (hazir_zamani_t > simdiki_zaman) {
            int kalanSure = (hazir_zamani_t - simdiki_zaman) / 60;
            int enKucukSureliAsci = enKucukBulma(kalanSureler, asci_Sayisi);
            kalanSureler[enKucukSureliAsci] = kalanSure;
        }
    }

    fclose(aktifSiptxt);
    printf("\nAna menuye gitmek icin bir tusa basiniz..");
    getch();
    system("cls");
}

//onaylanan yemekleri aktif.txt dosyasindan aldigi
    //gibi ascilara atayacak
    //ascilarin alacagi yemekler A1'den An'e kadar atandiktan sonra
    //siradaki yemekler en erken bitirene atanacak
    //eger bitis suresi esitse asci numarasi kucuk olan atanacak
    //ascilar aktif.txt dosyasini kullanacak
    //ascilarin yemek hazirlama suresi 0 olmasa da yeni yemegin saati ve ne zaman
    //baslayacagi belli olacak
    //sadece bu yemek hazirlandigi an mevcut siparislerden atilip onceki siparislere atilacak
    //yemek hazirlanma sureleri
    //hazir_zamani.tm_mon -= 1;
    //        hazir_zamani.tm_year -= 1900;
    //
    //        time_t hazir_zamani_t = mktime(&hazir_zamani);
    //if (hazir_zamani_t > simdiki_zaman) {
    //            int kalanSure = (hazir_zamani_t - simdiki_zaman) / 60; kullanilarak
    //kalan sure hesaplanacak
    //kalanSure'den gidilerek enKucukBulma() fonksiyonu kullanildiktan sonra
    //restoran.c'deki void asciSayisiBelirleme(int asciSayisi) ile alinan asciSayisi
    //n'da bulunan ascilarin 0(yemek yapmiyor) ve 1(yemek yapiyor) durumlarina gore
    //ascilar arasindaki kalan sure de enKucukBulma fonksiyonunun kullanilabilmesi icin
    //kalan sureler bir diziye atanacak

void atanmisYemekListele()
{
    FILE *aktifSiptxt, *ascilartxt;
    aktifSiptxt = fopen("aktif.txt","r");
    ascilartxt = fopen("ascilar.txt","r");

    if (aktifSiptxt == NULL || ascilartxt == NULL) {
        printf("aktif.txt ya da ascilar.txt mevcut degil!!\n");
        return;
    }

    printf("Siparis ekrani..\n\n");
    printf("ID\tYemek Adi\t\tFiyat\t\tKalan Sure\tKullanici Adi\tAsci Adi\n");
    printf("--\t---------\t\t-----\t\t----------\t-------------\t--------\n");

    time_t simdiki_zaman;
    time(&simdiki_zaman);

    struct Mutfak mutfak;
    while (fscanf(aktifSiptxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", mutfak.sipID, mutfak.yemekAdi, &mutfak.fiyat, mutfak.sipZamani, mutfak.hazZamani, mutfak.kullaniciAdi) == 6) {
        if(fscanf(ascilartxt, " %[^\n]", mutfak.asciAdi) == 1){
            struct tm hazir_zamani;
            sscanf(mutfak.hazZamani, "%d/%d/%d %d:%d:%d", &hazir_zamani.tm_mon, &hazir_zamani.tm_mday, &hazir_zamani.tm_year, &hazir_zamani.tm_hour, &hazir_zamani.tm_min, &hazir_zamani.tm_sec);

            // tm_mon 0-11 aralýðýnda olduðu için 1 eksiltiyoruz
            hazir_zamani.tm_mon -= 1;
            hazir_zamani.tm_year -= 1900;

            time_t hazir_zamani_t = mktime(&hazir_zamani);

            if (hazir_zamani_t > simdiki_zaman) {
                int kalanSure = (hazir_zamani_t - simdiki_zaman) / 60;
                if(fscanf(ascilartxt, " %[^\n]", mutfak.asciAdi) == EOF) {
                    rewind(ascilartxt); // Dosyanın başına dön
                }
                printf("%s\t%s\t\t%d TL\t\t%d dk\t\t%s\t\t%s\n",mutfak.sipID, mutfak.yemekAdi, mutfak.fiyat, kalanSure, mutfak.kullaniciAdi, mutfak.asciAdi);
            }
        }
    }

    fclose(aktifSiptxt);
    fclose(ascilartxt);
    printf("\nAna menuye gitmek icin bir tusa basiniz..");
    getch();
    system("cls");
}



/* typedef struct mutfak
 *
 * void onaylý yemekleri Listele
 * void onaylý yemeklerin suresini ilerlet vb
 * void asci bitirince yemegi siparis guncelleme
 *
 * burada istenen neredeyse sadece yemek hazirlanma zamaninin
 * guncellenmesi
 * !!!Asci sadece 1 yemek yapabilir, en az aþçý sayisiyla
 * (mumkunse mutfakta toplam asci sayisina gore yazilmali)
 *
 * //Asci yemegi en az bitirme suresi kalan ya da hazirlanma zamani en erken olana gore
 * //bu sart olmasi icin tum ascilar dolu olmali
 * //ilk ascilar 1. ascidan son asciya sirasiyla yemekler atanacak.
 * //eger esitse asci numarasi kucuk olan atanir.
 * //ascilar aktif.txt kullanacak
 *
 * Bura da gpt yolu:
 *- Onaylý Yemekleri Listeleme:(gerek var mi)
 *- Baska bir uygulama veya sistemden alinan onayli yemek listesini oku
mutfaga bu listedeki yemekleri listele
* -Yemek Hazýrlama Suresini Ýlerletme:
Asci sectigi bir yemegin hazirlik suresini belirli araliklarla ilerlet.
Bunu belirli bir yemegin hazirlik suresini artirmak icin kullan.
* -Ascinin Yemegi Hazirlama ve Guncelleme:
* -Asci bir yemegi hazirlamaya basladiginda, secilen yemegin hazirlik durumunu guncelle.
Guncellenmis yemek listesini yeni bir dosyaya kaydet veya mevcut dosyayi guncelle.

*/



#endif //ZEDASEPETI_MUTFAK_H
