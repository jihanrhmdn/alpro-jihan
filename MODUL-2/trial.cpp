#include <iostream>
using namespace std;

int main()
{
    char bunga;

    cout << " === TOKO BUNGA HARUMMANIS ==="<< endl;
    cout << "Pilih Bunga yang Diinginkan: " << endl;
    cout << "a. Mawar Harum" << endl;
    cout << "b. Melati Wangi" << endl;
    cout << "Pilih Mawar atau Melati (a atau b): ";
    cin >> bunga;
    switch (bunga)
    {
    case 'a':
        cout << "Wow Mawar";
        break;
    case 'b':
        cout << "Asik Melati";
        break;

    default:
        cout << "ZONKK";
    }

    cout << "Pilih Aroma: " << endl;

    return 0;
}