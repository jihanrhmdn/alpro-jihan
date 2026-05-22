#include <iostream>
#include <cstdlib>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

struct Player {
    char name[50];
    int level;
    int hp, maxHp;
    int mp, maxMp;
    int atk, def, agi;
    int exp, expToNext;
    int baseHp, baseMp;
    int baseAtk, baseDef, baseAgi;
};

struct Enemy {
    const char* name;
    int hp, maxHp;
    int atk, agi;
    bool isBoss;
    int expReward;
};
bool bossDefeated[7] = {false, false, false, false, false, false, false};

void printLine(int len = 65) {
    for (int i = 0; i < len; i++) cout << "=";
    cout << endl;
}

void printDivider(int len = 65) {
    for (int i = 0; i < len; i++) cout << "-";
    cout << endl;
}

void pressEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}

void initPlayer(Player &p) {
    p.level = 1;
    p.baseHp = 1500; p.maxHp = 1500; p.hp = 1500;
    p.baseMp = 100;  p.maxMp = 100;  p.mp = 100;
    p.baseAtk = 40; p.atk = 40;
    p.baseDef = 20; p.def = 20;
    p.baseAgi = 15; p.agi = 15;
    p.exp = 0;
    p.expToNext = 150;
}

void checkLevelUp(Player &p) {
    while (p.exp >= p.expToNext) {
        p.exp -= p.expToNext;
        p.level++;
        p.expToNext = p.level * 150;

        int addAtk = (int)(p.baseAtk * 0.3);
        int addDef = (int)(p.baseDef * 0.3);
        int addAgi = (int)(p.baseAgi * 0.3);
        int addHp  = (int)(p.baseHp  * 0.5);
        int addMp  = (int)(p.baseMp  * 0.5);

        p.atk += addAtk;
        p.def += addDef;
        p.agi += addAgi;
        p.maxHp += addHp;
        p.maxMp += addMp;
        p.hp = p.maxHp;
        p.mp = p.maxMp;

        printLine();
        cout << "|" << "                *** LEVEL UP! ***                               " << "|" << endl;
        cout << "| You reached Level " << p.level << endl;
        cout << "| ATK +" << addAtk
             << " DEF +" << addDef
             << " AGI +" << addAgi
             << " MaxHP +" << addHp
             << " MaxMP +" << addMp
             << " (HP/MP restored)" << endl;
        printLine();
        pressEnter();
    }
}

bool tryDodge(int myAgi, int enemyAgi) {
    int chance = (myAgi * 100) / (myAgi + enemyAgi + 1);
    int roll = rand() % 100;
    return roll < chance;
}

void showBattleUI(Player &p, Enemy &e, int turn) {
    printLine();
    cout << "| ABYSSAL REALM" << "                                     TURN " << turn << " |" << endl;
    printLine();
    cout << "| [" << p.name << "]" << "                                         Level " << p.level << endl;
    cout << "|   HP  : " << p.hp << " / " << p.maxHp << endl;
    cout << "|   MP  : " << p.mp << " / " << p.maxMp << endl;
    cout << "|   AGI : " << p.agi << endl;
    cout << "|   EXP : " << p.exp << " / " << p.expToNext << endl;
    printDivider();
    cout << "| [" << e.name << "]" << endl;
    cout << "|   HP  : " << e.hp << " / " << e.maxHp << endl;
    cout << "|   AGI : " << e.agi << endl;
    printLine();
    cout << "| 1. Basic Attack    (No MP  | 100% ATK)" << endl;
    cout << "| 2. Heavy Attack    (30 MP  | 160% ATK | lower accuracy)" << endl;
    cout << "| 3. Heal            (20 MP  | Restore 200 HP)" << endl;
    cout << "| 4. Run Away        (Exit game)" << endl;
    printLine();
}

