#include <iostream>
using namespace std;

int main()
{
    int n, umur, perlindungan = 3;
    char pilihan;

    cout << "=== GOBLET OF FIRE: TURNAMEN TRIWIZARD ===" << endl;
    cout << "Masukkan umur Anda: ";
    cin >> umur;

    if (umur < 17)
    {
        cout << "Piala Api menolak Anda! Umur terlalu kecil" << endl;
        return 0;
    }
    else
    {
        cout << "Piala Api menyala! Anda terpilih sebagai Triwizard Champions." << endl;
        system("pause");
        system("cls");
    }

    cout << "--- TUGAS 1: NAGA HUNGARIAN HORNTAIL ---" << endl;

    bool naga = false;
    while (!naga)
    {
        perlindungan = 3;
        while (perlindungan > 0)
        {
            cout << "Sisa perlindungan sihir: " << perlindungan << " kali." << endl;
            cout << "Pilih strategi (a: Sembunyi, b: Panggil Sapu): ";
            cin >> pilihan;

            switch (pilihan)
            {
            case 'a':
                cout << "Naga menyemburkan api! Anda terluka ";
                perlindungan--;
                break;
            case 'b':
                cout << "Berhasil! Anda mengambil Telur Emas! " << endl;
                naga = true;
                system("pause");
                system("cls");
                break;
            default:
                cout << "Pilihan tidak valid! Ulangi pilihan." << endl;
                system("pause");
                continue;
            }

            cout << endl;

            if (naga)
                break;
        }
        if (!naga)
        {
            cout << ">> KESEMPATAN HABIS! Anda ditarik keluar arena oleh pawang naga." << endl;
            cout << ">> MENGULANG TUGAS 1 DARI AWAL..." << endl;
            system("pause");
            system("cls");
        }
    }

    bool danau = false;
    while (!danau) //not false = true, not true = false 
    {
        cout << "--- TUGAS 2: DANAU HITAM ---" << endl;
        int waktu = 10;
        while (waktu < 60)
        {
            cout << "Menit " << waktu << "... Ada Grindylow! (l: Lawan, h: Hindari): ";
            cin >> pilihan;

            if (pilihan == 'h')
            {
                waktu += 10;
                cout << "Lolos dari Grindylow.";
            }
            else if (pilihan == 'l')
            {
                cout << "Oksigen Anda habis karena kelelahan bertarung!" << endl;
                break;
            }
            else
            {
                cout << "Pilihan tidak valid! Ulangi pilihan." << endl;
                system("pause");
                continue;
            }

            cout << endl;
        }
        if (waktu >= 60)
        {
            cout << "Tepat 60 menit! Anda menyelamatkan sandera." << endl;
            danau = true;
            system("pause");
            system("cls");
        }
        else
        {
            cout << ">> WAKTU/OKSIGEN HABIS! Putri duyung membawa Anda ke permukaan." << endl;
            cout << ">> MENGULANG TUGAS 2 DARI AWAL..." << endl;
            system("pause");
            system("cls");
        }
    }

    bool tugas3_selesai = false;

    while (!tugas3_selesai)
    {
        bool labirin = false;
        int langkah = 0, toleransi = 2, pilihan3;

        while (!labirin && toleransi > 0)
        {
            cout << endl
                 << "--- TUGAS 3: LABIRIN ---" << endl;
            cout << "Sisa toleransi kesalahan: " << toleransi << endl;
            cout << "Langkah ditempuh: " << langkah << endl;
            cout << "Pilih arah (1: Kiri, 2: Kanan, 3: Lurus): ";
            cin >> pilihan3;

            switch (pilihan3)
            {
            case 1:
                toleransi--;
                cout << "Terkena Akar Berbisa! Sisa toleransi kesalahan: " << toleransi << endl;
                langkah = 0;
                system("pause");

                if (toleransi == 0)
                {
                    cout << endl;
                    cout << ">> KESEMPATAN HABIS! Labirin berubah bentuk dan menendang Anda ke pintu masuk." << endl;
                    cout << ">> MENGULANG TUGAS 3 DARI AWAL..." << endl;
                    system("pause");
                    system("cls");
                }
                break;

            case 2:
                cout << "Jalan aman, Anda semakin dalam. " << endl;
                langkah++;
                system("pause");

                if (langkah >= 3)
                {
                    cout << "Anda melihat cahaya... Oh tunggu, apa itu..." << endl;
                    system("pause");
                    system("cls");
                    labirin = true;
                    tugas3_selesai = true;
                }
                break;

            case 3:
                cout << "Anda melihat cahaya... Oh tunggu, apa itu..." << endl;
                system("pause");
                system("cls");
                labirin = true;
                tugas3_selesai = true;
                break;

            default:
                cout << "Anda tidak berada di jalur pilihan! Ulangi pilihan!" << endl;
                system("pause");
                break;
            }
        }
    }

    if (tugas3_selesai)
    {
        cout << " --- JALAN KELUAR --- " << endl;
        cout << " Anda melihat sesuatu yang bersinar di tengah arena..." << endl;
        cout << " Terdapat sesuatu yang terkurung di dalamnya, dan terdapat mesin yang meminta Anda untuk Memasukkan sebuah angka..." << endl;
        cout << endl;

        do
        {
            cout << "Masukkan angka (minimal 5): ";
            cin >> n;
        } while (n < 5);
        cout << "Sebuah cahaya bersinar dan di tanganmu kini terdapat sebuah diamond besar!" << endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int k = 1; k <= (2 * i - 1); k++)
            {
                cout << "*";
            }
            cout << endl;
        }
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int k = 1; k <= (2 * i - 1); k++)
            {
                cout << "*";
            }
            cout << endl;
        }
        cout << endl;
        cout << " *** SELAMAT! ANDA ADALAH PEMENANG TURNAMEN TRIWIZARD! *** " << endl;
        cout << "-----------------------------------------------------------" << endl;
    }
    return 0;
}