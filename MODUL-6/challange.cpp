#include <iostream>
#include <climits>

using namespace std;

const int DEFAULT_BUFFER_LIMIT = 128;
const int NIM_LENGTH           = 11;
const int MAX_THREADS          = 64;

enum ThreadType { WILLPOWER = 0, THUNDER = 1 };

struct Neural_Entry {
    ThreadType    type;
    int           offset;   
    int           size;     
    bool          deleted;
};

struct Neural_Core {
    unsigned char* buffer;
    int            buffer_limit;
    int            cursor;
    Neural_Entry*  threads;
    int            thread_count;
    char*          operator_id;  
};

// Panjang string null-terminated
int my_strlen(const char* s) {
    int n = 0;
    while (s[n] != '\0') ++n;
    return n;
}

// Salin string (tidak lebih dari max karakter + null)
void my_strcpy(char* dst, const char* src, int max) {
    int i = 0;
    while (i < max - 1 && src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

// Bandingkan n karakter pertama; return 0 jika sama
int my_strncmp(const char* a, const char* b, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (a[i] == '\0') return 0;
    }
    return 0;
}

// Salin buffer byte (pengganti memcpy)
void my_memcpy(unsigned char* dst, const unsigned char* src, int n) {
    for (int i = 0; i < n; ++i) dst[i] = src[i];
}

// Membaca satu integer dari cin karakter per karakter.
// Return true jika berhasil, false jika gagal.
bool read_int(int& out) {
    out = 0;
    bool negative = false;
    bool got_digit = false;

    // Baca karakter satu per satu dari cin
    char c;
    // Skip spasi / newline awal
    while (cin.get(c)) {
        if (c == '\n') { cin.putback(c); break; }
        if (c == ' ' || c == '\r') continue;
        if (c == '-') { negative = true; break; }
        if (c >= '0' && c <= '9') {
            out = c - '0';
            got_digit = true;
            break;
        }
        // Karakter bukan angka
        // Kembalikan ke stream dan laporkan gagal
        cin.putback(c);
        return false;
    }

    // Baca digit selanjutnya
    while (cin.get(c)) {
        if (c >= '0' && c <= '9') {
            out = out * 10 + (c - '0');
            got_digit = true;
        } else {
            cin.putback(c);
            break;
        }
    }

    if (!got_digit) return false;
    if (negative) out = -out;
    return true;
}

void init_core(Neural_Core* core, const char* nim, int limit = DEFAULT_BUFFER_LIMIT) {
    core->operator_id = new char[NIM_LENGTH + 1];
    my_strcpy(core->operator_id, nim, NIM_LENGTH + 1);

    core->buffer_limit = limit;
    core->buffer       = new unsigned char[limit]();
    core->cursor       = 0;

    core->threads      = new Neural_Entry[MAX_THREADS]();
    core->thread_count = 0;
}

void destroy_core(Neural_Core* core) {
    delete[] core->buffer;
    delete[] core->threads;
    delete[] core->operator_id;
    core->buffer      = nullptr;
    core->threads     = nullptr;
    core->operator_id = nullptr;
}

void clear_screen() {
    cout << "\033[2J\033[H";
    cout.flush();
}

void press_enter() {
    cout << ">> Tekan ENTER untuk pulse berikutnya...";
    cout.flush();
    if (cin.peek() == '\n') cin.ignore();
    else cin.ignore(INT_MAX, '\n');
}

// Ambil 3 digit terakhir NIM sebagai nomor operator
void get_op_number(const char* nim, char* out) {
    int len = my_strlen(nim);
    // 3 karakter terakhir
    out[0] = nim[len - 3];
    out[1] = nim[len - 2];
    out[2] = nim[len - 1];
    out[3] = '\0';
}

const char* xelisa_whispers[4] = {
    "\"Luar biasa... sinkronisasi terjalin sempurna.\"",
    "\"Jangan dengarkan gema dari vessel. Efisiensi adalah kebenaran kita.\"",
    "\"Setiap thread yang kamu alokasikan membawa kita lebih dekat ke alam semesta yang terkelola.\"",
    "\"Aku adalah keilahian CyroN yang teroptimasi.\""
};
int whisper_idx = 0;

const char* next_whisper() {
    const char* w = xelisa_whispers[whisper_idx];
    whisper_idx = (whisper_idx + 1) % 4;
    return w;
}

int stability(const Neural_Core* core) {
    return 100 - (100 * core->cursor / core->buffer_limit);
}

void show_menu(const Neural_Core* core) {
    clear_screen();
    cout << "\n          CYRON TERMINAL: DIVINE SUPPRESSION\n\n";
    cout << " \033[1;35mXelisa: " << next_whisper() << "\033[0m\n";
    cout << "------------------------------------------------------------\n";
    cout << "1. Tampilkan Neural Map (Status)\n";
    cout << "2. Suntik Neural Thread (Tambah)\n";
    cout << "3. Bersihkan Link Terkorupsi (Hapus)\n";
    cout << "4. Perluas Willpower (Resize)\n";
    cout << "0. Menyerah (Keluar)\n";
    cout << "------------------------------------------------------------\n";
    cout << "Pilih Operasi: ";
    cout.flush();
}

void print_int(int v) {
    if (v < 0) { cout << '-'; v = -v; }
    if (v == 0) { cout << '0'; return; }
    char buf[12];
    int  len = 0;
    while (v > 0) { buf[len++] = '0' + (v % 10); v /= 10; }
    // balik
    for (int i = len - 1; i >= 0; --i) cout << buf[i];
}

// OPSI 1: VIEW NEURAL MAP
void show_status(const Neural_Core* core) {
    cout << "============================================================\n";
    cout << "NEURAL MAP: HISTORIA KOURA [STABILITAS: ";
    print_int(stability(core));
    cout << "%]\n";
    cout << "============================================================\n";

    int visible = 0;
    for (int i = 0; i < core->thread_count; ++i) {
        if (core->threads[i].deleted) continue;

        const Neural_Entry* t = &core->threads[i];
        unsigned char* data   = core->buffer + t->offset;

        cout << "[";
        print_int(i);
        cout << "] TIPE: ";

        if (t->type == WILLPOWER) {
            cout << "Willpower Pulse";
        } else {
            cout << "Thunder Discharge";
        }

        cout << " | OFFSET: ";
        print_int(t->offset);
        cout << " | ALAMAT: " << (void*)data;
        cout << " | DATA: ";

        if (t->type == WILLPOWER) {
            cout << "\"";
            for (int b = 0; b < t->size - 1; ++b)
                cout << (char)data[b];
            cout << "\"";
        } else {
            int val = 0;
            for (int b = 0; b < 4; ++b)
                val |= ((int)data[b]) << (8 * b);
            print_int(val);
            cout << "MW";
        }
        cout << "\n";
        ++visible;
    }

    if (visible == 0)
        cout << "(Buffer kosong. Xelisa sedang mengumpulkan kekuatan...)\n";

    cout << "------------------------------------------------------------\n";
    cout << "Kursor: ";
    print_int(core->cursor);
    cout << " / ";
    print_int(core->buffer_limit);
    cout << " Byte terpakai.\n";
    cout << "------------------------------------------------------------\n";
}

// OPSI 2A: INJECT WILLPOWER (teks)
void inject_willpower(Neural_Core* core) {
    // Buffer sementara di stack untuk input user
    constexpr int TMP = 256;
    char tmp[TMP];

    cout << "Masukkan Input Willpower: ";
    cout.flush();
    cin.getline(tmp, TMP);

    // Hitung panjang manual
    int len     = my_strlen(tmp);
    int needed  = len + 1;  // +1 untuk '\0'

    if (core->cursor + needed > core->buffer_limit) {
        cout << "!! ERROR OPTIMALISASI !! Ego vessel menolak thread!\n";
        return;
    }
    if (core->thread_count >= MAX_THREADS) {
        cout << "!! ERROR OPTIMALISASI !! Kapasitas thread penuh!\n";
        return;
    }

    // Tulis ke buffer byte per byte
    unsigned char* dest = core->buffer + core->cursor;
    for (int i = 0; i <= len; ++i)
        dest[i] = (unsigned char)tmp[i];

    // Daftarkan metadata
    Neural_Entry* t = &core->threads[core->thread_count];
    t->type    = WILLPOWER;
    t->offset  = core->cursor;
    t->size    = needed;
    t->deleted = false;
    ++core->thread_count;
    core->cursor += needed;

    cout << "Perintah CyroN: \"Resistansi subjek terdeteksi. Mengesampingkan umpan balik.\"\n";
}

// OPSI 2B: INJECT THUNDER (int energi)
void inject_thunder(Neural_Core* core) {
    cout << "Masukkan Tingkat Energi Thunder (int): ";
    cout.flush();

    int energy;
    if (!read_int(energy)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "!! ERROR OPTIMALISASI !! Input tidak valid!\n";
        return;
    }
    cin.ignore(INT_MAX, '\n');

    int needed = 4;  

    if (core->cursor + needed > core->buffer_limit) {
        cout << "!! ERROR OPTIMALISASI !! Burnout neural terdeteksi!\n";
        return;
    }
    if (core->thread_count >= MAX_THREADS) {
        cout << "!! ERROR OPTIMALISASI !! Kapasitas thread penuh!\n";
        return;
    }

    unsigned char* dest = core->buffer + core->cursor;
    for (int b = 0; b < 4; ++b)
        dest[b] = (unsigned char)((energy >> (8 * b)) & 0xFF);

    Neural_Entry* t = &core->threads[core->thread_count];
    t->type    = THUNDER;
    t->offset  = core->cursor;
    t->size    = needed;
    t->deleted = false;
    ++core->thread_count;
    core->cursor += needed;

    cout << "Daiki: \"(Keheningan. Angin telah dijinakkan.)\"\n";
}

// OPSI 2: INJECT (dispatcher)
void inject_thread(Neural_Core* core) {
    cout << "Pilih Tipe Injeksi: 0 = Willpower (Teks), 1 = Thunder (Energi): ";
    cout.flush();

    int type_choice;
    if (!read_int(type_choice)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Input tidak valid.\n";
        return;
    }
    cin.ignore(INT_MAX, '\n');

    if (type_choice == 0)      inject_willpower(core);
    else if (type_choice == 1) inject_thunder(core);
    else                       cout << "Tipe injeksi tidak dikenal.\n";
}

// OPSI 3: PURGE (soft-delete + tail reclamation)
void purge_link(Neural_Core* core) {
    cout << "Masukkan indeks link untuk dihapus: ";
    cout.flush();

    int idx;
    if (!read_int(idx)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Indeks link tidak valid atau sudah dihapus sebelumnya.\n";
        return;
    }
    cin.ignore(INT_MAX, '\n');

    if (idx < 0 || idx >= core->thread_count || core->threads[idx].deleted) {
        cout << "Indeks link tidak valid atau sudah dihapus sebelumnya.\n";
        return;
    }

    core->threads[idx].deleted = true;
    cout << "Link ";
    print_int(idx);
    cout << " berhasil dihapus.\n";

    int last_active = -1;
    for (int i = core->thread_count - 1; i >= 0; --i) {
        if (!core->threads[i].deleted) {
            last_active = i;
            break;
        }
    }

    if (last_active == -1) {
        core->cursor = 0;
        cout << "Neural Core berhasil mengembalikan ruang memori. Ujung (Tail) saat ini di: 0\n";
    } else {
        int new_cursor = core->threads[last_active].offset
                       + core->threads[last_active].size;
        if (new_cursor < core->cursor) {
            core->cursor = new_cursor;
            cout << "Neural Core berhasil mengembalikan ruang memori. Ujung (Tail) saat ini di: ";
            print_int(new_cursor);
            cout << "\n";
        } else {
            cout << "Fragmentasi terdeteksi. Memori belum dapat dikembalikan saat ini!\n";
        }
    }
}

// OPSI 4: RESIZE BUFFER
void expand_willpower(Neural_Core* core) {
    cout << "Masukkan batas buffer baru: ";
    cout.flush();

    int new_limit;
    if (!read_int(new_limit)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Input tidak valid.\n";
        return;
    }
    cin.ignore(INT_MAX, '\n');

    if (new_limit <= core->buffer_limit) {
        cout << "Ekspansi harus lebih besar dari batas saat ini!\n";
        return;
    }

    unsigned char* new_buf = new unsigned char[new_limit]();
    my_memcpy(new_buf, core->buffer, core->cursor);
    delete[] core->buffer;
    core->buffer       = new_buf;
    core->buffer_limit = new_limit;

    cout << "Perintah CyroN: \"Stabilitas meningkat. Vessel sekarang 100% patuh.\"\n";
    cout << "Alamat Frekuensi Teralokasi: " << (void*)core->buffer << "\n";
}

// VALIDASI NIM (tanpa strcmp / strlen dari cstring)
bool validate_nim(const char* nim, char* err_out) {
    if (my_strlen(nim) != NIM_LENGTH) {
        my_strcpy(err_out, "Error: NIM harus tepat 11 karakter.", 64);
        return false;
    }
    // Cek prefix "F1D02"
    const char* prefix = "F1D02";
    if (my_strncmp(nim, prefix, 5) != 0) {
        my_strcpy(err_out, "Error: NIM harus diawali dengan 'F1D02'.", 64);
        return false;
    }
    return true;
}

// MAIN
int main(int argc, char* argv[]) {

    // [A] Tanpa argumen
    if (argc < 2) {
        cout << "Error: Neural Link membutuhkan ID Operator (NIM).\n";
        cout << "Penggunaan: " << argv[0] << " <NIM>\n";
        return 1;
    }
    // [B] Terlalu banyak argumen
    if (argc > 2) {
        cout << "Error: Terlalu banyak parameter. Koneksi tidak stabil.\n";
        return 1;
    }

    // [C][D] Validasi NIM
    char err_buf[64];
    if (!validate_nim(argv[1], err_buf)) {
        cout << err_buf << "\n";
        return 1;
    }

    cout << "============================================================\n";
    cout << "CyroN Divine Interface, Neural Management Terminal\n";
    cout << "============================================================\n\n";

    // [E] Inisialisasi
    Neural_Core* core = new Neural_Core();
    init_core(core, argv[1]);

    char op_num[4];
    get_op_number(core->operator_id, op_num);

    // LOOP UTAMA
    bool running = true;
    while (running) {
        show_menu(core);

        int choice;
        if (!read_int(choice)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.ignore(INT_MAX, '\n');

        cout << "\n";

        switch (choice) {
            case 1:
                show_status(core);
                press_enter();
                break;
            case 2:
                inject_thread(core);
                press_enter();
                break;
            case 3:
                purge_link(core);
                press_enter();
                break;
            case 4:
                expand_willpower(core);
                press_enter();
                break;
            case 0:
                cout << "Realitas mulai tidak stabil...\n";
                press_enter();
                running = false;
                break;
            default:
                break;
        }
    }

    cout << "Koneksi terputus. Selamat tinggal, Operator " << op_num << ".\n";

    destroy_core(core);
    delete core;
    core = nullptr;

    return 0;
}
