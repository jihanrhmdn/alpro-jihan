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

int main() {
    cout << CYAN << "GITSIM" << RESET << " - Git Simulator\n";
    Repository* test = createRepository("test-repo");
    cout << "Repo created: " << test->name << "\n";
    delete test->branches;
    delete test;
    return 0;
}