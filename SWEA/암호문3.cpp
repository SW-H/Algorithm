#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

void I(int x, int y);
void A(int y);
void D(int x, int y);
void debug();

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

struct NODE {
    NODE *prev;
    NODE *next;
    int data;
};

int orgN, n, poolCapacity;
list<int> code;

int main() {
    INIT 
    for (int tc = 1; tc <= 10; tc++) {
        cin >> orgN;
        for (int i = 1; i <= orgN; i++) {
            cin >> n;
            code.push_back(n);
        }
        int cmdN, x, y;
        char cmd;
        cin >> cmdN;
        for (int c = 1; c <= cmdN; c++) {
            cin >> cmd;
            switch (cmd) {
            case 'I':
                cin >> x >> y;
                I(x, y);
                break;
            case 'D':
                cin >> x >> y;
                D(x, y);
                break;
            case 'A':
                cin >> y;
                A(y);
                break;
            default:
                cout << "ERROR\n";
                break;
            }
        }
        cout << "#" << tc << " ";
        debug();
    }
}
void I(int x, int y) {
    auto it = code.begin();
    list<int> tmp;
    for (int i = 1; i <= x; i++) {
        it++;
    }
    int n;
    for (int i = 1; i <= y; i++) {
        cin >> n;
        tmp.push_back(n);
    }
    code.splice(it, tmp);
}

void A(int y) {
    for (int i = 0; i < y; i++) {
        cin >> n;
        code.push_back(n);
    }
}

void D(int x, int y) {
    // 삭제 범위 : first~last
    auto first = code.begin();
    for (int i = 1; i <= x; i++) {
        first++;
    }
    auto last = first;
    for (int i = 1; i < y; i++) {
        last++;
    }
    code.erase(first, last);
}

void debug() {
    for (int i = 0; i < min((int)code.size(), 10); i++) {
        cout << code.front() << " ";
        code.pop_front();
    }
    cout << "\n";
    code.clear();
}