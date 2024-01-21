#include <iomanip> 
#include <cstring> 
#include <stdlib.h>
#include <conio.h>
#include <stdio.h> 
#include <fstream>                  
#include <iostream>

using namespace std;

struct OtelMusteri
{
    char ad[80];
    char soyad[80];
    char tel_no[12];
    int oda_no;
    int gun_sayisi;
};

void MusteriEkle();
void MusteriListeleme();
void MusteriArama();
void MusteriSil();
void MusteriDuzenle();

int main()
{
    char anamenu;
    do
    {
        system("cls");

        cout << "|------Hosgeldiniz-----------|" << endl;
        cout << "|      Secim Yapiniz         |" << endl;
        cout << "|   1- Musteri Ekleme        |" << endl;
        cout << "|   2- Musteri Listeleme     |" << endl;
        cout << "|   3- Musteri Arama         |" << endl;
        cout << "|   4- Musteri Sil           |" << endl;
        cout << "|   5- Musteri Duzenle       |" << endl;
        cout << "|----------------------------|" << endl;
        char secim;
        cin >> secim;

        switch (secim)
        {
        case '1':
        {
            MusteriEkle();
            break;
        }
        case '2':
        {
            MusteriListeleme();
            break;
        }
        case '3':
        {
            MusteriArama();
            break;
        }
        case '4':
        {
            MusteriSil();
            break;
        }
        case '5':
        {
            MusteriDuzenle();
            break;
        }
        }

        cout << "Anamenuye Donmek icin: a basin cikmak icin: c" << endl;
        anamenu = getche();

    } while (anamenu == 'a');

    return 0;
}

OtelMusteri musteri;

void MusteriEkle()
{
    ofstream yaz("otelrezervasyon.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do
    {
        cout << "Musteri Ad Giriniz" << endl;
        cin >> musteri.ad;
        cout << "Musteri Soyad Giriniz" << endl;
        cin >> musteri.soyad;
        cout << "Musteri Telefon No Giriniz" << endl;
        cin >> musteri.tel_no;
        cout << "Oda Numarasi Giriniz" << endl;
        cin >> musteri.oda_no;
        cout << "Kalacak Gun Sayisi Giriniz" << endl;
        cin >> musteri.gun_sayisi;

        yaz.write((char *)&musteri, sizeof(musteri));
        adet++;
        cout << "Baska Kayit Eklemek Istermisin (E/H)" << endl;
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet Musteri Ekledi.." << endl;

    yaz.close();
}

void MusteriListeleme()
{
    ifstream oku("otelrezervasyon.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(musteri);
    cout << "Toplam Musteri Kayit Sayisi:" << kayits << endl;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(musteri));
            oku.read((char *)&musteri, sizeof(musteri));

            cout << i + 1 << ". Musterinin Bilgileri" << endl;
            cout << "Musteri Adi: " << musteri.ad << endl;
            cout << "Musteri Soyadi: " << musteri.soyad << endl;
            cout << "Telefon No: " << musteri.tel_no << endl;
            cout << "Oda Numarasi: " << musteri.oda_no << endl;
            cout << "Kalacak Gun Sayisi: " << musteri.gun_sayisi << endl;
        }
    }
    else
        cout << "Kayit Bulunamadi..." << endl;

    oku.close();
}

