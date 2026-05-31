#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define RED     "\033[0;31m"
#define CYAN    "\033[0;36m"
#define GRAY    "\033[0;90m"
#define WHITE   "\033[0;37m"

struct Commit {
    int     id;
    string  message;
    string  author;
    string  timestamp;
    Commit* next;
};

struct Branch {
    string  name;
    Commit* head;
    int     commitCount;
    Branch* next;
};

struct Repository {
    string      name;
    Branch*     branches;
    Branch*     activeBranch;
    int         branchCount;
    Repository* next;
};

Repository* repoList      = nullptr;
Repository* activeRepo    = nullptr;
int         repoCount     = 0;
int         globalCommitId = 1;
string      authorName;

void clearScreen() { cout << "\033[2J\033[H"; }

void printLine() {
    cout << GRAY << "----------------------------------------" << RESET << "\n";
}

void waitEnter() {
    cout << "Press Enter...";
    cin.get();
}

string generateShortHash(int commitId) {
    const char hexChars[] = "0123456789abcdef";
    string hash = "";
    int value = commitId * 2654435761u;
    if (value < 0) value = -value;
    for (int i = 0; i < 7; i++) {
        hash = hexChars[value & 0xF] + hash;
        value >>= 4;
    }
    return hash;
}

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buffer);
}

Branch* createBranch(const string& name) {
    Branch* b     = new Branch;
    b->name        = name;
    b->head        = nullptr;
    b->commitCount = 0;
    b->next        = nullptr;
    return b;
}

Repository* createRepository(const string& name) {
    Repository* r  = new Repository;
    r->name         = name;
    r->branchCount  = 1;
    r->next         = nullptr;
    Branch* main    = createBranch("main");
    r->branches     = main;
    r->activeBranch = main;
    return r;
}

void gitCommit() {
    clearScreen();
    printLine();
    cout << "git commit [" << GREEN << activeRepo->activeBranch->name << RESET << "]\n";
    printLine();

    cout << CYAN << "Message : " << RESET;
    string msg;
    getline(cin, msg);

    if (msg.empty()) {
        cout << RED << "[ERROR]" << RESET << " Commit message cannot be empty!\n";
        waitEnter(); return;
    }

    cout << CYAN << "Push commit? (y/n): " << RESET;
    char confirm; cin >> confirm; cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << GRAY << "Commit cancelled.\n" << RESET;
        waitEnter(); return;
    }

    Commit* c    = new Commit;
    c->id         = globalCommitId++;
    c->message    = msg;
    c->author     = authorName;
    c->timestamp  = getCurrentTimestamp();
    c->next       = activeRepo->activeBranch->head;
    activeRepo->activeBranch->head = c;
    activeRepo->activeBranch->commitCount++;

    string hash = generateShortHash(c->id);
    cout << "[" << GREEN << activeRepo->activeBranch->name
         << " " << hash << RESET << "] " << msg << "\n";
    printLine();
    cout << activeRepo->activeBranch->name << " -> origin/" << activeRepo->activeBranch->name << "\n";
    cout << "$ git push origin " << GREEN << activeRepo->activeBranch->name << RESET << "\n";
    printLine();
    waitEnter();
}

void gitLog() {
    clearScreen();
    printLine();
    cout << "git log  [" << GREEN << activeRepo->activeBranch->name << RESET << "]\n";
    printLine();

    if (!activeRepo->activeBranch->head) {
        cout << "(No commits on this branch)\n";
    } else {
        Commit* c = activeRepo->activeBranch->head;
        while (c) {
            cout << YELLOW << "commit " << generateShortHash(c->id) << RESET << "\n";
            cout << "Author : " << c->author << "\n";
            cout << "Date   : " << c->timestamp << "\n";
            cout << "        " << c->message << "\n\n";
            c = c->next;
        }
    }
    printLine();
    waitEnter();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << RED << "Usage: ./gitsim <Username>" << RESET << "\n";
        return 1;
    }
    authorName = argv[1];
    Repository* first = createRepository("my-repo");
    repoList = first; activeRepo = first; repoCount = 1;
    cout << GREEN << "[OK]" << RESET << " test: commit & log ready\n";
    return 0;
}