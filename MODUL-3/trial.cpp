#include <iostream>
#include <iomanip>

using namespace std;

// menerjemahkan pesan rahasia yang di-input
int decryptCaesar(char cipher[], char result[], int key)
{
    int i = 0;
    while (cipher[i] != '\0')
    {
        char c = cipher[i];
        if (c >= 'A' && c <= 'Z')
        {
            result[i] = (char)(((c - 'A' - key + 26) % 26) + 'A');
        }
        else if (c >= 'a' && c <= 'z')
        {
            result[i] = (char)(((c - 'a' - key + 26) % 26) + 'a');
        }
        else
        {
            result[i] = c;
        }
        i++;
    }
    result[i] = '\0';
    return i;
}

// menjumlahkan seluruh nilai numerik (ASCII) dari setiap karakter dalam teks petunjuk
int sumASCII(char str[])
{
    int total = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        total += (int)str[i];
        i++;
    }
    return total;
}

int main()
{
    char clue[50];
    cout << "Enter clue: ";
    cin.getline(clue, 50);

    cout << "\nWelcome to the Treasure Hunt!" << endl;
    cout << "Find the treasure before your health runs out!" << endl;
    cout << "You have 5 health." << endl;

    int key = 9;
    char decrypted[50];
    decryptCaesar(clue, decrypted, key);

    int totalASCII = sumASCII(clue);

    // menentukan posisi treasure berdasarkan hasil ASCII
    int treasureIdx = totalASCII % 25;
    char treasureCell = (char)('A' + treasureIdx);

    char grid[5][5];
    bool revealed[5][5];
    char label = 'A';

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            grid[row][col] = label++;
            revealed[row][col] = false;
        }
    }

    int health = 5;
    bool found = false;

    while (health > 0 && !found)
    {
        cout << endl;
        for (int row = 0; row < 5; row++)
        {
            // 1. tampilan bagian atas sel
            for (int col = 0; col < 5; col++)
            {
                cout << setw(4) << " ";
                if (col < 4)
                    cout << "|";
            }
            cout << endl;

            // 2. tampilan isi sel ('-')
            for (int col = 0; col < 5; col++)
            {
                if (revealed[row][col])
                {
                    cout << setw(3) << "-" << " ";
                }
                else
                {
                    cout << setw(3) << grid[row][col] << " ";
                }
                if (col < 4)
                    cout << "|";
            }
            cout << endl;

            // 3. tampilan garis bawah antar sel
            if (row < 4)
            {
                for (int col = 0; col < 5; col++)
                {
                    cout << "____";
                    if (col < 4)
                        cout << "|";
                }
                cout << endl;
            }
        }
        cout << endl;

        char move;
        cout << "Enter your move (A to Y): ";
        cin >> move;

        // convert huruf kecil ke besar
        if (move >= 'a' && move <= 'y')
            move -= 32;

        // cek apakah input berada di range A-Y
        if (move < 'A' || move > 'Y')
        {
            cout << "Invalid input! Please enter A-Y." << endl;
            continue;
        }

        int idx = move - 'A';
        int mRow = idx / 5;
        int mCol = idx % 5;

        if (revealed[mRow][mCol])
        {
            cout << "You already opened this cell!" << endl;
            continue;
        }

        if (move == treasureCell)
        {
            found = true;
            cout << "+---------------------------------------------------+" << endl;
            cout << "|                                                   |" << endl;
            cout << "|   Congratulations!                                |" << endl;
            cout << "|                                                   |" << endl;
            cout << "|   You found the treasure at: " << treasureCell;
            cout << "                    |" << endl;
            cout << "|                                                   |" << endl;
            cout << "+---------------------------------------------------+" << endl;
            cout << "You win the game!" << endl;
        }
        else
        {
            revealed[mRow][mCol] = true;
            health--;
            cout << "\nNo treasure here! You lose 1 health." << endl;
            cout << "Remaining health: " << health << endl;
        }
    }
    return 0;
}