#include <iostream>
using namespace std;

void headerUtama()
{
    cout << "|====================================|" << endl;
    cout << "|                                    |" << endl;
    cout << "[        MODULE 4 - FUNCTION         ]" << endl;
    cout << "|                                    |" << endl;
    cout << "|====================================|" << endl;
}

void headerStore()
{
    cout << "#==========================#" << endl;
    cout << "|       TIVAIZ STORE       |" << endl;
    cout << "#==========================#" << endl;
}

void headerHalaman(char judul[])
{
    cout << "---------------------------" << endl;
    cout << "       " << judul << "        " << endl;
    cout << "---------------------------" << endl;
}

void headerMenu1()
{
    cout << "1. Input Barang" << endl;
    cout << "2. Hapus Barang" << endl;
    cout << "3. Edit Barang" << endl;
    cout << "4. Lihat Barang" << endl;
    cout << "0. Kembali" << endl;
    cout << "============================" << endl;
    cout << "Pilih menu: ";
}

void headerKalkulator()
{
    cout << "+==============================-+" << endl;
    cout << "|           K4LKUL4T0R          |" << endl;
    cout << "X==============================/ " << endl;
}

void tampilkanDetail(int i, char nama[][50], int stok[], int harga[])
{
    cout << "No          : " << i + 1 << endl;
    cout << "Nama Barang : " << nama[i] << endl;
    cout << "Stok Barang : " << stok[i] << endl;
    cout << "Harga/Stok  : Rp " << harga[i] << endl;
}

void inputBarang(char nama[][50], int stok[], int harga[], int &total)
{
    system("cls");
    headerStore();
    char judul[] = "INPUT BARANG";
    headerHalaman(judul);

    cout << "Nama Barang : ";
    cin.ignore();
    cin.getline(nama[total], 50);

    cout << "---------------------------" << endl;
    cout << "Stok (unit) : ";
    cin >> stok[total];

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Gagal] Stok harus berupa angka!" << endl;
        system("pause");
        return;
    }

    cout << "---------------------------" << endl;
    cout << "Harga (Rp)  : ";
    cin >> harga[total];

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Gagal] Harga harus berupa angka!" << endl;
        system("pause");
        return;
    }

    total++;
    cout << "---------------------------" << endl;
    cout << "[Berhasil] " << nama[total - 1] << " ditambahkan! (Total barang: " << total << ")" << endl;
    system("pause");
}

void hapusBarang(char nama[][50], int stok[], int harga[], int &total)
{
    system("cls");
    headerStore();
    char judul[] = "HAPUS BARANG";
    headerHalaman(judul);
    cout << "---------------------------------------" << endl;

    if (total == 0)
    {
        cout << "[Info] Belum ada barang di toko." << endl;
    }
    else
    {
        for (int i = 0; i < total; i++)
        {
            tampilkanDetail(i, nama, stok, harga);
            cout << "---------------------------------------" << endl;
        }

        int pil;
        cout << "Pilih nomor barang yang dihapus (1-" << total << "): ";
        cin >> pil;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "---------------------------------------" << endl;
            cout << "[Gagal] Input harus berupa angka!" << endl;
        }
        else if (pil < 1 || pil > total)
        {
            cout << "---------------------------------------" << endl;
            cout << "[Gagal] Nomor " << pil << " tidak valid! Pilih antara 1 sampai " << total << "." << endl;
        }
        else
        {
            int idx = pil - 1;
            char namaDihapus[50];
            for (int j = 0; j < 50; j++)
                namaDihapus[j] = nama[idx][j];

            for (int i = idx; i < total - 1; i++)
            {
                for (int j = 0; j < 50; j++)
                    nama[i][j] = nama[i + 1][j];
                stok[i] = stok[i + 1];
                harga[i] = harga[i + 1];
            }
            total--;
            cout << "---------------------------------------" << endl;
            cout << "[Berhasil] " << namaDihapus << " dihapus! (Total barang: " << total << ")" << endl;
        }
    }
    system("pause");
}

