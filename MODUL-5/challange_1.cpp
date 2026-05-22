#include <iostream>
using namespace std;

const int MAX_PASIEN = 100;
const int MAX_ALERGI = 5;
const int TARIF_PER_HARI = 75000;

#define MERAH  "\033[31m"
#define RESET  "\033[0m"

struct TanggalLahir {
    int tanggal;
    int bulan;
    int tahun;
};

struct TanggalMasuk {
    int tanggal;
    int bulan;
    int tahun;
};

struct Alamat {
    string jalan;
    string kelurahan;
    string kota;
    string provinsi;
    int kodePos;
};

struct Alergi {
    string alergen;
    string reaksi;
};

struct Pasien {
    int id;
    string nik;
    string nama;
    char jenisKelamin;
    char golonganDarah;
    string noTelp;
    TanggalLahir tanggalLahir;
    Alamat alamat;
    bool pesertaBPJS;
    int jumlahAlergi;
    Alergi daftarAlergi[MAX_ALERGI];
    TanggalMasuk tanggalMasuk;
    bool sudahPulang;
};

Pasien daftarPasien[MAX_PASIEN];
int totalPasien = 0;

void bersihkanLayar() {
    system("cls");
}

void tekanEnterUntukLanjut() {
    system("pause");
    system("cls");
}

int hitungLamaRawat(TanggalMasuk tanggalMasuk, int tanggalKeluar, int bulanKeluar, int tahunKeluar) {
    int hariMasuk  = tanggalMasuk.tahun * 360 + tanggalMasuk.bulan * 30 + tanggalMasuk.tanggal;
    int hariKeluar = tahunKeluar * 360 + bulanKeluar * 30 + tanggalKeluar;
    int selisih = hariKeluar - hariMasuk;
    if (selisih <= 0) selisih = 1;
    return selisih;
}

// Cek apakah string hanya berisi digit
bool hanyaDigit(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Ubah string angka ke int
int stringKeInt(const string& s) {
    int hasil = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        hasil = hasil * 10 + (s[i] - '0');
    }
    return hasil;
}

// cek apakah nik sudah terdaftar atau belum
bool nikSudahAda(const string& nikBaru) {
    for (int i = 0; i < totalPasien; i++) {
        // NIK dianggap duplikat jika NIK-nya sama DAN pasien tersebut belum dipulangkan
        if (daftarPasien[i].nik == nikBaru && !daftarPasien[i].sudahPulang) {
            return true; 
        }
    }
    return false;
}

void tampilMenu() {
    time_t sekarang = time(0);
    tm* lt = localtime(&sekarang);
    int hari  = lt->tm_mday;
    int bulan = lt->tm_mon + 1;
    int tahun = lt->tm_year + 1900;

    cout << "=================================================================" << endl;
    cout << "           SISTEM MANAJEMEN RS GAZACARE PLUS                     " << endl;
    cout << "=================================================================" << endl;
    cout << "                                                Tanggal " << hari << "/" << bulan << "/" << tahun << "     " << endl;
    cout << "  [1] Daftarkan Pasien Baru" << endl;
    cout << "  [2] Lihat Semua Pasien" << endl;
    cout << "  [3] Cari Pasien" << endl;
    cout << "  [4] Pulangkan Pasien" << endl;
    cout << "  [0] Keluar" << endl;
    cout << "=================================================================" << endl;
    cout << "Pilihan: ";
}

