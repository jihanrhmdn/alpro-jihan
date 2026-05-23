#include <iostream>
#include <cstdlib>
using namespace std;

struct Character {
    char name[50];
    int hp, maxHp;
    int mp, maxMp;
    int atk, def, agi;
    int exp, expToLevel;
    int level;
    int baseAtk, baseDef, baseAgi, baseMaxHp, baseMaxMp;
};

struct Enemy {
    char name[50];
    int hp, maxHp;
    int atk, def, agi;
    int expReward;
    bool isBoss;
};

bool bossDefeated[7] = {false, false, false, false, false, false, false};

void clearScreen() {
    system("cls");
}

void banner(){
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
}

void pressEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore(1000, '\n');
}

void levelUp(Character &player) {
    player.level++;
    int addAtk  = (int)(player.baseAtk   * 0.3);
    int addDef  = (int)(player.baseDef   * 0.3);
    int addAgi  = (int)(player.baseAgi   * 0.3);
    int addHp   = (int)(player.baseMaxHp * 0.5);
    int addMp   = (int)(player.baseMaxMp * 0.5);

    player.atk    += addAtk;
    player.def    += addDef;
    player.agi    += addAgi;
    player.maxHp  += addHp;
    player.maxMp  += addMp;
    player.hp      = player.maxHp;
    player.mp      = player.maxMp;
    player.expToLevel += 50;

    cout << "+================================================================+" << endl;
    cout << "|                      *** LEVEL UP! ***                        |" << endl;
    cout << "| You reached Level " << player.level << endl;
    cout << "| ATK +" << addAtk << "  DEF +" << addDef << "  AGI +" << addAgi
         << "  MaxHP +" << addHp << "  MaxMP +" << addMp << "  (HP/MP restored)" << endl;
    cout << "+================================================================+" << endl;
    pressEnter();
}

void gainExp(Character &player, int amount) {
    player.exp += amount;
    cout << "+----------------------------------------------------------------+" << endl;
    cout << "| EXP gained: " << amount << endl;
    cout << "+----------------------------------------------------------------+" << endl;
    while (player.exp >= player.expToLevel) {
        player.exp -= player.expToLevel;
        levelUp(player);
    }
}

void displayHUD(const Character &player, const Enemy &enemy, int turn) {
    cout << "+================================================================+" << endl;
    cout << "| ABYSSAL REALM                                   TURN " << turn << "       |" << endl;
    cout << "+================================================================+" << endl;
    cout << "| [" << player.name << "]                                    Level " << player.level << endl;
    cout << "|   HP  : " << player.hp << " / " << player.maxHp << endl;
    cout << "|   MP  : " << player.mp << " / " << player.maxMp << endl;
    cout << "|   AGI : " << player.agi << endl;
    cout << "|   EXP : " << player.exp << " / " << player.expToLevel << endl;
    cout << "+----------------------------------------------------------------+" << endl;
    cout << "| [" << enemy.name << "]" << endl;
    cout << "|   HP  : " << enemy.hp << " / " << enemy.maxHp << endl;
    cout << "|   AGI : " << enemy.agi << endl;
    cout << "+================================================================+" << endl;
    cout << "| 1. Basic Attack    (No MP  | 100% ATK)" << endl;
    cout << "| 2. Heavy Attack    (30 MP  | 160% ATK  | lower accuracy)" << endl;
    cout << "| 3. Heal            (20 MP  | Restore 200 HP)" << endl;
    cout << "| 4. Run Away        (Exit game)" << endl;
    cout << "+================================================================+" << endl;
    cout << "[Choose action]: ";
}

bool dodgeCheck(int agi) {
    int chance = agi;
    if (chance > 75) chance = 75;
    int roll = rand() % 100;
    return roll < chance;
}

