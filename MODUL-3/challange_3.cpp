#include <iostream>
using namespace std;

int main()
{
    int ukuran;
    cout << "[TASK 3/3] ALIGN NAVIGATION MATRIX - Engine Core " << endl;
    cout << "<< Sistem navigasi mati total akibat sabotase. " << endl;
    cout << "<< Rekonstruksi matriks koordinat sekarang! " << endl;

    cout << "[ MATRIX NAVIGATION ]" << endl;
    cout << "Masukkan ukuran Navigation Matrix (max 5): ";
    cin >> ukuran;
    cout << "------------------------------------------------" << endl;
    cout << "Odd Coordinate Matrix (Ganjil)" << endl;

    int matriks[3][3];
    int angka = 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            matriks[i][j] = angka++;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << matriks[i][j] << " ";
    }

    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            cout << matriks[j][i] << " ";

    cout << "Even Coordinate Mtrix (Genap)" << endl;

    cout << "Matriks koordinat telah dipulihkan";
    cout << "Lakukanlah proses-proses berikut ini untuk membuat matriks koordinat lebih akurat!";
    cout << "1. Coordinate Matrix Integration";
    cout << "2. Matrix Transpose";
    cout << "3. Snake Traverse";

    cout << "Tekan ENTER untuk melanjutkan...";

    return 0;
}