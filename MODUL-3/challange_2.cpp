#include <iostream>
using namespace std;

int main()
{
    char ulang;
    cout << "[TASK 2/3] REPAIR TEXT CONSOLE - Captain's Bridge" << endl;
    cout << ">> Konsol teks mengalami interferensi kosmik." << endl;
    cout << ">> Verifikasi integritas data teks sebelum terlambat!" << endl;
    cout << endl;

    do
    {
        cout << endl;
        cout << "[ Verifikasi Teks ]" << endl;
        cout << endl;
        for (int k = 1; k <= 3; k++)
        {
            char kalimat[200];
            cout << "Masukkan Kalimat ke-" << k << " : ";
            cin.getline(kalimat, 200);
            cout << "------------------------------------------------" << endl;

            // hapus spasi
            char bersih[200];
            int idx = 0;
            for (int i = 0; kalimat[i] != '\0'; i++)
            {
                if (kalimat[i] != ' ')
                    bersih[idx++] = kalimat[i];
            }
            bersih[idx] = '\0';

            int panjang = idx; // jumlah huruf tanpa spasi

            cout << "Hasil untuk Kalimat ke-" << k << ":" << endl;
            cout << "Jumlah Huruf         : " << panjang << endl;

            // 1. ASLI
            cout << "1. Asli              : ";
            for (int i = 0; i < panjang; i++)
            {
                cout << bersih[i];
                if (i < panjang - 1)
                    cout << ", ";
            }
            cout << endl;

            // 2. INVERSE
            cout << "2. Inverse           : ";
            for (int i = panjang - 1; i >= 0; i--)
            {
                cout << bersih[i];
                if (i > 0)
                    cout << ", ";
            }
            cout << endl;

            // 3. SWAP AWAL-AKHIR
            char swap_str[200];
            for (int i = 0; i < panjang; i++)
                swap_str[i] = bersih[i];
            swap_str[panjang] = '\0';

            // tukar karakter pertama dan terakhir
            char temp = swap_str[0];
            swap_str[0] = swap_str[panjang - 1];
            swap_str[panjang - 1] = temp;

            cout << "3. Swap Awal-Akhir   : ";
            for (int i = 0; i < panjang; i++)
                cout << swap_str[i];
            cout << endl;

            // 4. PALINDROME
            bool palindrome = true;

            if (panjang == 0)
            {
                palindrome = false;
            }
            else
            {
                for (int i = 0; i < panjang / 2; i++)
                {
                    if (bersih[i] != bersih[panjang - 1 - i])
                    {
                        palindrome = false;
                        break;
                    }
                }
            }

            cout << "4. Palindrome?       : " << (palindrome ? "YES" : "NO") << endl;
            cout << endl;
        }

        // opsi untuk ulang
        cout << "============================================" << endl;
        do
        {
            cout << "Verifikasi Teks Lain? (y/n): ";
            cin >> ulang;
            cin.ignore();
            if (ulang != 'y' && ulang != 'n')
                cout << "[!] Input tidak valid. Masukkan y atau n." << endl;
        } while (ulang != 'y' && ulang != 'n');

    } while (ulang == 'y');
    cout << endl;
    cout << ">> [TASK 2/3] COMPLETE - Text console back online." << endl;
    cout << ">> Tekan ENTER untuk melanjutkan ke [ TASK 3 ]!";

    return 0;
}