void tampilPasien(Pasien pasien) {
    cout << " ID      : " << pasien.id
         << "                               Tgl Masuk "
         << pasien.tanggalMasuk.tanggal << "/" << pasien.tanggalMasuk.bulan << "/" << pasien.tanggalMasuk.tahun << endl;
    cout << " NIK     : " << pasien.nik << endl;
    cout << " Nama    : " << pasien.nama << endl;
    cout << " JK      : " << pasien.jenisKelamin << endl;
    cout << " Tgl Lahir" << endl;
    cout << "    Tanggal    : " << pasien.tanggalLahir.tanggal << endl;
    cout << "    Bulan      : " << pasien.tanggalLahir.bulan << endl;
    cout << "    Tahun      : " << pasien.tanggalLahir.tahun << endl;
    cout << " Gol     : " << pasien.golonganDarah << endl;
    cout << " Telp    : " << pasien.noTelp << endl;
    cout << " BPJS    : " << (pasien.pesertaBPJS ? "Ya" : "Tidak") << endl;
    cout << " Alamat" << endl;
    cout << "    Jalan      : " << pasien.alamat.jalan << endl;
    cout << "    Kelurahan  : " << pasien.alamat.kelurahan << endl;
    cout << "    Kota       : " << pasien.alamat.kota << endl;
    cout << "    Provinsi   : " << pasien.alamat.provinsi << endl;
    cout << "    Kode Pos   : " << pasien.alamat.kodePos << endl;
    cout << " Alergi  :" << endl;
    if (pasien.jumlahAlergi == 0) {
        cout << "   Tidak ada" << endl;
    } else {
        for (int i = 0; i < pasien.jumlahAlergi; i++) {
            cout << "   " << pasien.daftarAlergi[i].alergen << " -> " << pasien.daftarAlergi[i].reaksi << endl;
        }
    }
    cout << "----------------------------------------------------------------" << endl;
}