int doBattle(Player &p, Enemy &e) {
    int turn = 1;

    while (p.hp > 0 && e.hp > 0) {
        clearScreen();
        showBattleUI(p, e, turn);

        int choice;
        cout << "[Choose action]: ";
        cin >> choice;

        bool playerActed = true;

        if (choice == 1) {
            if (tryDodge(e.agi, p.agi)) {
                cout << "[Basic Attack] " << e.name << " dodges " << p.name << "'s attack!" << endl;
            } else {
                int dmg = p.atk - e.agi / 3;
                if (dmg < 1) dmg = 1;
                e.hp -= dmg;
                if (e.hp < 0) e.hp = 0;
                cout << "[Basic Attack] " << p.name << " hits " << e.name << " for " << dmg << " damage." << endl;
            }
        } else if (choice == 2) {
            if (p.mp < 30) {
                cout << "Not enough MP for Heavy Attack. Turn wasted." << endl;
                playerActed = false;
            } else {
                p.mp -= 30;
                int hitRoll = rand() % 100;
                if (hitRoll < 30 || tryDodge(e.agi, p.agi)) {
                    cout << "[Heavy Attack] " << p.name << " missed!" << endl;
                } else {
                    int dmg = (int)(p.atk * 1.6) - e.agi / 3;
                    if (dmg < 1) dmg = 1;
                    e.hp -= dmg;
                    if (e.hp < 0) e.hp = 0;
                    cout << "[Heavy Attack] " << p.name << " lands a crushing blow on " << e.name << " for " << dmg << " damage!" << endl;
                }
            }
        } else if (choice == 3) {
            if (p.mp < 20) {
                cout << "Not enough MP to Heal. Turn wasted." << endl;
                playerActed = false;
            } else {
                p.mp -= 20;
                p.hp += 200;
                if (p.hp > p.maxHp) p.hp = p.maxHp;
                cout << "[Heal] " << p.name << " restores 200 HP. HP: " << p.hp << "/" << p.maxHp << endl;
            }
        } else if (choice == 4) {
            cout << "You ran away from the battle!" << endl;
            pressEnter();
            return -1;
        } else {
            cout << "Invalid choice!" << endl;
        }

        if (e.hp <= 0) {
            cout << endl;
            printDivider();
            cout << "| " << e.name << " has been defeated!" << endl;
            cout << "| EXP gained: " << e.expReward << endl;
            printDivider();
            p.exp += e.expReward;
            pressEnter();
            checkLevelUp(p);
            return 1;
        }

        if (tryDodge(p.agi, e.agi)) {
            cout << "[" << e.name << "] attacked, but " << p.name << " dodges!" << endl;
        } else {
            int enemyDmg = e.atk - p.def / 4;
            if (enemyDmg < 1) enemyDmg = 1;
            p.hp -= enemyDmg;
            if (p.hp < 0) p.hp = 0;
            cout << "[" << e.name << "] attacks " << p.name << " for " << enemyDmg << " damage." << endl;
        }

        if (p.hp <= 0) {
            cout << endl;
            cout << "You have been defeated... Game Over." << endl;
            pressEnter();
            return 0;
        }

        pressEnter();
        turn++;
    }

    return 1;
}

struct StageData {
    const char* stageName;
    const char* enemies[3];
    int enemyHp[3];
    int enemyAtk[3];
    int enemyAgi[3];
    int enemyExp[3];
    const char* bossName;
    int bossHp;
    int bossAtk;
    int bossAgi;
    int bossExp;
};

StageData stages[7] = {
    {
        "Pride",
        {"Arrogant Soldier", "Noble Knight", "Fallen Champion"},
        {80, 150, 220},
        {25, 40, 55},
        {8, 10, 12},
        {10, 20, 35},
        "King of Pride",
        500, 80, 15, 80
    },
    {
        "Greed",
        {"Gold Hoarder", "Corrupt Merchant", "Living Treasure"},
        {180, 250, 320},
        {35, 50, 65},
        {13, 14, 16},
        {35, 50, 65},
        "Dragon of Greed",
        700, 100, 18, 120
    },
    {
        "Wrath",
        {"Furious Beast", "Berserker", "Flame Demon"},
        {260, 340, 420},
        {55, 75, 90},
        {14, 17, 19},
        {55, 75, 90},
        "Avatar of Wrath",
        900, 130, 20, 160
    },
    {
        "Sloth",
        {"Lazy Undead", "Sleeping Giant", "Dream Spirit"},
        {350, 460, 550},
        {65, 85, 100},
        {6, 8, 14},
        {70, 90, 110},
        "Lord of Sloth",
        1100, 150, 12, 200
    },
    {
        "Gluttony",
        {"Hungry Slime", "Devourer Beast", "Endless Maw"},
        {420, 550, 680},
        {80, 105, 125},
        {12, 16, 20},
        {90, 115, 135},
        "Lord of Gluttony",
        1400, 175, 17, 240
    },
    {
        "Envy",
        {"Shadow Copy", "Mirror Spirit", "Shapeshifter"},
        {500, 630, 760},
        {95, 120, 145},
        {18, 22, 26},
        {110, 140, 165},
        "Embodiment of Envy",
        1700, 200, 24, 280
    },
    {
        "Lust",
        {"Charming Spirit", "Siren", "Succubus"},
        {600, 750, 900},
        {110, 140, 170},
        {20, 25, 30},
        {130, 165, 200},
        "Queen of Lust",
        2200, 250, 28, 350
    }
};

