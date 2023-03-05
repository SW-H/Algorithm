#include <iostream>
#include <list>
using namespace std;

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

list<int> seq;

void solve(char cmd);
void I(list<int>::iterator it, int cont);
void printAt(int idx);
void debug();

int main() {
    INIT;
    int T;
    cin >> T;
    int len, cnt, idx, n;
    for (int tc = 1; tc <= T; tc++) {
        seq.clear();
        cin >> len >> cnt >> idx;
        for (int i = 1; i <= len; i++) {
            cin >> n; // 수열 내용
            seq.push_back(n);
        }
        char cmd;
        for (int i = 1; i <= cnt; i++) {
            cin >> cmd;
            solve(cmd);
        }
        cout << "#" << tc << " ";
        printAt(idx);
    }
}
void printAt(int idx) {
    list<int>::iterator it = seq.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    if(idx>=seq.size()){
        cout << "-1\n";
        return;
    }
    cout << *it << "\n";
}

void solve(char cmd) {
    int idx, cont;
    cin >> idx;
    list<int>::iterator it = seq.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    switch (cmd) {
    case 'I':
        cin >> cont;
        I(it, cont);
        break;
    case 'D':
        seq.erase(it);
        break;
    case 'C':
        cin >> cont;
        *it = cont;
        break;
    }
}

void I(list<int>::iterator it, int cont) {
    list<int> tmp;
    tmp.push_back(cont);
    seq.splice(it, tmp);
}

void debug() {
    list<int>::iterator it = seq.begin();
    cout << "\n";
    while (it != seq.end()) {
        cout << *(it++) << " ";
    }
}