void editHarga(char nama[], int &harga)
{
    int lama = harga;
    cout << "--------------------------------" << endl;
    cout << "Harga baru (Rp): ";
    if (!(cin >> harga))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Gagal] Harga harus berupa angka!" << endl;
        return;
    }
    cout << "--------------------------------" << endl;
    cout << "[Berhasil] Harga " << nama << ": Rp " << lama << " -> Rp " << harga << endl;
}

void tambahStok(char nama[], int &stok)
{
    int lama = stok;
    int tam;
    cout << "--------------------------------" << endl;
    cout << "Jumlah tambah: ";
    if (!(cin >> tam))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Gagal] Stok harus berupa angka!" << endl;
        return;
    }
    stok += tam;
    cout << "--------------------------------" << endl;
    cout << "[Berhasil] Stok " << nama << ": " << lama << " -> " << stok << endl;
}

void kurangiStok(char nama[], int &stok)
{
    int lama = stok;
    int kur;
    cout << "--------------------------------" << endl;
    cout << "Jumlah kurang: ";
    if (!(cin >> kur))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Gagal] Stok harus berupa angka!" << endl;
        return;
    }
    if (stok - kur < 1)
    {
        cout << "--------------------------------" << endl;
        cout << "[Gagal] Stok tidak boleh kurang dari 1!" << endl;
    }
    else
    {
        stok -= kur;
        cout << "--------------------------------" << endl;
        cout << "[Berhasil] Stok " << nama << ": " << lama << " -> " << stok << endl;
    }
}

void editBarang(char nama[][50], int stok[], int harga[], int total)
{
    int pil;
    while (true)
    {
        system("cls");
        headerStore();
        char judul[] = "EDIT BARANG";
        headerHalaman(judul);

        if (total == 0)
        {
            cout << "[Info] Belum ada barang untuk diedit." << endl;
            system("pause");
            return;
        }

        for (int i = 0; i < total; i++)
        {
            tampilkanDetail(i, nama, stok, harga);
            cout << "---------------------------------------" << endl;
        }

        cout << "Pilih nomor barang yang diedit (1-" << total << "): ";
        if (!(cin >> pil))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Gagal] Input harus berupa angka!" << endl;
            system("pause");
            continue;
        }

        if (pil < 1 || pil > total)
        {
            cout << "[Gagal] Nomor tidak valid!" << endl;
            system("pause");
            continue;
        }

        int idx = pil - 1;
        int opsi = -1;

        while (true)
        {
            system("cls");
            headerStore();
            headerHalaman(judul);
            cout << "Barang: " << nama[idx] << endl;
            cout << "--------------------------------" << endl;
            cout << "1. Edit Harga\n2. Tambah Stok\n3. Kurangi Stok\n0. Kembali" << endl;
            cout << "--------------------------------\nPilih opsi: ";

            if (!(cin >> opsi))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "[Gagal] Input harus berupa angka!" << endl;
                system("pause");
                continue;
            }

            if (opsi == 1)
                editHarga(nama[idx], harga[idx]);
            else if (opsi == 2)
                tambahStok(nama[idx], stok[idx]);
            else if (opsi == 3)
                kurangiStok(nama[idx], stok[idx]);
            else if (opsi == 0)
                break;

            system("pause");
        }
        break;
    }
}

void lihatBarang(char nama[][50], int stok[], int harga[], int total)
{
    system("cls");
    headerStore();
    char judul[] = "LIHAT BARANG";
    headerHalaman(judul);

    if (total == 0)
    {
        cout << "Toko masih kosong!" << endl;
    }
    else
    {
        for (int i = 0; i < total; i++)
        {
            tampilkanDetail(i, nama, stok, harga);
            double totalHargaBarang = (double)stok[i] * harga[i];
            cout << "Total Harga : Rp " << totalHargaBarang << endl;
            cout << "-----------------------" << endl;
        }
        cout << "Total barang: " << total << " jenis" << endl;
    }
    system("pause");
}

