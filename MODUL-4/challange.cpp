#include <iostream>
using namespace std;

void nama()
{
    cout << "|====================================|" << endl;
    cout << "|                                    |" << endl;
    cout << "[         MODULE 4 - FUNCTION        ]" << endl;
    cout << "|                                    |" << endl;
    cout << "|====================================|" << endl;
    cout << "1. TIVAIZ Store" << endl;
    cout << "2. Kalkulator TIVAIZ" << endl;
    cout << "0. Keluar" << endl;
    cout << "=============================" << endl;
}
int main()
{
    nama();
    int menu;
    cout << "Pilih menu: ";
    cin >> menu;

    cout << "#==========================#" << endl;
    cout << "|       TIVAIZ STORE       |" << endl;
    cout << "#==========================#" << endl;
    if (menu == 1)
    {
        cout << "1. Input Barang" << endl;
    }
    else if (menu == 2)
    {
        cout << "2. Hapus Barang" << endl;
    }
    else if (menu == 3)
    {
        cout << "3. Edit Barang" << endl;
    }
    if (menu == 4)
    {
        cout << "4. Lihat Barang" << endl;
    }
    if (menu == 0)
    {
        cout << "0. Kembali" << endl;
    }

    cout << "======================================" << endl;
    cout << "Pilih menu: ";
    cin >> menu;

    cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 4." << endl;
    system("pause");
    system("cls");

    cout << "[Gagal] Input harus berupa angka" << endl;
    system("pause");
    system("cls");

    cout << "---------------------------" << endl;
    cout << "       INPUT BARANG        " << endl;
    cout << "---------------------------" << endl;
    cout << "---------------------------" << endl;
    cout << "Nama Barang : ";
    cout << "---------------------------" << endl;
    cout << "Stok (unit) : ";
    cout << "---------------------------" << endl;
    cout << "Harga (Rp) : ";
    cout << "---------------------------" << endl;
    cout << "[Berhasil] Indomie Goreng ditambahkan!";
    system("pause");
    system("cls");

    cout << "[Gagal] Stok harus berupa angka!" << endl;
    system("pause");
    system("cls");

    return 0;
}