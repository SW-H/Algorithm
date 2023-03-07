#include <cctype>
#include <cstring>
#include <deque>
#include <iostream>
using namespace std;

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define T 10

struct node {
    node *child[2];
    string cont;
};

node nodes[1001];
int vertices;
double res;
deque<string> opStk;

void initialize();
void input();
void solve();
void traverse(node *start);

int main() {
    INIT;
    for (int tc = 1; tc <= T; tc++) {
        // initialize();
        input();
        solve();
        cout << "#" << tc << " " << nodes[1].cont << "\n";
    }
}

void input() {
    int id;
    cin >> vertices;
    for (int v = 1; v <= vertices; v++) {
        cin >> id;
        cin >> nodes[id].cont;
        int childId;
        for (int idx = 0; idx < 2; idx++) {
            if (cin.get() == '\n') { //  && (cin.get() != '\n')
                break;
            }
            cin >> childId;
            nodes[id].child[idx] = &nodes[childId];
        }
    }
}

void initialize() {
    res = 0;
    memset(nodes, 0, sizeof(nodes));
    opStk.clear();
}

void solve() { traverse(&nodes[1]); }
void traverse(node *start) {
    if (start->child[0]) {
        traverse(start->child[0]);
    }
    if (start->child[1]) {
        traverse(start->child[1]);
    }
    if (!isdigit(start->cont.c_str()[0])) {
        char oprtr = start->cont.c_str()[0];
        int operand1, operand2;
        operand1 = stoi(start->child[0]->cont);
        operand2 = stoi(start->child[1]->cont);

        switch (oprtr) {
        case '-':
            start->cont = to_string(operand1 - operand2);
            break;
        case '+':
            start->cont = to_string(operand1 + operand2);
            break;
        case '*':
            start->cont = to_string(operand1 * operand2);
            break;
        case '/':
            start->cont = to_string(operand1 / operand2);
            break;
        }
    }
}