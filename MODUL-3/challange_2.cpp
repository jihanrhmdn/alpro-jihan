#include <iostream>
using namespace std;

int main()
{
    int kata;
    cout << "Konsol teks mengalami interferensi kosmik.";
    cout << "<< Verifikasi integritas data teks sebelum terlambat! ";

    cout << "[ Verifikasi Teks ]" << endl;
    cout << "Masukkan Kalimat ke-1: ";
    cin >> kata;
    cout << "----------------------------------------" << endl;

    
    const int max = 100;
    string kalimat;
    char nama[max];

    int panjang = 0;
    int count = 0;

    cin.getline(nama, max);
    for (panjang; nama[panjang] != 0; panjang++)
    {
        count++;
    }
    cout << panjang << endl;

    cout << "Hasil Kalimat ke-1: " << endl;
    cout << "Jumlah Huruf: " << endl;
    cout << "1. Asli: " << endl;
    cout << "2. Inverse: " << endl;
    cout << "3. Snap Awal-Akhir: " << endl;
    cout << "4. Palindrome?: " << endl;

    cout << "----------------------------------------";
    cout << "Hasil Kalimat ke-2: ";
    cout << "Jumlah Huruf: ";
    cout << "1. Asli: ";
    cout << "2. Inverse: ";
    cout << "3. Snap Awal-Akhir: ";
    cout << "4. Palindrome?: ";

    cout << "----------------------------------------";
    cout << "Hasil Kalimat ke-3: ";
    cout << "Jumlah Huruf: ";
    cout << "1. Asli: ";
    cout << "2. Inverse: ";
    cout << "3. Snap Awal-Akhir: ";
    cout << "4. Palindrome?: ";

    return 0;
}