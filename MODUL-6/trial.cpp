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

void clearScreen() { cout << "\033[2J\033[H"; }

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

Repository* repoList     = nullptr;
Repository* activeRepo   = nullptr;
int         repoCount    = 0;
int         globalCommitId = 1;
string      authorName;

void printLine() {
    cout << GRAY << "----------------------------------------" << RESET << "\n";
}

void waitEnter() {
    cout << "Press Enter...";
    cin.get();
}

void printHeader(bool showFull = false) {
    clearScreen();
    cout << CYAN << "GITSIM" << RESET << " - Git Simulator\n";
    if (showFull && activeRepo != nullptr) {
        int idx = 1;
        Repository* tmp = repoList;
        while (tmp && tmp != activeRepo) { idx++; tmp = tmp->next; }
        cout << GRAY << "Author : " << WHITE << authorName << RESET
             << GRAY << " | Repo: " << WHITE << activeRepo->name << RESET
             << GRAY << " | HEAD: " << GREEN << activeRepo->activeBranch->name << RESET
             << " | [" << idx << "/" << repoCount << "]\n";
    } else {
        cout << GRAY << "Author: " << WHITE << authorName << RESET << "\n";
    }
}

Branch* findBranch(Repository* repo, const string& name) {
    Branch* b = repo->branches;
    while (b) { if (b->name == name) return b; b = b->next; }
    return nullptr;
}

Repository* findRepo(const string& name) {
    Repository* r = repoList;
    while (r) { if (r->name == name) return r; r = r->next; }
    return nullptr;
}

Branch* createBranch(const string& name) {
    Branch* b    = new Branch;
    b->name       = name;
    b->head       = nullptr;
    b->commitCount= 0;
    b->next       = nullptr;
    return b;
}

void copyCommits(Branch* dst, Branch* src) {
    if (!src->head) return;
    Commit* arr[1000];
    int cnt = 0;
    Commit* cur = src->head;
    while (cur) { arr[cnt++] = cur; cur = cur->next; }
    for (int i = cnt - 1; i >= 0; i--) {
        Commit* nc  = new Commit;
        nc->id       = arr[i]->id;
        nc->message  = arr[i]->message;
        nc->author   = arr[i]->author;
        nc->timestamp= arr[i]->timestamp;
        nc->next     = dst->head;
        dst->head    = nc;
        dst->commitCount++;
    }
}

Repository* createRepository(const string& name) {
    Repository* r = new Repository;
    r->name        = name;
    r->branchCount = 1;
    r->next        = nullptr;
    Branch* main   = createBranch("main");
    r->branches    = main;
    r->activeBranch= main;
    return r;
}

void appendRepo(Repository* r) {
    repoCount++;
    if (!repoList) { repoList = r; return; }
    Repository* tmp = repoList;
    while (tmp->next) tmp = tmp->next;
    tmp->next = r;
}

void appendBranch(Repository* repo, Branch* b) {
    Branch* tmp = repo->branches;
    while (tmp->next) tmp = tmp->next;
    tmp->next = b;
    repo->branchCount++;
}

void gitCommit() {
    printHeader();
    printLine();
    cout << "git commit [" << GREEN << activeRepo->activeBranch->name << RESET << "]\n";
    printLine();

    cout << CYAN << "Message : " << RESET;
    string msg;
    getline(cin, msg);
    cout << endl;

    if (msg.empty()) {
        cout << RED << "[ERROR]" << RESET << " Commit message cannot be empty!\n";
        waitEnter();
        return;
    }

    cout << CYAN << "Push commit? (y/n): " << RESET;
    char confirm;
    cin >> confirm;
    cin.ignore();
    cout << endl;

    if (confirm != 'y' && confirm != 'Y') {
        cout << GRAY << "Commit cancelled.\n" << RESET;
        waitEnter();
        return;
    }

    Commit* c   = new Commit;
    c->id        = globalCommitId++;
    c->message   = msg;
    c->author    = authorName;
    c->timestamp = getCurrentTimestamp();
    c->next      = activeRepo->activeBranch->head;
    activeRepo->activeBranch->head = c;
    activeRepo->activeBranch->commitCount++;

    string hash = generateShortHash(c->id);
    cout << "[" << GREEN << activeRepo->activeBranch->name << " " << hash << RESET << "] " << msg << "\n";
    printLine();
    cout << activeRepo->activeBranch->name << " -> origin/" << activeRepo->activeBranch->name << "\n";
    cout << "$ git push origin " << GREEN << activeRepo->activeBranch->name << RESET << "\n";
    printLine();
    cout << "\n";
    waitEnter();
}