bool battle(Character &player, Enemy enemy) {
    clearScreen();
    cout << "+================================================================+" << endl;
    cout << "| [" << enemy.name << "]: Welcome, adventurer. Show me what you are made of! |" << endl;
    cout << "+================================================================+" << endl;
    pressEnter();

    int turn = 1;
    while (player.hp > 0 && enemy.hp > 0) {
        clearScreen();
        displayHUD(player, enemy, turn);

        int choice;
        cin >> choice;
        cin.ignore();

        bool playerActed = true;
        if (choice == 1) {

            // Basic Attack
            if (dodgeCheck(enemy.agi)) {
                cout << "\n[Basic Attack] " << enemy.name << " dodges the attack!" << endl << endl;
            } else {
                int dmg = player.atk;
                if (dmg < 1) dmg = 1;
                enemy.hp -= dmg;
                cout << "\n[Basic Attack] " << player.name << " hits " << enemy.name << " for " << dmg << " damage." << endl << endl;
            }
        } else if (choice == 2) {

            // Heavy Attack
            if (player.mp < 30) {
                cout << "\nNot enough MP for Heavy Attack. Turn wasted." << endl;
                playerActed = false;
            } else {
                player.mp -= 30;
                int roll = rand() % 100;
                if (roll >= 70 || dodgeCheck(enemy.agi)) {
                    cout << "\n[Heavy Attack] " << player.name << " misses!" << endl << endl;
                } else {
                    int dmg = (int)(player.atk * 1.6);
                    if (dmg < 1) dmg = 1;
                    enemy.hp -= dmg;
                    cout << "\n[Heavy Attack] " << player.name << " lands a crushing blow on " << enemy.name << " for " << dmg << " damage!" << endl << endl;
                }
            }
        } else if (choice == 3) {

            // Heal
            if (player.mp < 20) {
                cout << "\nNot enough MP for Heal. Turn wasted." << endl;
                playerActed = false;
            } else {
                player.mp -= 20;
                player.hp += 200;
                if (player.hp > player.maxHp) player.hp = player.maxHp;
                cout << "\n[Heal] " << player.name << " restores 200 HP! HP: " << player.hp << "/" << player.maxHp << endl;
            }
        } else if (choice == 4) {
            cout << "\nYou fled from battle. Game over." << endl;
            return false;
        } else {
            cout << "\nInvalid choice. Turn wasted." << endl;
            playerActed = false;
        }

        if (enemy.hp <= 0) {
            cout << "\n+----------------------------------------------------------------+" << endl;
            cout << "| " << enemy.name << " has been defeated!" << endl;
            cout << "+----------------------------------------------------------------+" << endl;
            gainExp(player, enemy.expReward);
            pressEnter();
            return true;
        }

        if (dodgeCheck(player.agi)) {
            cout << "[" << enemy.name << "] attacked, but " << player.name << " dodges!" << endl;
        } else {
            int dmg = enemy.atk - player.def;
            if (dmg < 1) dmg = 1;
            player.hp -= dmg;
            cout << "[" << enemy.name << "] attacks " << player.name << " for " << dmg << " damage." << endl;
        }

        if (player.hp <= 0) {
            cout << "\n" << player.name << " has been defeated! Game Over." << endl;
            pressEnter();
            return false;
        }

        pressEnter();
        turn++;
    }
    return true;
}

bool runStage(Character &player, int stageIndex) {
    Enemy stages[7][4] = {
        // 1. Pride
        {
            {"Arrogant Soldier",  80,  80, 25, 5,  8, 10, false},
            {"Noble Knight",     120, 120, 30, 8, 10, 20, false},
            {"Fallen Champion",  150, 150, 35,10, 12, 30, false},
            {"King of Pride (Boss)", 600, 600, 50,15, 20, 60, true }
        },
        // 2. Greed
        {
            {"Gold Hoarder",     180, 180, 30, 8, 13, 35, false},
            {"Corrupt Merchant", 200, 200, 35,10, 14, 40, false},
            {"Living Treasure",  220, 220, 40,12, 15, 50, false},
            {"Dragon of Greed",  400, 400, 60,18, 16, 80, true }
        },
        // 3. Wrath
        {
            {"Furious Beast",    200, 200, 45, 8, 16, 40, false},
            {"Berserker",        230, 230, 55,10, 18, 50, false},
            {"Flame Demon",      260, 260, 60,12, 20, 60, false},
            {"Avatar of Wrath",  500, 500, 80,20, 22, 100, true}
        },
        // 4. Sloth
        {
            {"Lazy Undead",      220, 220, 40,15, 10, 45, false},
            {"Sleeping Giant",   280, 280, 50,18, 12, 55, false},
            {"Dream Spirit",     260, 260, 55,14, 14, 60, false},
            {"Lord of Sloth",    550, 550, 75,22, 16, 110, true}
        },
        // 5. Gluttony
        {
            {"Hungry Slime",     240, 240, 50,12, 14, 50, false},
            {"Devourer Beast",   280, 280, 60,15, 16, 60, false},
            {"Endless Maw",      300, 300, 65,16, 18, 70, false},
            {"Lord of Gluttony", 600, 600, 90,24, 20, 120, true}
        },
        // 6. Envy
        {
            {"Shadow Copy",      260, 260, 55,14, 18, 55, false},
            {"Mirror Spirit",    290, 290, 60,16, 20, 65, false},
            {"Shapeshifter",     310, 310, 65,18, 22, 75, false},
            {"Embodiment of Envy",650,650,100,26, 24, 130, true}
        },
        // 7. Lust
        {
            {"Charming Spirit",  280, 280, 60,16, 20, 60, false},
            {"Siren",            310, 310, 70,18, 22, 70, false},
            {"Succubus",         340, 340, 80,20, 25, 85, false},
            {"Queen of Lust",    700, 700,120,30, 28, 150, true}
        }
    };

    const char* stageNames[7] = {"Pride","Greed","Wrath","Sloth","Gluttony","Envy","Lust"};
    const char* sinIntro[7] = {
        "I am Pride, and you dare to challenge me?",
        "I am Greed, and you dare to challenge me?",
        "I am Wrath, and you dare to challenge me?",
        "I am Sloth, and you dare to challenge me?",
        "I am Gluttony, and you dare to challenge me?",
        "I am Envy, and you dare to challenge me?",
        "I am Lust, and you dare to challenge me?"
    };

    clearScreen();
    cout << "+================================================================+" << endl;
    cout << "| [???]     : Fufufu, human. Are you strong enough to fight me? |" << endl;
    cout << "| [???]     : " << sinIntro[stageIndex] << endl;
    cout << "| [" << stageNames[stageIndex] << "] : But first, prove your worth." << endl;
    cout << "+================================================================+" << endl;
    cout << "| 1. " << stages[stageIndex][0].name << endl;
    cout << "| 2. " << stages[stageIndex][1].name << endl;
    cout << "| 3. " << stages[stageIndex][2].name << endl;
    cout << "| 4. " << stages[stageIndex][3].name << endl;
    cout << "| 5. Retreat" << endl;
    cout << "+================================================================+" << endl;
    cout << "[Which path will you take?]: ";

    int choice;
    cin >> choice;
    if (choice == 5) {
        cout << "[" << stageNames[stageIndex] << "]: I knew you were not worthy of my time." << endl;
        system("pause");
        return true;
    }

    if (choice < 1 || choice > 4) {
        cout << "Invalid choice." << endl;
        system("pause");
        return true;
    }

    int idx = choice - 1;
    bool result = battle(player, stages[stageIndex][idx]);
    if (!result) return false; 

    if (idx == 3) {
        bossDefeated[stageIndex] = true;
    }

    return true;
}

