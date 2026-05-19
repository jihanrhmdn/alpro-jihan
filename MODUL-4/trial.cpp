#include <iostream>
using namespace std;

string user, pass;
int noRegis = 0;

void menuUtama()
{
    cout << "====== MENU ======" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
}
void Register()
{
    cout << "\n=== REGISTER ===" << endl;

    cout << "Masukkan Username : ";
    cin >> user;

    cout << "Masukkan Password : ";
    cin >> pass;
    noRegis++; 

    cout << "\n[Sistem] Register Berhasil!" << endl;
}
bool Login()
{
    string username, password;

    cout << "\n=== LOGIN ===" << endl;

    cout << "Masukkan Username : ";
    cin >> username;

    if (user == "")
    {
        cout << "Username tidak terdaftar!" << endl;
        return false;
    }

    if (username != user)
    {
        cout << "Username tidak terdaftar!" << endl;
        return false;
    }
    cout << "Masukkan Password : ";
    cin >> password;

    if (password != pass)
    {
        cout << "Password salah!" << endl;
        return false;
    }

    cout << "Login berhasil!" << endl;
    return true;
}

void halamanUser()
{
    int pilih;
    do
    {
        cout << "\n===== HALAMAN USER =====" << endl;
        cout << "Nomor Registrasi : " << noRegis << endl;
        cout << "Username         : " << user << endl;

        cout << "\n0. Sign Out" << endl;
        cout << "Pilih : ";
        cin >> pilih;

    } while (pilih != 0);

    cout << "\n[Sistem] Berhasil Sign Out!" << endl;
}

int main()
{
    int menu;

    do
    {
        menuUtama();
        cout << "Pilih: ";
        cin >> menu;

        if (menu == 1)
        {
            Register();
        }
        else if (menu == 2)
        {
            if (Login())
            {
                halamanUser();
            }
        }
        else if (menu == 3)
        {
            cout << "\n[Sistem] Keluar dari program." << endl;
        }
        else
        {
            cout << "\n[Sistem] Pilihan tidak valid!" << endl;
        }

        cout << endl;

    } while (menu != 3);

    return 0;
}