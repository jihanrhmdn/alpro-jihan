#include <iostream>
using namespace std;

int main(){
    int  umur;
    char pilihan;

    cout << "=== GOBLET OF FIRE: TURNAMEN TRIWIZARD ===" << endl;
    cout << "Masukkan umur Anda: ";
    cin >> umur;
    if (umur < 17) {
        cout << "Piala Api menolak Anda! Umur terlalu kecil" << endl;
    } else {
        cout << "Piala Api menyala! Anda terpilih sebagai Triwizard Champions." << endl;
    }
    cout << endl;

    cout << "--- TUGAS 1: NAGA HUNGARIAN HORNTAIL ---" << endl;
    cout << "Sisa perlindungan sihir: " << endl;
    cout << "Pilih strategi (a: Sembunyi, b: Panggil Sapu): ";
    cin >> pilihan;
    switch (pilihan) {
        case 'a':
            cout << "Naga menyemburkan api! Anda terluka ";
            break;
        case 'b':
            cout << "Berhasil! Anda mengambil Telur Emas! ";
            break;
        default:
            cout << "Pilihan tidak valid! Ulangi pilihan.";
    }
    cout << "Sisa perlindungan sihir: ";
    cout << endl;

    cout << "--- TUGAS 2: DANAU HITAM ---" << endl;
    cout << "Menit ... Ada GrindlyLow! (l: Lawan, h: Hindari): " << endl;

    cout << "--- TUGAS 3: LABIRIN ---" << endl;
    cout << "Sisa toleransi kesalahan: " << endl;
    cout << "Langkah ditempuh: " << endl;
    cout << "Pilih arah (1: Kiri, 2: Kanan, 3: Lurus): ";
    cin >> pilihan;
    switch (pilihan){
        case 1: 
            cout << "Terkena Akar Berbisa! Sisa toleransi kesalahan: ";
            break;
        case 2:
            cout << "Jalan aman, Anda semakin dalam. ";
            break;
        case 3: 
            cout << "Anda melihat cahaya... Oh tunggu, apa itu...";
            break;
        default:
            cout << "Anda tidak berada di jalur pilihan! Ulangi pilihan!";
    cout << endl;

        
    cout << " --- JALAN KELUAR --- " << endl;
    cout << " Anda melihat sesuatu yang bersinar di tengah arena..." << endl;
    cout << " Terdapat sesuatu yang terkurung di dalamnya,dan terdapat mesin yang meminta Anda untuk Memasukkan sebuah angka..." << endl;

    cout << "Masukkan angka (minimal 5): " << endl;
    cout << "Sebuah cahaya bersinar dan di tanganmu kini terdapat sebuah diamond besar!" << endl;

    cout << " *** SELAMAT! ANDA ADALAH PEMENANG TURNAMEN TRIWIZARD! *** " << endl;    
    }

    return 0;

}