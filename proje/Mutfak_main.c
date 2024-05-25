#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "Mutfak.h"

int enKucukBulma() {
    int enKucuk = 0,i;
    for(i=0;)

    return enKucuk;
}

void otomatikYemekGuncelle(){
    //onaylanan yemekleri aktif.txt dosyasindan aldigi
    //gibi ascilara atayacak
    //ascilarin alacagi yemekler A1'den An'e kadar atandiktan sonra
    //siradaki yemekler en erken bitirene atanacak
    //eger bitis suresi esitse asci numarasi kucuk olan atanacak
}
void atanmisYemekListele(){
    //ascilara atanmis yemekleri listelenmis halde terminalde gosterecek
    FILE* aktifSiptxt = fopen("aktif.txt", "r");
    if (aktifSiptxt == NULL) {
        printf("aktif.txt mevcut degil!!\n");
        return;
    }

    printf("Siparis ekrani..\n\n");
    printf("ID\tYemek Adi\t\tFiyat\t\tKalan Sure\tKullanici Adi\nAsci\n");
    printf("--\t---------\t\t-----\t\t----------\t-------------\n----\n");

    time_t simdiki_zaman;
    time(&simdiki_zaman);

    while (fscanf(aktifSiptxt, " %[^\t] %[^\t] %d %[^\t] %[^\t] %[^\n]", mutfak.sipID, mutfak.yemekAdi, &mutfak.fiyat, mutfak.sipZamani, mutfak.hazZamani, mutfak.kullaniciAdi, mutfak.) == 7 ) {

        struct tm hazir_zamani;
        sscanf(mutfak.hazZamani, "%d/%d/%d %d:%d:%d", &hazir_zamani.tm_mon, &hazir_zamani.tm_mday, &hazir_zamani.tm_year, &hazir_zamani.tm_hour, &hazir_zamani.tm_min, &hazir_zamani.tm_sec);

        // tm_mon 0-11 aralığında olduğu için 1 eksiltiyoruz
        hazir_zamani.tm_mon -= 1;
        hazir_zamani.tm_year -= 1900;

        time_t hazir_zamani_t = mktime(&hazir_zamani);

        if (hazir_zamani_t > simdiki_zaman) {
            int kalanSure = (hazir_zamani_t - simdiki_zaman) / 60;
            printf("%s\t%s\t\t%d TL\t\t%d dk\t\t%s\n",mutfak.sipID, mutfak.yemekAdi, mutfak.fiyat, kalanSure, mutfak.kullaniciAdi);
        }

        //kalan sureden gidilerek ascilar arasinda paylasim yapilacak
    }

    fclose(aktifSiptxt);
    system("cls");


}


/*
 *
 * void onaylı yemekleri Listele
 * void onaylı yemeklerin suresini ilerlet vb
 * void asci bitirince yemegi siparis guncelleme
 *
 * burada istenen neredeyse sadece yemek hazirlanma zamaninin
 * guncellenmesi
 * !!!Asci sadece 1 yemek yapabilir, en az aşçı sayisiyla
 * (mumkunse mutfakta toplam asci sayisina gore yazilmali)

*/