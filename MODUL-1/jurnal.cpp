#include <iostream>
using namespace std;

int main (){
    int Beras, Telur, MinyakGoreng, TotalBelanja, TotalUang, TotalKembalian, sisa, pecahan100000, pecahan50000, pecahan20000, pecahan10000, pecahan5000, pecahan2000, pecahan1000l, pecahan1000k, pecahan500, pecahan200, pecahan100;
    double Pajak, TotalBelanja2;

    cout << "================================= " << endl;
    cout << "|    TOKO SEMBAKO JAYA ABADI    | " << endl;
    cout << "================================= " << endl;
    cout << "[Bina]: Than, masukin harga barangnya Rendy di program ini! " << endl;
    cout << "Harga Beras (Rp)\t\t: ";
    cin >> Beras; 
    cout << "Harga Telur (Rp)\t\t: ";
    cin >> Telur;
    cout << "Harga Minyak Goreng (Rp)\t: ";
    cin >> MinyakGoreng; 
    cout << endl;
   
    TotalBelanja = Beras + Telur + MinyakGoreng;
    cout << "Total Belanja Sebelum Pajak \t: " <<TotalBelanja<< endl;

    Pajak = 0.25;
    
    TotalBelanja2 = (TotalBelanja * Pajak) + TotalBelanja;
    cout << "Total Belanja (+ PPN 25%) \t: " << TotalBelanja2 << endl;
    
    cout << "Total Uang \t\t\t: ";
    cin >> TotalUang;
    
    TotalKembalian = TotalUang - TotalBelanja2;
    sisa = TotalKembalian;
    cout << endl;

    pecahan100000 = sisa / 100000; sisa %= 100000;
    pecahan50000  = sisa / 50000;  sisa %= 50000;
    pecahan20000  = sisa / 20000;  sisa %= 20000;
    pecahan10000  = sisa / 10000;  sisa %= 10000;
    pecahan5000   = sisa / 5000;   sisa %= 5000;
    pecahan1000l   = sisa / 1000;   sisa %= 1000;
    pecahan1000k  = sisa / 1000;   sisa %= 1000;
    pecahan500    = sisa / 500;    sisa %= 500;
    pecahan200    = sisa / 200;    sisa %= 200;
    pecahan100    = sisa / 100;    sisa %= 100;

    cout << "======================================== " << endl;
    cout << "|            STRUK KEMBALIAN           | " << endl;
    cout << "======================================== " << endl;
    cout << "[Bina]: Nih, Than. Rincian kembaliannya: " << endl;
    cout << "Total Kembalian : Rp " << TotalKembalian << endl;
    cout << "---------------------------------------" <<  endl;
    cout << "- Rp 100.000 : " << pecahan100000 << " lembar" << endl;
    cout << "- Rp 50.000  : " << pecahan50000 << " lembar" << endl;
    cout << "- Rp 20.000  : " << pecahan20000 << " lembar" << endl;
    cout << "- Rp 10.000  : " << pecahan10000 << " lembar" << endl;
    cout << "- Rp 5.000   : " << pecahan5000 << " lembar" << endl;
    cout << "- Rp 1.000   : " << pecahan1000l << " lembar" << endl;
    cout << "- Rp 1.000   : " << pecahan1000k << " koin" << endl;
    cout << "- Rp 500     : " << pecahan500 << " koin" << endl;
    cout << "- Rp 200     : " << pecahan200 << " koin" << endl;
    cout << "- Rp 100     : " << pecahan100 << " koin" << endl;
    cout << "---------------------------------------" <<  endl;
    cout << "[Fathan]: Aman! Sisa receh tak terpecahnya: Rp 0" << endl;
    cout << "Ini mau di Donasikan ga Ren?" << endl;
    cout << "[Rendy]: GAS" << endl;
    cout << "===================================="<< endl;

    return 0;
}