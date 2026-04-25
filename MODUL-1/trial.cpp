#include <iostream>
using namespace std;

int main()
{
    int NIM, UTS, UAS, Tugas, NilaiBawah, NilaiAtas,
        SKS, SisaSKS, TotalSKS, SKS1Semester, SemesterPenuh, ascii, shift; 
    char grade, upper, enkripsi;
    float NilaiAkhir;

    cout << "|========== SISTEM NILAI AKADEMIK ==========|" << endl;
    cout << "Masukkan NIM\t\t: ";
    cin >> NIM;
    cout << "Nilai UTS\t\t: ";
    cin >> UTS;
    cout << "Nilai UAS\t\t: ";
    cin >> UAS;
    cout << "Nilai Tugas\t\t: ";
    cin >> Tugas;
    cout << "--------------------------------------------" << endl;

    NilaiAkhir = (float)((UTS * 30) + (UAS * 40) + (Tugas * 30)) / 100;
    cout.precision(2);
    cout << fixed;
    NilaiBawah = (int)NilaiAkhir;
    NilaiAtas = (int)NilaiAkhir;

    cout << "Nilai Akhir\t\t: " << NilaiAkhir << endl;
    cout << "Nilai Bulat Bawah\t: " << NilaiBawah << endl;
    cout << "Nilai Bulat Atas\t: " << NilaiAtas << endl;
    cout << "--------------------------------------------" << endl;

    TotalSKS = 144;
    cout << "SKS Ditempuh\t\t: ";
    cin >> SKS;

    SisaSKS = TotalSKS - SKS;
    cout << "Sisa SKS\t\t: " << SisaSKS << endl;

    SKS1Semester = 18;
    SemesterPenuh = SisaSKS / SKS1Semester;
    SisaSKS %= SKS1Semester;

    cout << "   Semester Penuh\t: " << SemesterPenuh << endl;
    cout << "   SKS Sisa\t\t: " << SisaSKS << endl;
    cout << "--------------------------------------------" << endl;

    cout << "Kode Grade (lowercase)\t: ";
    cin >> grade;

    upper = grade - 32;
    ascii = upper;
    shift = NIM % 10;
    enkripsi = 'A' + (upper - 'A' + shift) % 26;

    cout << "Uppercase (manual)\t: " << upper << endl;
    cout << "Nilai ASCII\t\t: " << ascii << endl;
    cout << "Shift (Akhir NIM)\t: " << shift << endl;
    cout << "Hasil Enkripsi)\t\t: " << enkripsi << endl;
    cout << "|===========================================| " << endl;

    return 0;
}