bool enemyDefeated[7][3] = {
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false},
    {false,false,false}
};

void showStageMenu(int stageIdx, Player &p) {
    StageData &s = stages[stageIdx];
    printLine();
    cout << "| [???]  : Fufufu, human. Are you strong enough to fight me?" << endl;
    cout << "| [???]  : I am " << s.stageName << ", and you dare to challenge me?" << endl;
    cout << "| [" << s.stageName << "] : But first, prove your worth." << endl;
    printLine();

    for (int i = 0; i < 3; i++) {
        cout << "| " << (i+1) << ". " << s.enemies[i];
        if (enemyDefeated[stageIdx][i]) cout << " [DEFEATED]";
        cout << endl;
    }
    cout << "| 4. " << s.bossName << " (Boss)";
    if (bossDefeated[stageIdx]) cout << " [DEFEATED]";
    cout << endl;
    cout << "| 5. Retreat" << endl;
    printLine();
}

bool allDefeatedInStage(int stageIdx) {
    for (int i = 0; i < 3; i++) {
        if (!enemyDefeated[stageIdx][i]) return false;
    }
    return bossDefeated[stageIdx];
}

void runStage(int stageIdx, Player &p) {
    if (allDefeatedInStage(stageIdx)) {
        cout << "You have already cleared this stage!" << endl;
        pressEnter();
        return;
    }

    StageData &s = stages[stageIdx];

    while (true) {
        clearScreen();
        showStageMenu(stageIdx, p);

        int choice;
        cout << "[Which path will you take?]: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            int idx = choice - 1;
            if (enemyDefeated[stageIdx][idx]) {
                cout << "This enemy is already defeated!" << endl;
                pressEnter();
                continue;
            }

            Enemy e;
            e.name    = s.enemies[idx];
            e.hp      = s.enemyHp[idx];
            e.maxHp   = s.enemyHp[idx];
            e.atk     = s.enemyAtk[idx];
            e.agi     = s.enemyAgi[idx];
            e.isBoss  = false;
            e.expReward = s.enemyExp[idx];

            clearScreen();
            printLine();
            cout << "| [" << e.name << "]: Welcome, adventurer. Show me what you are made of!" << endl;
            printLine();
            pressEnter();

            int result = doBattle(p, e);
            if (result == 1) {
                enemyDefeated[stageIdx][idx] = true;
            } else if (result == 0) {
                return;
            }

        } else if (choice == 4) {
            // Boss
            if (bossDefeated[stageIdx]) {
                cout << "Boss is already defeated!" << endl;
                pressEnter();
                continue;
            }

            bool allRegularDone = true;
            for (int i = 0; i < 3; i++) {
                if (!enemyDefeated[stageIdx][i]) { allRegularDone = false; break; }
            }
            if (!allRegularDone) {
                cout << "Defeat all other enemies before challenging the Boss!" << endl;
                pressEnter();
                continue;
            }

            Enemy boss;
            boss.name     = s.bossName;
            boss.hp       = s.bossHp;
            boss.maxHp    = s.bossHp;
            boss.atk      = s.bossAtk;
            boss.agi      = s.bossAgi;
            boss.isBoss   = true;
            boss.expReward = s.bossExp;

            clearScreen();
            printLine();
            cout << "| [" << boss.name << "]: You dare challenge me?! Prepare yourself!" << endl;
            printLine();
            pressEnter();

            int result = doBattle(p, boss);
            if (result == 1) {
                bossDefeated[stageIdx] = true;
                clearScreen();
                printLine();
                cout << "| Stage " << s.stageName << " CLEARED!" << endl;
                printLine();
                pressEnter();
                return;
            } else if (result == 0) {
                return;
            }

        } else if (choice == 5) {
            return;
        } else {
            cout << "Invalid choice!" << endl;
            pressEnter();
        }

        if (p.hp <= 0) return;
    }
}

