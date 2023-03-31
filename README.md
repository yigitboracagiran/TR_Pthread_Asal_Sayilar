# Program Hakkında

Bu program pthread.h kütüphanesini kullanarak paralel programlama yaparak kullanıcıdan alınan iki sayı arasındaki asal sayıları bulur.

Asal sayıları sırasıyla 1-2-4-8-16-32-64 thread oluşturarak bulur ve bu threadler arasındaki süreleri kullanıcıya verir.

# Kodun Ubuntu'da Derlenmesi Ve Çalıştırılması

Kodun olduğu dizine gelip: 

1- `g++ -std=c++17 PthreadAsalSayilar.cpp -o PthreadAsalSayilar -lpthread` ile kod derlenir.

2- `./PthreadAsalSayilar` ile kod çalıştırılır.