void kalkulator()
{
    int p;
    while (true)
    {
        system("cls");
        headerKalkulator();
        cout << "1. Operasi Dasar (+, -, *, /)\n2. Faktorial\n0. Kembali" << endl;
        cout << "================================" << endl;
        cout << "Pilih menu: ";

        if (!(cin >> p))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Gagal] Input harus berupa angka!" << endl;
            system("pause");
            continue;
        }
        if (p == 0)
        {
            return;
        }

        if (p == 1)
        {
            system("cls");
            headerKalkulator();
            double a, b;
            char op;
            cout << "--------------------------------------" << endl;
            cout << "Operator (+, -, *, /) : ";
            cin >> op;
            if (op != '+' && op != '-' && op != '*' && op != '/')
            {
                cout << "[Gagal] Operator tidak valid!" << endl;
            }
            else
            {
                cout << "--------------------------------------" << endl;
                cout << "Angka pertama : ";
                cin >> a;
                cout << "--------------------------------------" << endl;
                cout << "Angka kedua   : ";
                cin >> b;
                cout << "--------------------------------------" << endl;
                if (op == '+')
                    cout << a << " + " << b << " = " << a + b << endl;
                else if (op == '-')
                    cout << a << " - " << b << " = " << a - b << endl;
                else if (op == '*')
                    cout << a << " * " << b << " = " << a * b << endl;
                else if (op == '/')
                {
                    if (b != 0)
                        cout << a << " / " << b << " = " << a / b << endl;
                    else
                        cout << "[Gagal] Tidak bisa dibagi nol!" << endl;
                }
            }
        }
        else if (p == 2)
        {
            system("cls");
            headerKalkulator();
            int n;
            cout << "N : ";
            cin >> n;
            if (n < 0)
                cout << "[Gagal] Faktorial tidak bisa untuk angka negatif!";
            else
            {
                unsigned long long hasil = 1;
                for (int i = 1; i <= n; i++)
                    hasil *= i;
                cout << "--------------------------------------" << endl;
                cout << n << "! = " << hasil << endl;
            }
        }
        else
        {
            cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 2." << endl;
        }
        cout << endl;
        system("pause");
    }
}

int main()
{
    char namaBarang[100][50];
    int stokBarang[100], hargaBarang[100], total = 0, menu, sub;

    do
    {
        system("cls");
        headerUtama();
        cout << "1. TIVAIZ Store\n2. Kalkulator TIVAIZ\n0. Keluar" << endl;
        cout << "=============================" << endl;
        cout << "Pilih menu: ";
        cin >> menu;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Gagal] Input harus berupa angka!" << endl;
            system("pause");
            menu = -1;
        }

        else if (menu < 0 || menu > 2)
        {
            cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 2." << endl;
            system("pause");
            menu = -1;
            continue;
        }

        if (menu == 1)
        {
            do
            {
                system("cls");
                headerStore();
                headerMenu1();

                if (!(cin >> sub))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    cout << "[Gagal] Input harus berupa angka!" << endl;
                    system("pause");
                    sub = -1;
                    continue;
                }

                if (sub < 0 || sub > 4)
                {
                    cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 4." << endl;
                    system("pause");
                    continue;
                }

                if (sub == 1)
                    inputBarang(namaBarang, stokBarang, hargaBarang, total);
                else if (sub == 2)
                    hapusBarang(namaBarang, stokBarang, hargaBarang, total);
                else if (sub == 3)
                    editBarang(namaBarang, stokBarang, hargaBarang, total);
                else if (sub == 4)
                    lihatBarang(namaBarang, stokBarang, hargaBarang, total);
                else if (sub != 0)
                {
                    cout << "[Gagal] Menu tidak valid!" << endl;
                    system("pause");
                }
                else if (sub < 0 || sub > 4)
                {
                    cout << "[Gagal] Menu tidak valid! Pilih antara 0 sampai 4." << endl;
                    system("pause");
                }

            } while (sub != 0);
        }
        else if (menu == 2)
        {
            kalkulator();
        }
        else if (menu == 0)
        {
            system("cls");
            cout << "\nSampai jumpa! Terima kasih telah menggunakan Toko TIVAIZ!" << endl;
            cout << "================================" << endl;
            break;
        }
    } while (menu != 0);

    return 0;
}