void showMainMenu() {
    printLine();
    cout << "+=======================================================================+" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|      _    _                         _   ____            _             |" << endl;
    cout << "|     / \\  | |__  _   _ ___ ___  __ _| | |  _ \\ ___  __ _| |_ __ ___    |" << endl;
    cout << "|    / _ \\ | '_ \\| | | / __/ __|/ _` | | | |_) / _ \\/ _` | | '_ ` _ \\   |" << endl;
    cout << "|   / ___ \\| |_) | |_| \\__ \\__ \\ (_| | | |  _ <  __/ (_| | | | | | | |  |" << endl;
    cout << "|  /_/   \\_\\_.__/ \\__, |___/___/\\__,_|_| |_| \\_\\___|\\__,_|_|_| |_| |_|  |" << endl;
    cout << "|                 |___/                                                 |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "+=======================================================================+" << endl;
    printLine();
    printLine();
    cout << "|          THE 7 DEADLY SINS ARE WAITING FOR YOU                 |" << endl;
    printLine();

    const char* sinNames[7] = {"Pride","Greed","Wrath","Sloth","Gluttony","Envy","Lust"};
    for (int i = 0; i < 7; i++) {
        cout << "|              " << (i+1) << ". " << sinNames[i];
        if (bossDefeated[i]) cout << "   [BOSS DEFEATED]";
        cout << endl;
    }
    cout << "|              8. EXIT" << endl;
    printLine();
    cout << "|      The deeper you go, the stronger they are                  |" << endl;
    printLine();
    cout << "[Choose your desired stage]: ";
}

void showIntro(Player &p) {
    clearScreen();
    printLine();
    cout << "|" << endl;
    cout << "|   Welcome to Abyssal Realm, adventurer." << endl;
    cout << "|   The seven deadly sins await your challenge." << endl;
    cout << "|" << endl;
    printLine();
    cout << "[Enter your name]: ";
    cin.ignore();
    cin.getline(p.name, 50);
    cout << "Press ENTER to continue...";
    cin.get();
}

bool allBossesDefeated() {
    for (int i = 0; i < 7; i++) {
        if (!bossDefeated[i]) return false;
    }
    return true;
}

void showVictory(Player &p) {
    clearScreen();
    printLine();
    cout << "|   *** CONGRATULATIONS, CHAMPION OF THE ABYSS! ***              |" << endl;
    cout << "|" << endl;
    cout << "|       You have defeated all Seven Deadly Sins!" << endl;
    cout << "|" << endl;
    const char* sins[7] = {"Pride","Greed","Wrath","Sloth","Gluttony","Envy","Lust"};
    for (int i = 0; i < 7; i++) {
        cout << "|   " << sins[i] << "     - DEFEATED" << endl;
    }
    cout << "|" << endl;
    cout << "|   The Abyssal Realm trembles before your name, " << p.name << "!" << endl;
    cout << "|       You are the true master of the Abyss!" << endl;
    cout << "|" << endl;
    printLine();
    pressEnter();
}

int main() {
    srand(12345);

    Player player;
    initPlayer(player);
    showIntro(player);

    while (true) {
        clearScreen();
        showMainMenu();

        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= 7) {
            if (player.hp <= 0) {
                cout << "You are dead. Please restart the game." << endl;
                pressEnter();
                break;
            }
            runStage(choice - 1, player);

            if (player.hp <= 0) {
                cout << "GAME OVER. Your journey ends here." << endl;
                pressEnter();
                break;
            }

            if (allBossesDefeated()) {
                showVictory(player);
                break;
            }

        } else if (choice == 8) {
            cout << "Farewell, adventurer." << endl;
            pressEnter();
            break;
        } else {
            cout << "Invalid choice!" << endl;
            pressEnter();
        }
    }

    return 0;
}
