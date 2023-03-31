#include <iostream>
#include <pthread.h>
#include <ctime>
#include <chrono>

bool asalSayiMi( int sayi ) {//Parametre olarak gelen sayiyi asal mi diye kontrol eder.

    if ( sayi <= 1 ) {
        return false;
    }

    for ( int i = 2 ; i <= sayi / 2 ; i++ ) {
        if ( sayi % i == 0 ) {
            return false;
        }
    }

    return true;

}

void *aramaAralik( void *args ){ //Parametre olarak gelen araliktaki sayilari asal sayi kontrolune gonderir.

    int *limit = ( int* ) args;

    for( int i = limit[0] ; i < limit[1] ; i++ ){
        if( asalSayiMi(i) ){
            // std::cout << " " << i << " ";
        }
    }

    return NULL;

}

int main( void ){

    int kucukSayi, buyukSayi, kanalSayisi=1, geciciSayi;
    
    std::cout << "Kucuk Sayiyi Giriniz: ";
    std::cin >> kucukSayi;
    geciciSayi = kucukSayi;

    std::cout << "Buyuk Sayiyi Giriniz: ";
    std::cin >> buyukSayi;

    while(kanalSayisi<=64){

        kucukSayi=geciciSayi; //Her dongude kucuk sayimizi sifirliyoruz.
        std::cout << "\nKanal Sayisi: " << kanalSayisi << std::endl;

        pthread_t *kanal = NULL; 
        kanal = new pthread_t[ kanalSayisi ]; // Belirtilen kanal sayisi kadar threadleri tutacak.

        int **aralik=NULL;
        aralik = new int *[ kanalSayisi ]; //Kanallara gidecek kucuk ve buyuk sayilari tutar. 
         // Or: 0...1000 ve 4 kanalli oldugunu dusunursek:  0-250, 250-500, 500-750, 750-1000
        
        int artisMiktari = ( buyukSayi - kucukSayi ) / kanalSayisi; 
        // Or: Diyelim 0-1000 arasi dendi ve kanal sayisi 4, artis miktari 250 olur.

        // Sureyi tutmak icin...
        auto start = std::chrono::high_resolution_clock::now();

        // Burada belirtilen kanal sayisi kadar thread olusturuyoruz.
        for( int i = 0 ; i < kanalSayisi ; i++ ){

            aralik[i] = new int[2]; 
            aralik[i][0] = kucukSayi;
            aralik[i][1] = kucukSayi + artisMiktari;
            kucukSayi += artisMiktari; 
            pthread_create( &kanal[i], NULL, aramaAralik, aralik[i] );

        }

        // Burada threadlerin birbirini beklemesini sagliyoruz.
        for( int i = 0 ; i < kanalSayisi ; i++ ){

            pthread_join( kanal[i], NULL );

        }   

        // Gecen sure hesaplaniyor.
        auto finish = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration<double>(finish - start).count();
        std::cout << "Harcanan Zaman = " << elapsed*1000 << " ms." << std::endl;

        //Bellekten siliyoruz.
        for (int i = 0 ; i < kanalSayisi ; i++) {
            delete [] aralik[i];
        }
        delete [] aralik;
        delete [] kanal;

        kanalSayisi*=2; //Bir sonraki thread sayimiz...
    }

    return 0; 

}