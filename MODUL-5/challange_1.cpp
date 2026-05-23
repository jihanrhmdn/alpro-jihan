#include <iostream>
using namespace std;

const int MAX_PASIEN = 100;
const int MAX_ALERGI = 5;
const int TARIF_PER_HARI = 75000;

#define MERAH  "\033[31m"
#define RESET  "\033[0m"

int HARI_SISTEM  = 0;
int BULAN_SISTEM = 0;
int TAHUN_SISTEM = 0;

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

// cek apakah string hanya berisi digit
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
bool nikSudahAda(const string& nikBaru, string& namaPasien) {
    for (int i = 0; i < totalPasien; i++) {
        if (daftarPasien[i].nik == nikBaru && !daftarPasien[i].sudahPulang) {
            namaPasien = daftarPasien[i].nama;  
            return true;
        }
    }
    return false;
}

// Ambil ID baru berdasarkan jumlah pasien keseluruhan (termasuk yang sudah pulang)
int idBerikutnya() {
    int maxId = 0;
    for (int i = 0; i < totalPasien; i++) {
        if (daftarPasien[i].id > maxId) maxId = daftarPasien[i].id;
    }
    return maxId + 1;
}

void tampilMenu() {
    cout << "=================================================================" << endl;
    cout << "           SISTEM MANAJEMEN RS GAZACARE PLUS                     " << endl;
    cout << "=================================================================" << endl;
    cout << "                                                Tanggal "
         << HARI_SISTEM << "/" << BULAN_SISTEM << "/" << TAHUN_SISTEM << "     " << endl;
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

void inisialisasiDataDummy() {
    // Pasien 1
    daftarPasien[0].id = 1;
    daftarPasien[0].nik = "F1D02410xxx34567";
    daftarPasien[0].nama = "Salsabila Nailafahdi";
    daftarPasien[0].jenisKelamin = 'P';
    daftarPasien[0].golonganDarah = 'A';
    daftarPasien[0].noTelp = "88533321xxxx";
    daftarPasien[0].tanggalLahir = {5, 3, 1998};
    daftarPasien[0].alamat = {"Jl. Mawar No. 12", "Kebon Jeruk", "Jakarta Barat", "DKI Jakarta", 11530};
    daftarPasien[0].pesertaBPJS = true;
    daftarPasien[0].jumlahAlergi = 2;
    daftarPasien[0].daftarAlergi[0] = {"Aspirin", "Sesak napas"};
    daftarPasien[0].daftarAlergi[1] = {"Seafood", "Gatal-gatal"};
    daftarPasien[0].tanggalMasuk = {10, 5, 2026};
    daftarPasien[0].sudahPulang = false;

    // Pasien 2
    daftarPasien[1].id = 2;
    daftarPasien[1].nik = "F1D02410xxx45678";
    daftarPasien[1].nama = "I Kadek Mahesa Permana Putra";
    daftarPasien[1].jenisKelamin = 'L';
    daftarPasien[1].golonganDarah = 'B';
    daftarPasien[1].noTelp = "88133716xxxx";
    daftarPasien[1].tanggalLahir = {12, 5, 1985};
    daftarPasien[1].alamat = {"Jl. Melati No. 7", "Wonokromo", "Surabaya", "Jawa Timur", 60243};
    daftarPasien[1].pesertaBPJS = false;
    daftarPasien[1].jumlahAlergi = 0;
    daftarPasien[1].tanggalMasuk = {10, 5, 2026};
    daftarPasien[1].sudahPulang = false;

    // Pasien 3
    daftarPasien[2].id = 3;
    daftarPasien[2].nik = "F1D02418xxx56789";
    daftarPasien[2].nama = "Azizurrifki";
    daftarPasien[2].jenisKelamin = 'L';
    daftarPasien[2].golonganDarah = 'O';
    daftarPasien[2].noTelp = "08907590xxxx";
    daftarPasien[2].tanggalLahir = {20, 7, 1992};
    daftarPasien[2].alamat = {"Jl. Flamboyan No. 3", "Baciro", "Yogyakarta", "DI Yogyakarta", 55225};
    daftarPasien[2].pesertaBPJS = true;
    daftarPasien[2].jumlahAlergi = 1;
    daftarPasien[2].daftarAlergi[0] = {"Ibuprofen", "Mual dan muntah"};
    daftarPasien[2].tanggalMasuk = {11, 5, 2026};
    daftarPasien[2].sudahPulang = false;

    // Pasien 4
    daftarPasien[3].id = 4;
    daftarPasien[3].nik = "F1D02410xxx89012";
    daftarPasien[3].nama = "Rendy Wahyu Islami";
    daftarPasien[3].jenisKelamin = 'L';
    daftarPasien[3].golonganDarah = 'B';
    daftarPasien[3].noTelp = "08234136xxxx";
    daftarPasien[3].tanggalLahir = {2, 6, 1975};
    daftarPasien[3].alamat = {"Jl. Pandanaran No. 20", "Mugassari", "Semarang", "Jawa Tengah", 50249};
    daftarPasien[3].pesertaBPJS = false;
    daftarPasien[3].jumlahAlergi = 1;
    daftarPasien[3].daftarAlergi[0] = {"Latex", "Kulit memerah dan gatal"};
    daftarPasien[3].tanggalMasuk = {18, 5, 2026};
    daftarPasien[3].sudahPulang = false;

    // Pasien 5
    daftarPasien[4].id = 5;
    daftarPasien[4].nik = "F1D02410xxx01234";
    daftarPasien[4].nama = "Wimar Aryasmarta Prakasa";
    daftarPasien[4].jenisKelamin = 'L';
    daftarPasien[4].golonganDarah = 'A';
    daftarPasien[4].noTelp = "08582966xxxx";
    daftarPasien[4].tanggalLahir = {26, 6, 1968};
    daftarPasien[4].alamat = {"Jl. Sam Ratulangi No. 11", "Wenang", "Manado", "Sulawesi Utara", 95111};
    daftarPasien[4].pesertaBPJS = true;
    daftarPasien[4].jumlahAlergi = 0;
    daftarPasien[4].tanggalMasuk = {19, 5, 2026};
    daftarPasien[4].sudahPulang = false;

    totalPasien = 5;
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

    // Tanggal masuk otomatis dari sistem
    pasienBaru.tanggalMasuk.tanggal = HARI_SISTEM;
    pasienBaru.tanggalMasuk.bulan   = BULAN_SISTEM;
    pasienBaru.tanggalMasuk.tahun   = TAHUN_SISTEM;

    cout << "NIK (16 digit)     : ";
    cin >> pasienBaru.nik;
    while ((int)pasienBaru.nik.size() != 16) {
        cout << "                              " << "Panjang nik wajib 16 karakter...." << RESET << endl;
        system("pause");
        cin.get();
        cout << "NIK (16 digit)     : ";
        cin >> pasienBaru.nik;
    }

    string namaSudahAda = "";
    if (nikSudahAda(pasienBaru.nik, namaSudahAda)) {
        cout << endl;
        cout << "Pasien sudah terdaftar sebagai " << namaSudahAda << endl;
        tekanEnterUntukLanjut();
        return; 
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

    bool adaPasienAktif = false;
    for (int i = 0; i < totalPasien; i++) {
        if (!daftarPasien[i].sudahPulang) {
            adaPasienAktif = true;
            break;
        }
    }

    if (!adaPasienAktif) {
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
    
    cout << "================================================================" << endl;
    cout << endl;
    cout << "                       DAFTAR PASIEN                           " << endl;
    cout << "================================================================" << endl;

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

    int tanggalKeluar = HARI_SISTEM;
    int bulanKeluar   = BULAN_SISTEM;
    int tahunKeluar   = TAHUN_SISTEM;

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
    time_t sekarang = time(0);
    tm* lt = localtime(&sekarang);
    HARI_SISTEM  = lt->tm_mday;
    BULAN_SISTEM = lt->tm_mon + 1;
    TAHUN_SISTEM = lt->tm_year + 1900;

    inisialisasiDataDummy();
    
    int pilihan;
    do {
        bersihkanLayar();
        tampilMenu();

        string inputPilihan;
        cin >> inputPilihan;

        if (!hanyaDigit(inputPilihan)) {
            cout << MERAH << "[!] Input harus berupa angka...." << RESET << endl;
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
                cout << endl << endl;
                cout << "------------------------------";
                break;
            default:
                cout << MERAH << "[!] Pilihan tidak valid!" << RESET << endl;
                tekanEnterUntukLanjut();
        }
    } while (pilihan != 0);

    return 0;
}