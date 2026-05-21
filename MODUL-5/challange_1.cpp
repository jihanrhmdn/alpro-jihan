#include <iostream>
using namespace std;

void menu (){
    cout << "==================================================================" << endl;
    cout << "                SISTEM MANAJEMEN RS GAZACARE PLUS                 " << endl;
    cout << "==================================================================" << endl;
    cout << " [1] Daftarkan Pasien Baru " << endl;
    cout << " [2] Lihat Semua Pasien " << endl;
    cout << " [3] Cari Pasien " << endl;
    cout << " [4] Cari Pasien " << endl;
    cout << " [0] Keluar" << endl;
    cout << "==================================================================" << endl;
    cout << "Pilihan :" << endl;
}

struct Pasien {
    string id;
    int nim;
    string nm;
    char jk;
};

struct TanggalLahir {
    int tgl;
    int bln;
    int thn;
};

struct Alamat {
    string jln;
    string lur;
    string kot;
    string prov;
    int kode;
};

void tampilPasien(Pasien a) {
    cout << "      ID      : " << a.id << "\n";
    cout << "      NIK       : " << a.nim << "\n";
    cout << "      Nama       : " << a.nm << "\n";
    cout << "      JK       : " << a.jk << "\n";
}

void tampilTanggalLahir(TanggalLahir b){
    cout << "      Tanggal      : " << b.tgl << "\n";
    cout << "      Bulan        : " << b.bln << "\n";
    cout << "      Tahun       : " << b.thn << "\n";
}

void tampilAlamat(Alamat c){
    cout << "      Jalan      : " << c.jln << "\n";
    cout << "      Kelurahan   : " << c.lur << "\n";
    cout << "      Kota       : " << c.kot << "\n";
    cout << "      Provinsi     : " << c.prov << "\n";
    cout << "      Kode Pos     : " << c.kode << "\n";
}

int main() {
    
}