void gitLog() {
    printHeader();
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

void gitBranch() {
    printHeader();
    printLine();
    cout << "git branch\n";
    printLine();

    Branch* b = activeRepo->branches;
    while (b) {
        if (b == activeRepo->activeBranch)
            cout << GREEN << "* " << RESET << b->name << " (" << b->commitCount << " commits)" << RESET << "\n";
        else
            cout << "  " << b->name << " (" << b->commitCount << " commits)\n";
        b = b->next;
    }

    printLine();
    cout << CYAN << "New branch name: " << RESET;
    string newName;
    getline(cin, newName);
    cout << endl;

    if (newName.empty()) {
        cout << RED << "[ERROR]" << RESET << " Branch name cannot be empty!\n";
        waitEnter();
        return;
    }
    if (findBranch(activeRepo, newName)) {
        cout << RED << "[ERROR]" << RESET << " Branch '" << newName << "' already exists!\n";
        waitEnter();
        return;
    }

    Branch* nb = createBranch(newName);
    copyCommits(nb, activeRepo->activeBranch);
    appendBranch(activeRepo, nb);

    cout << GREEN << "[OK]" << RESET << " Branch '" << newName
         << "' created from '" << activeRepo->activeBranch->name << "'\n";
    cout << GRAY << nb->commitCount << " commit(s) inherited\n";
    cout << "\n";
    waitEnter();
}

void gitCheckout() {
    printHeader();
    printLine();
    cout << "git checkout\n";
    printLine();

    Branch* b = activeRepo->branches;
    while (b) {
        if (b == activeRepo->activeBranch)
            cout << GREEN << "* " << RESET << b->name << RESET << "\n";
        else
            cout << "  " << b->name << "\n";
        b = b->next;
    }

    printLine();
    cout << CYAN << "Switch to branch: " << RESET;
    string target;
    getline(cin, target);
    cout << endl;

    Branch* found = findBranch(activeRepo, target);
    if (!found || found == activeRepo->activeBranch) {
        cout << RED << "[ERROR]" << RESET << " Invalid branch!\n";
        waitEnter();
        return;
    }

    activeRepo->activeBranch = found;
    cout << GREEN << "[OK]" << RESET << " Switched to branch '" << target << "'\n";
    cout << "\n";
    waitEnter();
}

void newRepository() {
    printHeader();
    printLine();
    cout << "git init (new repository)\n";
    printLine();

    cout << CYAN << "New repository name: " << RESET;
    string rname;
    getline(cin, rname);
    cout << endl;

    if (rname.empty()) {
        rname = "repo-" + to_string(repoCount + 1);
        Repository* r = createRepository(rname);
        appendRepo(r);
        activeRepo = r;
        cout << GREEN << "[OK]" << RESET << " Repository '" << rname << "' created and set as active.\n";
        cout << GRAY << "On branch: " << GREEN << "main" << RESET << "\n\n";
        waitEnter();
        return;
    }

    if (findRepo(rname)) {
        cout << RED << "[ERROR]" << RESET << " Repository '" << rname << "' already exists!\n";
        waitEnter();
        return;
    }

    Repository* r = createRepository(rname);
    appendRepo(r);
    activeRepo = r;
    cout << GREEN << "[OK]" << RESET << " Repository '" << rname << "' created and set as active.\n";
    cout << GRAY << "On branch: " << GREEN << "main" << RESET << "\n\n";
    waitEnter();
}

void switchRepository() {
    printHeader();
    printLine();
    cout << "switch repository\n";
    printLine();

    Repository* r = repoList;
    int idx = 1;
    while (r) {
        int cnt = r->activeBranch->commitCount;
        if (r == activeRepo)
        cout << GREEN << "* " << RESET << "[" << idx << "] " << r->name
            << "  (" << r->branchCount << " branch, " << cnt << " commits at HEAD)\n";
        else
            cout << "  [" << idx << "] " << r->name
                 << "  (" << r->branchCount << " branch, " << cnt << " commits at HEAD)\n";
        idx++;
        r = r->next;
    }

    printLine();
    cout << CYAN << "Select repository number: " << RESET;
    int choice;
    cin >> choice;
    cin.ignore();
    cout << endl;

    if (choice < 1 || choice > repoCount) {
        cout << RED << "[ERROR]" << RESET << " Invalid selection!\n";
        waitEnter();
        return;
    }

    r = repoList;
    for (int i = 1; i < choice; i++) r = r->next;
    activeRepo = r;

    cout << GREEN << "[OK]" << RESET << " Switched to repository '" << r->name << "'\n";
    cout << "HEAD: " << GREEN << r->activeBranch->name << RESET << "\n\n";
    waitEnter();
}

void freeAll() {
    Repository* r = repoList;
    while (r) {
        Branch* b = r->branches;
        while (b) {
            Commit* c = b->head;
            while (c) { Commit* t = c->next; delete c; c = t; }
            Branch* bt = b->next; delete b; b = bt;
        }
        Repository* rt = r->next; delete r; r = rt;
    }
}

void showMenu() {
    printHeader(true);
    printLine();
    cout << "[1] git commit\n";
    cout << "[2] git log\n";
    cout << "[3] git branch\n";
    cout << "[4] git checkout\n";
    cout << "[5] new repository\n";
    cout << "[6] switch repository\n";
    cout << "[0] exit\n";
    printLine();
    cout << GREEN << "> " << RESET;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << RED << "Usage: ./trial <Username>" << RESET << "\n";
        return 1;
    }
    authorName = argv[1];

    clearScreen();
    cout << CYAN << "GITSIM" << RESET << " - Lightweight Git Simulator\n";
    cout << GRAY << "Author: " << WHITE << authorName << RESET << "\n";
    printLine();
    cout << "git init\n";
    printLine();

    cout << CYAN << "Repository name: " << RESET;
    string rname;
    getline(cin, rname);
    if (rname.empty()) rname = "my-repo";
    
    Repository* first = createRepository(rname);
    appendRepo(first);
    activeRepo = first;

    cout << "\n" << GREEN << "[OK]" << RESET << " Initialized empty repository: " << rname << "\n";
    cout << GRAY << "On branch: " << GREEN << "main" << RESET << "\n\n";
    waitEnter();

    int choice = -1;
    while (choice != 0) {
        showMenu();
        cin >> choice;
        cin.clear();
        cin.ignore();

        switch (choice) {
            case 1: gitCommit();        break;
            case 2: gitLog();           break;
            case 3: gitBranch();        break;
            case 4: gitCheckout();      break;
            case 5: newRepository();    break;
            case 6: switchRepository(); break;
            case 0: break;
            default:
                cout << RED << "Invalid option!\n" << RESET;
                waitEnter();
        }
    }

    clearScreen();
    cout << CYAN << "Session Ended\n" << RESET;
    cout << GRAY << "Author : " << RESET << authorName << "\n";
    cout << GREEN << "Goodbye!\n" << RESET;

    freeAll();
    return 0;
}