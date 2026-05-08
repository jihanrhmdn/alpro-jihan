#include <iostream>
using namespace std;

int main()
{
    int ukuran;
    cout << "[TASK 3/3] ALIGN NAVIGATION MATRIX - Engine Core " << endl;
    cout << "<< Sistem navigasi mati total akibat sabotase. " << endl;
    cout << "<< Rekonstruksi matriks koordinat sekarang! " << endl;
    cout << endl;
    cout << "[ MATRIX NAVIGATION ]" << endl;
    cout << endl;

    do
    {
        cout << "Masukkan ukuran Navigation Matrix (max 5): ";
        cin >> ukuran;
        if (ukuran < 3 || ukuran > 5)
            cout << "[!] Input tidak valid. Masukkan ukuran antara 3 sampai 5." << endl
                 << endl;
    } while (ukuran < 3 || ukuran > 5);

    cout << "------------------------------------------------" << endl;

    // isi nilai matriks
    int ganjil[5][5], genap[5][5];

    int angkaGanjil = 1;
    for (int i = 0; i < ukuran; i++)     // baris
        for (int j = 0; j < ukuran; j++) // kolom
        {
            ganjil[i][j] = angkaGanjil;
            angkaGanjil += 2;
        }

    int angkaGenap = 2;
    for (int i = 0; i < ukuran; i++)
        for (int j = 0; j < ukuran; j++)
        {
            genap[i][j] = angkaGenap;
            angkaGenap += 2;
        }

    // menampilkan matriks
    cout << "Odd Coordinate Matrix (Ganjil)" << endl;
    for (int i = 0; i < ukuran; i++)
    {
        for (int j = 0; j < ukuran; j++)
        {
            if (ganjil[i][j] < 10)
                cout << "0";
            cout << ganjil[i][j];
            if (j < ukuran - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Even Coordinate Matrix (Genap):" << endl;
    for (int i = 0; i < ukuran; i++)
    {
        for (int j = 0; j < ukuran; j++)
        {
            if (genap[i][j] < 10)
                cout << "0";
            cout << genap[i][j];
            if (j < ukuran - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------------------" << endl;
    cout << endl;

    cout << "Matriks koordinat telah dipulihkan" << endl;
    cout << "Lakukanlah proses-proses berikut ini untuk membuat matriks koordinat lebih akurat!" << endl;
    cout << "1. Coordinate Matrix Integration" << endl;
    cout << "2. Matrix Transpose" << endl;
    cout << "3. Snake Traverse" << endl;
    cout << endl;
    cout << "Tekan ENTER untuk melanjutkan...";
    cin.ignore();
    cin.get();

    // OPERASI 1: FUSION MATRIX (menggabungkan dua matriks)
    int fusion[5][5];
    for (int i = 0; i < ukuran; i++)
        for (int j = 0; j < ukuran; j++)
            fusion[i][j] = ganjil[i][j] + genap[i][j];

    cout << endl;
    cout << "COORDINATE MATRIX INTEGRATION:" << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < ukuran; i++)
    {
        for (int j = 0; j < ukuran; j++)
        {
            if (fusion[i][j] < 10)
                cout << "0";
            cout << fusion[i][j];
            if (j < ukuran - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    // OPERASI 2: TRANSPOSE (menukar baris menjadi kolom, sebaliknya)
    int transpose[5][5];
    for (int i = 0; i < ukuran; i++)
        for (int j = 0; j < ukuran; j++)
            transpose[i][j] = fusion[j][i];

    cout << "MATRIX TRANSPOSE:" << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < ukuran; i++)
    {
        for (int j = 0; j < ukuran; j++)
        {
            if (transpose[i][j] < 10)
                cout << "0";
            cout << transpose[i][j];
            if (j < ukuran - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    // OPERASI 3: SNAKE TRAVERSE (matriks zig zag / ular)
    int traverse[5][5];
    for (int i = 0; i < ukuran; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j < ukuran; j++)
                traverse[i][j] = transpose[i][j];
        }
        else
        {
            for (int j = 0; j < ukuran; j++)
                traverse[i][j] = transpose[i][ukuran - 1 - j];
        }
    }

    cout << "SNAKE TRAVERSE:" << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < ukuran; i++)
    {
        for (int j = 0; j < ukuran; j++)
        {
            if (traverse[i][j] < 10)
                cout << "0";
            cout << traverse[i][j];
            if (j < ukuran - 1)
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "------------------------------------------------" << endl;
    cout << endl;
    cout << ">> [TASK 3/3] COMPLETE - Navigation matrix aligned." << endl;
    cout << "============================================================" << endl;
    cout << "  ALL TASKS COMPLETE - SHIP SYSTEMS RESTORED" << endl;
    cout << "============================================================" << endl;

    return 0;
}