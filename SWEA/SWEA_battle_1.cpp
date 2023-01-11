#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define INITIAL_SETTING                                                        \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

int row[] = {-1, 1, 0, 0}; // 상하좌우
int col[] = {0, 0, -1, 1};

int T, R, C, res;

vector<vector<char> /**/> map(20, vector<char>(20));
vector<vector<int> /**/> cnt(20, vector<int>(20, 0));
vector<char> items[20][20];
vector<pair<int, int> /**/> routes;
bool visited[20][20];

void solve(pair<int, int> start);
bool isDuplicated(char chk);
int typeCnt;
int main() {
    INITIAL_SETTING
    cin >> T;
    string line;
    for (int t = 1; t <= T; t++) {
        cin >> R >> C;
        set<char> types;
        for (int r = 0; r < R; r++) {
            cin >> line;
            for (int c = 0; c < C; c++) {
                map[r][c] = line[c];
                types.insert(line[c]);
            }
        }
        typeCnt = types.size();
        res = 0;

        fill(&visited[0][0], &visited[19][20], false);
        solve(make_pair(0, 0));
        cout << "#" << t << " " << res << "\n";
    }
}

void solve(pair<int, int> start) {
    if (res == typeCnt) {
        return;
    }
    bool isFinished = true;
    visited[start.first][start.second] = true;
    routes.push_back(start);

    for (int i = 0; i < 4; i++) {
        if (start.first + row[i] < 0 || start.first + row[i] >= R ||
            start.second + col[i] < 0 || start.second + col[i] >= C) {
            continue;
        }
        if ((visited[start.first + row[i]][start.second + col[i]] == false) &&
            map[start.first][start.second] !=
                map[start.first + row[i]][start.second + col[i]] &&
            !isDuplicated(map[start.first + row[i]][start.second + col[i]])) {
            isFinished = false;
            solve(make_pair(start.first + row[i], start.second + col[i]));
        }
    }
    if (routes.size() > res) {
        res = routes.size();
    }

    if (!routes.empty()) {
        visited[routes.back().first][routes.back().second] = false;
        routes.pop_back();
    }
}

bool isDuplicated(char chk) {
    for (pair<int, int> point : routes) {
        if (map[point.first][point.second] == chk) {
            return true;
        }
    }
    return false;
}