// MENU 1: DAFTARKAN PASIEN BARU
void daftarkanPasienBaru() {
    bersihkanLayar();
    if (totalPasien >= MAX_PASIEN) {
        cout << MERAH << "[GAGAL] Kapasitas penuh!" << RESET << endl;
        tekanEnterUntukLanjut();
        return;
    }

    cout << "================================================" << endl;
    cout << "           PENDAFTARAN PASIEN BARU              " << endl;
    cout << "================================================" << endl;

    Pasien pasienBaru;
    pasienBaru.id = totalPasien + 1;
    pasienBaru.sudahPulang = false;
    pasienBaru.jumlahAlergi = 0;

    cout << "NIK (16 digit)     : ";
    cin >> pasienBaru.nik;
    while ((int)pasienBaru.nik.size() != 16) {
        cout << "                              " << "Panjang nik wajib 16 karakter...." << RESET << endl;
        system("pause");
        cin.get();
        cout << "NIK (16 digit)     : ";
        cin >> pasienBaru.nik;
    }

    if (nikSudahAda(pasienBaru.nik)) {
        cout << endl;
        cout << "Pasien sudah terdaftar sebagai " << pasienBaru.nama << endl;
        tekanEnterUntukLanjut();
        return; // Menggagalkan dan langsung keluar dari fungsi pendaftaran
    }

    cin.ignore();

    cout << "Nama               : ";
    getline(cin, pasienBaru.nama);

    cout << "Tgl Lahir" << endl;

    // Tanggal
    while (true) {
        cout << "  Tanggal : ";
        string inputTanggal;
        cin >> inputTanggal;
        if (!hanyaDigit(inputTanggal)) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        int t = stringKeInt(inputTanggal);
        if (t < 1 || t > 30) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        pasienBaru.tanggalLahir.tanggal = t;
        break;
    }

    // Bulan
    while (true) {
        cout << "  Bulan   : ";
        string inputBulan;
        cin >> inputBulan;
        if (!hanyaDigit(inputBulan)) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        int b = stringKeInt(inputBulan);
        if (b < 1 || b > 12) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        pasienBaru.tanggalLahir.bulan = b;
        break;
    }

    // Tahun
    while (true) {
        cout << "  Tahun   : ";
        string inputTahun;
        cin >> inputTahun;
        if (!hanyaDigit(inputTahun)) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        int y = stringKeInt(inputTahun);
        if (y < 1900 || y > 2026) {
            cout << "            " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        pasienBaru.tanggalLahir.tahun = y;
        break;
    }

    // Jenis Kelamin
    while (true) {
        cout << "Jenis Kelamin (L/P): ";
        char jk;
        cin >> jk;
        // Ubah ke huruf besar
        if (jk >= 'a' && jk <= 'z') jk = jk - 32;
        if (jk != 'L' && jk != 'P') {
            cout << MERAH << "[GAGAL] Jenis kelamin harus L atau P!" << RESET << endl;
            continue;
        }
        pasienBaru.jenisKelamin = jk;
        break;
    }

    // Golongan Darah
    cout << "Gol. Darah         : ";
    cin >> pasienBaru.golonganDarah;

    // No Telp
    cout << "No. Telp           : ";
    cin >> pasienBaru.noTelp;
    cin.ignore();

    // Alamat
    cout << "Alamat" << endl;
    cout << "  Jalan      : "; getline(cin, pasienBaru.alamat.jalan);
    cout << "  Kelurahan  : "; getline(cin, pasienBaru.alamat.kelurahan);
    cout << "  Kota       : "; getline(cin, pasienBaru.alamat.kota);
    cout << "  Provinsi   : "; getline(cin, pasienBaru.alamat.provinsi);

    // Kode Pos
    while (true) {
        cout << "  Kode Pos   : ";
        string inputKodePos;
        cin >> inputKodePos;
        if (!hanyaDigit(inputKodePos)) {
            cout << "              " << MERAH << "Input tidak valid" << RESET << endl;
            continue;
        }
        pasienBaru.alamat.kodePos = stringKeInt(inputKodePos);
        break;
    }
    cin.ignore();

    // BPJS
    char inputBPJS;
    cout << "Peserta BPJS (y/n) : ";
    cin >> inputBPJS;
    pasienBaru.pesertaBPJS = (inputBPJS == 'y' || inputBPJS == 'Y');

    // Alergi
    int jumlahAlergi;
    cout << "Jumlah alergi (0-5): ";
    cin >> jumlahAlergi;
    if (jumlahAlergi < 0 || jumlahAlergi > 5) jumlahAlergi = 0;
    pasienBaru.jumlahAlergi = jumlahAlergi;
    cin.ignore();
    for (int i = 0; i < jumlahAlergi; i++) {
        cout << "[Alergi " << i + 1 << "]" << endl;
        cout << "  Alergen : "; getline(cin, pasienBaru.daftarAlergi[i].alergen);
        cout << "  Reaksi  : "; getline(cin, pasienBaru.daftarAlergi[i].reaksi);
    }

    daftarPasien[totalPasien] = pasienBaru;
    totalPasien++;

    cout << endl;
    cout << "[OK] Pasien ID-" << pasienBaru.id << " berhasil didaftarkan!" << endl;
    tekanEnterUntukLanjut();
}

// MENU 2: LIHAT SEMUA PASIEN

void lihatSemuaPasien() {
    bersihkanLayar();
    cout << "================================================================" << endl;
    cout << "                      DAFTAR PASIEN                            " << endl;
    cout << "================================================================" << endl;

    if (totalPasien == 0) {
        cout << "Belum ada pasien terdaftar." << endl;
        tekanEnterUntukLanjut();
        return;
    }

    for (int i = 0; i < totalPasien; i++) {
        if (!daftarPasien[i].sudahPulang) {
            tampilPasien(daftarPasien[i]);
        }
    }

    tekanEnterUntukLanjut();
}

// MENU 3: CARI PASIEN

void cariPasien() {
    bersihkanLayar();
    cout << "================================================================" << endl;
    cout << "                       CARI PASIEN                             " << endl;
    cout << "================================================================" << endl;

    string keyword;
    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, keyword);
       

    bool ditemukan = false;
    for (int i = 0; i < totalPasien; i++) {
        if (!daftarPasien[i].sudahPulang) {
            if (daftarPasien[i].nama.find(keyword) != string::npos) {
                tampilPasien(daftarPasien[i]);
                ditemukan = true;

            }
        }
    }

    if (!ditemukan) {
        cout << MERAH << "Pasien tidak ditemukan." << RESET << endl;
    }

    tekanEnterUntukLanjut();
}

// MENU 4: PULANGKAN PASIEN

