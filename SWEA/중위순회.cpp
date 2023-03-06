#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define T 10

struct node {
    node *child[2];
    char ch; // 문자
    int childCnt;
};
string info;
int vertex;

int nodeCnt;
node pool[101];
vector<char> res;

vector<string> split(string str, string delimeter);
void construct(vector<string> splited);
void solve();
void traverse(node *start);
void initialize();

int main() {
    INIT;
    for (int tc = 1; tc <= T; tc++) {
        cin >> vertex;
        initialize();
        cout << "#" << tc << " ";
        solve();
    }
}

void initialize() {

    nodeCnt = 0;
    memset(pool, 0, sizeof(pool));
}

void solve() {

    for (int v = 1; v <= vertex; v++) {
        int id;
        char ch;
        cin >> id ;
        cin >> pool[id].ch;
        int childId;
        for(int cnt=0;cnt<2 && (cin.get()!='\n');cnt++){
            cin >> childId;
            pool[id].child[pool[id].childCnt++] = &pool[childId];
        }
    }
    traverse(&pool[1]);
    cout << "\n";
}

void traverse(node *start) {
    if (start->child[0]) {
        traverse(start->child[0]);
    }
    cout << start->ch;
    if (start->child[1]) {
        traverse(start->child[1]);
    }
}

void construct(vector<string> splited) {
    int id = std::stoi(splited[0]);
    pool[id].ch = splited[1].c_str()[0];
    for (int i = 0; i < splited.size() - 2; i++) {
        pool[id].child[pool[id].childCnt++] = &pool[stoi(splited[2 + i])];
    }
}

vector<string> split(string str, string delimeter) {
    int prev = 0, cur;
    vector<string> ret;
    cur = str.find(delimeter);
    while (cur != string::npos) {
        string subStr = str.substr(prev, cur - prev);
        ret.push_back(subStr);
        prev = cur + 1;
        cur = str.find(delimeter, prev);
    }
    ret.push_back(str.substr(prev, cur - prev));
    return ret;
}