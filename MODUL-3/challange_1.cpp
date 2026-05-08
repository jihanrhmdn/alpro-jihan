#include <iostream>
using namespace std;

int main()
{
    cout << "[TASK 1/3] DECODE SIGNAL - Communication Room" << endl;
    cout << ">> Kirim Sinyal terenkripsi dan dekripsi balasan dari Bumi." << endl;
    cout << endl;

    cout << "[ ENKRIPSI ]" << endl;
    cout << endl;

    // input key
    int key;
    while (true)
    {
        string inputKey;
        cout << "Masukkan key         : ";
        cin >> inputKey;
        cin.ignore();

        bool valid = true;
        int start = 0;

        if (inputKey.empty())
        {
            valid = false;
        }
        else if (inputKey[0] == '-')
        {
            valid = false;
        }
        else if (inputKey[0] == '+')
        {
            start = 1;
        }

        if (valid)
        {
            for (int i = start; i < (int)inputKey.length(); i++)
            {
                if (inputKey[i] < '0' || inputKey[i] > '9')
                {
                    valid = false;
                    break;
                }
            }
        }

        if (valid)
        {
            key = 0;
            for (int i = start; i < (int)inputKey.length(); i++)
            {
                key = key * 10 + (inputKey[i] - '0');
            }
            if (key > 0)
                break;
        }

        cout << "  [!] Key harus bilangan bulat positif. Coba lagi." << endl;
    }

    // input teks enkripsi
    string teks;
    while (true)
    {
        cout << "Masukkan teks        : ";
        getline(cin, teks);
        if (!teks.empty())
            break;
        cout << "  [!] Input tidak boleh kosong. Coba lagi." << endl;
    }

    int panjang = teks.length();
    int baris = panjang / 4;
    if (panjang % 4 != 0)
        baris++;

    // matriks baris per baris
    char matriksEnk[100][4];
    for (int i = 0; i < baris; i++)
        for (int j = 0; j < 4; j++)
            matriksEnk[i][j] = '_';

    int idx = 0;
    for (int i = 0; i < baris; i++)
        for (int j = 0; j < 4; j++)
            if (idx < panjang)
                matriksEnk[i][j] = teks[idx++];

    // menampilkan matriks enkripsi
    cout << endl;
    cout << "Matriks enkripsi:" << endl;
    for (int i = 0; i < baris; i++)
    {
        cout << "  ";
        for (int j = 0; j < 4; j++)
        {
            cout << matriksEnk[i][j];
            if (j < 3)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    // per kolom
    string sebelumShift = "";
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < baris; i++)
            sebelumShift += matriksEnk[i][j];

    cout << "Enkripsi sebelum ditambah key : " << sebelumShift << endl;

    // Caesar Cipher +key
    string sesudahShift = "";
    for (int i = 0; i < (int)sebelumShift.length(); i++)
        sesudahShift += (char)(sebelumShift[i] + key);

    cout << "Enkripsi setelah ditambah key : " << sesudahShift << endl;

    // DEKRIPSI
    cout << endl;
    cout << "[ DEKRIPSI ]" << endl;
    cout << endl;

    // input teks terenkripsi
    string teksEnkripsi;
    while (true)
    {
        cout << "Masukkan teks terenkripsi    : ";
        getline(cin, teksEnkripsi);
        if (!teksEnkripsi.empty())
            break;
        cout << "  [!] Input tidak boleh kosong. Coba lagi." << endl;
    }

    // Caesar Cipher balik -key
    string setelahShiftBalik = "";
    for (int i = 0; i < (int)teksEnkripsi.length(); i++)
        setelahShiftBalik += (char)(teksEnkripsi[i] - key);

    cout << "Dekripsi setelah dikurang key : " << setelahShiftBalik << endl;
    cout << endl;

    // susun ke matriks kolom per kolom
    int panjangDek = setelahShiftBalik.length();
    int barisDek = panjangDek / 4;
    if (panjangDek % 4 != 0)
        barisDek++;

    char matriksDek[100][4];
    for (int i = 0; i < barisDek; i++)
        for (int j = 0; j < 4; j++)
            matriksDek[i][j] = '_';

    int idxDek = 0;
    for (int j = 0; j < 4; j++)
        for (int i = 0; i < barisDek; i++)
            if (idxDek < panjangDek)
                matriksDek[i][j] = setelahShiftBalik[idxDek++];

    // menampilkan matriks dekripsi
    cout << "Matriks Dekripsi:" << endl;
    for (int i = 0; i < barisDek; i++)
    {
        cout << "  ";
        for (int j = 0; j < 4; j++)
        {
            cout << matriksDek[i][j];
            if (j < 3)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Baca baris per baris, abaikan '_'
    string hasilDekripsi = "";
    for (int i = 0; i < barisDek; i++)
        for (int j = 0; j < 4; j++)
            if (matriksDek[i][j] != '_')
                hasilDekripsi += matriksDek[i][j];

    cout << "Hasil Dekripsi final          : " << hasilDekripsi << endl;

    cout << endl;
    cout << ">> [TASK 1/3] COMPLETE - Signal channel restored." << endl;
    cout << ">> Tekan ENTER untuk melanjutkan ke [ TASK 2 ]!." << endl;
    cin.get();

    return 0;
}