void pulangkanPasien() {
    bersihkanLayar();
    cout << "================================================" << endl;
    cout << "           HAPUS / PULANGKAN PASIEN             " << endl;
    cout << "================================================" << endl;

    cout << "Daftar Pasien:" << endl;
    cout << "------------------------------------------------" << endl;

    bool adaPasienAktif = false;
    for (int i = 0; i < totalPasien; i++) {
        if (!daftarPasien[i].sudahPulang) {
            cout << "  ID-" << daftarPasien[i].id << "\t| " << daftarPasien[i].nama << endl;
            adaPasienAktif = true;
        }
    }
    cout << "------------------------------------------------" << endl;

    if (!adaPasienAktif) {
        cout << "Tidak ada pasien aktif." << endl;
        tekanEnterUntukLanjut();
        return;
    }

    int idPilihan;
    cout << endl;
    cout << "Masukkan ID pasien yang ingin dipulangkan: ";
    cin >> idPilihan;

    int indexDitemukan = -1;
    for (int i = 0; i < totalPasien; i++) {
        if (daftarPasien[i].id == idPilihan && !daftarPasien[i].sudahPulang) {
            indexDitemukan = i;
            break;
        }
    }

    if (indexDitemukan == -1) {
        cout << endl;
        cout << MERAH << "[!] ID-" << idPilihan << " tidak ditemukan." << RESET << endl;
        tekanEnterUntukLanjut();
        return;
    }

    Pasien& pasien = daftarPasien[indexDitemukan];

    int tanggalKeluar = 21, bulanKeluar = 5, tahunKeluar = 2026;
    int lamaRawat = hitungLamaRawat(pasien.tanggalMasuk, tanggalKeluar, bulanKeluar, tahunKeluar);
    long long totalTagihan = (long long)lamaRawat * TARIF_PER_HARI;

    cout << endl;
    cout << "================================================" << endl;
    cout << "                RINCIAN TAGIHAN                 " << endl;
    cout << "================================================" << endl;
    cout << " Nama    : " << pasien.nama << endl;
    cout << " NIK     : " << pasien.nik << endl;
    cout << " BPJS    : " << (pasien.pesertaBPJS ? "Ya" : "Tidak") << endl;
    cout << "------------------------------------------------" << endl;
    cout << " Tgl Masuk  : " << pasien.tanggalMasuk.tanggal << "/" << pasien.tanggalMasuk.bulan << "/" << pasien.tanggalMasuk.tahun << endl;
    cout << " Tgl Keluar : " << tanggalKeluar << "/" << bulanKeluar << "/" << tahunKeluar << endl;
    cout << " Lama Rawat : " << lamaRawat << " hari" << endl;
    cout << " Tarif/Hari : Rp " << TARIF_PER_HARI << endl;
    cout << "------------------------------------------------" << endl;

    if (pasien.pesertaBPJS) {
        cout << " Total Tagihan : Rp 0 (Ditanggung BPJS)" << endl;
    } else {
        cout << " Total Tagihan : Rp " << totalTagihan << endl;
    }

    cout << "================================================" << endl;
    cout << endl;
    cout << "Pasien wajib melunasi tagihan sebelum dipulangkan." << endl;
    cout << endl;

    char konfirmasi;
    cout << "Yakin ingin memulangkan pasien ini? (y/n): ";
    cin >> konfirmasi;
    cout << endl;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        pasien.sudahPulang = true;

        int sisaPasien = 0;
        for (int i = 0; i < totalPasien; i++) {
            if (!daftarPasien[i].sudahPulang) sisaPasien++;
        }

        cout << "[OK] Pasien ID-" << pasien.id << " berhasil dipulangkan." << endl;
        cout << "     Sisa pasien terdaftar: " << sisaPasien << endl;
    } else {
        cout << "[!] Pemulangan dibatalkan." << endl;
    }

    tekanEnterUntukLanjut();
}

int main() {
    int pilihan;
    do {
        bersihkanLayar();
        tampilMenu();

        string inputPilihan;
        cin >> inputPilihan;

        if (!hanyaDigit(inputPilihan)) {
            cout << MERAH << "[!] Input harus berupa angka." << RESET << endl;
            tekanEnterUntukLanjut();
            pilihan = -1;
            continue;
        }

        pilihan = stringKeInt(inputPilihan);

        switch (pilihan) {
            case 1: daftarkanPasienBaru(); break;
            case 2: lihatSemuaPasien();    break;
            case 3: cariPasien();          break;
            case 4: pulangkanPasien();     break;
            case 0:
                bersihkanLayar();
                cout << "Terima kasih! Sistem ditutup." << endl;
                cout << endl << endl << endl;
                cout << "------------------------------";
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                tekanEnterUntukLanjut();
        }
    } while (pilihan != 0);

    return 0;
}