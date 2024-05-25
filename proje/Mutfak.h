#ifndef _MUTFAK_H
#define _MUTFAK_H

#define MAX_UZUNLUK 30

typedef struct Mutfak {
    int fiyat,yemekID, yemekBuldu;
    char yemekAdi[30], durum[15], tarih[30],
            saat[30], satir[100], kullaniciAdi[15],
            sifre[8], sipID[10],sipZamani[30],hazZamani[30];
    time_t siparisTarihi, hazirOlmaZamani;
} mutfak ;

int enKucukBulma();

void otomatikYemekGuncelle();
void atanmisYemekListele();


/* typedef struct mutfak
 *
 * void onaylı yemekleri Listele
 * void onaylı yemeklerin suresini ilerlet vb
 * void asci bitirince yemegi siparis guncelleme
 *
 * burada istenen neredeyse sadece yemek hazirlanma zamaninin
 * guncellenmesi
 * !!!Asci sadece 1 yemek yapabilir, en az aşçı sayisiyla
 * (mumkunse mutfakta toplam asci sayisina gore yazilmali)
 *
 * //Asci yemegi en az bitirme suresi kalan ya da hazirlanma zamani en erken olana gore
 * //bu sart olmasi icin tum ascilar dolu olmali
 * //ilk ascilar 1. ascidan son asciya sirasiyla yemekler atanacak.
 * //eger esitse asci numarasi kucuk olan atanir.
 * //ascilar aktif.txt kullanacak
 *
 * Bura da gpt yolu:
 *- Onaylı Yemekleri Listeleme:(gerek var mi)
 *- Baska bir uygulama veya sistemden alinan onayli yemek listesini oku
mutfaga bu listedeki yemekleri listele
* -Yemek Hazırlama Suresini İlerletme:
Asci sectigi bir yemegin hazirlik suresini belirli araliklarla ilerlet.
Bunu belirli bir yemegin hazirlik suresini artirmak icin kullan.
* -Ascinin Yemegi Hazirlama ve Guncelleme:
* -Asci bir yemegi hazirlamaya basladiginda, secilen yemegin hazirlik durumunu guncelle.
Guncellenmis yemek listesini yeni bir dosyaya kaydet veya mevcut dosyayi guncelle.

*/



#endif //ZEDASEPETI_MUTFAK_H