void MusteriArama()
{
    ifstream oku("otelrezervasyon.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(musteri);

    cout << "Aranan Musteri Telefon Numarasini Giriniz" << endl;
    char tel_no[12];
    cin >> tel_no;

    if (kayits > 0)
    {
        for (int i = 0; i < kayits; i++)
        {
            oku.seekg(i * sizeof(musteri));
            oku.read((char *)&musteri, sizeof(musteri));

            if (strcmp(musteri.tel_no, tel_no) == 0)
            {
                cout << "Bulunan Musterinin Bilgileri" << endl;
                cout << "Musteri Adi: " << musteri.ad << endl;
                cout << "Musteri Soyadi: " << musteri.soyad << endl;
                cout << "Telefon No: " << musteri.tel_no << endl;
                cout << "Oda Numarasi: " << musteri.oda_no << endl;
                cout << "Kalacak Gun Sayisi: " << musteri.gun_sayisi << endl;
            }
        }
    }
    else
        cout << "Kayit Bulunamadi..." << endl;

    oku.close();
}

void MusteriSil()
{
    char tel_no[12];
    char secim = ' ';
    bool var = false;

    ifstream oku("otelrezervasyon.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(musteri);

    cout << "Silmek istediginiz Musterinin Telefon Numarasini Giriniz : ";
    cin >> tel_no;

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(musteri));
        oku.read((char *)&musteri, sizeof(musteri));

        if (strcmp(musteri.tel_no, tel_no) == 0)
        {
            cout << endl;
            cout << "Musterinin";
            cout << "\nAdi : " << musteri.ad;
            cout << "\nSoyad : " << musteri.soyad << endl;
            cout << "\nTelefon No : " << musteri.tel_no;
            cout << "\nOda Numarasi : " << musteri.oda_no;
            cout << "\nKalacak Gun Sayisi : " << musteri.gun_sayisi;

            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if (secim == 'H' || secim == 'h')
            {
                OtelMusteri y_musteri;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

                strcpy(y_musteri.ad, musteri.ad);
                strcpy(y_musteri.soyad, musteri.soyad);
                strcpy(y_musteri.tel_no, musteri.tel_no);
                y_musteri.oda_no = musteri.oda_no;
                y_musteri.gun_sayisi = musteri.gun_sayisi;

                y_dosya.write((char *)&y_musteri, sizeof(y_musteri));
                y_dosya.close();
            }
            if (secim == 'e' || secim == 'E')
            {
                var = true;
            }
        }
        else
        {
            OtelMusteri y_musteri;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);

            strcpy(y_musteri.ad, musteri.ad);
            strcpy(y_musteri.soyad, musteri.soyad);
            strcpy(y_musteri.tel_no, musteri.tel_no);
            y_musteri.oda_no = musteri.oda_no;
            y_musteri.gun_sayisi = musteri.gun_sayisi;

            y_dosya.write((char *)&y_musteri, sizeof(y_musteri));
            y_dosya.close();
        }
    }
    oku.close();
    if (var)
    {
        remove("otelrezervasyon.dat");
        rename("Yedek.dat", "otelrezervasyon.dat");
        cout << "\n Kayit Silindi" << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\n Kayit Bulunamadi" << endl;
    }
}

void MusteriDuzenle()
{
    char tel_no[12];
    char secim = ' ';
    bool var = false;

    ifstream oku("otelrezervasyon.dat", ios::binary | ios::app);

    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(musteri);

    cout << "Duzeltmek istediginiz Musterinin Telefon Numarasini Giriniz : ";
    cin >> tel_no;

    for (int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(musteri));
        oku.read((char *)&musteri, sizeof(musteri));

        if (strcmp(musteri.tel_no, tel_no) == 0)
        {
            cout << endl;
            cout << "Musterinin";
            cout << "\nAdi : " << musteri.ad;
            cout << "\nSoyad : " << musteri.soyad << endl;
            cout << "\nTelefon No : " << musteri.tel_no;
            cout << "\nOda Numarasi : " << musteri.oda_no;
            cout << "\nKalacak Gun Sayisi : " << musteri.gun_sayisi;

            cout << "\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if (secim == 'E' || secim == 'e')
            {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                cout << "\nMusteri Ad Giriniz" << endl;
                cin >> musteri.ad;
                cout << "Musteri Soyad Giriniz" << endl;
                cin >> musteri.soyad;
                cout << "Musteri Telefon No Giriniz" << endl;
                cin >> musteri.tel_no;
                cout << "Oda Numarasi Giriniz" << endl;
                cin >> musteri.oda_no;
                cout << "Kalacak Gun Sayisi Giriniz" << endl;
                cin >> musteri.gun_sayisi;

                dosya.write((char *)&musteri, sizeof(musteri));
                dosya.close();
            }
            else
            {
                OtelMusteri y_musteri;
                ofstream y_dosya;
                y_dosya.open("Yedek.dat", ios::app | ios::binary);

                strcpy(y_musteri.ad, musteri.ad);
                strcpy(y_musteri.soyad, musteri.soyad);
                strcpy(y_musteri.tel_no, musteri.tel_no);
                y_musteri.oda_no = musteri.oda_no;
                y_musteri.gun_sayisi = musteri.gun_sayisi;

                y_dosya.write((char *)&y_musteri, sizeof(y_musteri));
                y_dosya.close();
            }
        }
        else
        {
            OtelMusteri y_musteri;
            ofstream y_dosya;
            y_dosya.open("Yedek.dat", ios::app | ios::binary);

            strcpy(y_musteri.ad, musteri.ad);
            strcpy(y_musteri.soyad, musteri.soyad);
            strcpy(y_musteri.tel_no, musteri.tel_no);
            y_musteri.oda_no = musteri.oda_no;
            y_musteri.gun_sayisi = musteri.gun_sayisi;

            y_dosya.write((char *)&y_musteri, sizeof(y_musteri));
            y_dosya.close();
        }
    }
    oku.close();
    if (var)
    {
        remove("otelrezervasyon.dat");
        rename("Yedek.dat", "otelrezervasyon.dat");
        cout << "\nKayit Duzeltildi." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\nKayit Bulunamadi" << endl;
    }
}

