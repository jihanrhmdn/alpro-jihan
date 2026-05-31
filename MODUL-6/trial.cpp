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

int main() {
    cout << CYAN << "GITSIM" << RESET << " - Git Simulator\n";
    return 0;
}