void showMainMenu(const Character &player) {
    clearScreen();
    banner();
    cout << "+=======================================================================+" << endl;
    cout << "|                  THE 7 DEADLY SINS ARE WAITING FOR YOU                |" << endl;
    cout << "+=======================================================================+" << endl;
    const char* names[7] = {"Pride","Greed","Wrath","Sloth","Gluttony","Envy","Lust"};
    for (int i = 0; i < 7; i++) {
        cout << "|                          " << (i+1) << ". " << names[i];
        if (bossDefeated[i]) cout << "   [BOSS DEFEATED]";
        cout << endl;
    }
    cout << "|                          8. EXIT" << endl;
    cout << "+=======================================================================+" << endl;
    cout << "|          The deeper you go, the stronger they are                     |" << endl;
    cout << "+=======================================================================+" << endl;
    cout << "[Choose your desired stage]: ";
}

// check win
bool allDefeated() {
    for (int i = 0; i < 7; i++)
        if (!bossDefeated[i]) return false;
    return true;
}

void showVictory(const char* name) {
    clearScreen();
    cout << "+================================================================+" << endl;
    cout << "|        *** CONGRATULATIONS, CHAMPION OF THE ABYSS! ***       |" << endl;
    cout << "|                                                               |" << endl;
    cout << "|          You have defeated all Seven Deadly Sins!            |" << endl;
    cout << "|                                                               |" << endl;
    cout << "|   Pride      - DEFEATED                                      |" << endl;
    cout << "|   Greed      - DEFEATED                                      |" << endl;
    cout << "|   Wrath      - DEFEATED                                      |" << endl;
    cout << "|   Sloth      - DEFEATED                                      |" << endl;
    cout << "|   Gluttony   - DEFEATED                                      |" << endl;
    cout << "|   Envy       - DEFEATED                                      |" << endl;
    cout << "|   Lust       - DEFEATED                                      |" << endl;
    cout << "|                                                               |" << endl;
    cout << "|   The Abyssal Realm trembles before your name, " << name << "!  " << endl;
    cout << "|        You are the true master of the Abyss!                 |" << endl;
    cout << "+================================================================+" << endl;
    pressEnter();
}

int main() {
    Character player;
    player.level    = 1;
    player.baseAtk  = 39;
    player.baseDef  = 5;
    player.baseAgi  = 15;
    player.baseMaxHp= 1500;
    player.baseMaxMp= 100;
    player.atk      = player.baseAtk;
    player.def      = player.baseDef;
    player.agi      = player.baseAgi;
    player.maxHp    = player.baseMaxHp;
    player.maxMp    = player.baseMaxMp;
    player.hp       = player.maxHp;
    player.mp       = player.maxMp;
    player.exp      = 0;
    player.expToLevel = 150;

    clearScreen();
    banner();
    cout << "+=======================================================================+" << endl;
    cout << "|            Welcome to Abyssal Realm, adventurer.                      |" << endl;
    cout << "|            The seven deadly sins await your challenge.                |" << endl;
    cout << "+=======================================================================+" << endl;
    cout << "[Enter your name]: ";
    cin.getline(player.name, 50);
    pressEnter();

    bool running = true;
    while (running) {
        showMainMenu(player);
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= 7) {
            bool alive = runStage(player, choice - 1);
            if (!alive) {
                cout << "\nGame Over. " << player.name << " has fallen in the Abyssal Realm." << endl;
                running = false;
            }
            if (allDefeated()) {
                showVictory(player.name);
                running = false;
            }
        } else if (choice == 8) {
            cout << "[???]: Coward..." << endl;
            running = false;
        } else {
            cout << "Invalid choice." << endl;
            pressEnter();
        }
    }

    return 0;
}