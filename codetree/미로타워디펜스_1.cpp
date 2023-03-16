#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int sz, round;
int map[25][25];
vector<pair<int, int> /**/> routes;
pair<int, int> player;

void calcRoutes();
void debug();
vector<pair<int, int> /**/> clearRepeat();
void makeMap(vector<pair<int, int> /**/> monsters);

// → ↓ ← ↑
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
int score;
int main() {
    cin >> sz >> round;
    for (int row = 0; row < sz; row++) {
        for (int col = 0; col < sz; col++) {
            cin >> map[row][col];
        }
    }
    calcRoutes();
    int d, power;
    //  d : 0번부터 3번까지 각각 → ↓ ← ↑
    for (int r = 1; r <= round; r++) {
        cin >> d >> power;
        // 몬스터 공격
        for (int p = 1; p <= power; p++) {
            int nr = player.first + dr[d] * p;
            int nc = player.second + dc[d] * p;
            score += map[nr][nc];
            // cout << "+" << map[nr][nc] << "\n";
            map[nr][nc] = 0;
        }
        // 4번이상 반복된 몬스터 삭제
        vector<pair<int, int> /**/> res = clearRepeat();
        makeMap(res);
        // debug();
    }
    cout << score << "\n";
}

void makeMap(vector<pair<int, int> /**/> monsters) {
    int idx = 0;
    int repeat = 1;
    int newMap[25][25] = {};
    for (int i = 1; i < monsters.size(); i++) {
        if (map[monsters[i].first][monsters[i].second] ==
            map[monsters[i - 1].first][monsters[i - 1].second]) {
            repeat++;
        } else {
            newMap[routes[idx].first][routes[idx++].second] = repeat;
            newMap[routes[idx].first][routes[idx++].second] =
                map[monsters[i - 1].first][monsters[i - 1].second];
            repeat = 1;
        }
    }
    for (int row = 0; row < sz; row++) {
        for (int col = 0; col < sz; col++) {
            map[row][col] = newMap[row][col];
        }
    }
}

vector<pair<int, int> /**/> clearRepeat() {
    int repeat = 1;
    vector<pair<int, int> /**/> monsters;
    for (auto r : routes) {
        if (map[r.first][r.second] != 0) {
            // cout << r.first << " " << r.second << "\n";
            monsters.push_back(r);
        }
    }
    // vector<pair<int, int> /**/> monsters(routes);
    // for (auto it = monsters.begin(); it != monsters.end(); it++) {
    //     if (map[it->first][it->second] == 0) {
    //         it=monsters.erase(it);
    //     }
    // }

    for (int i = 1; i < monsters.size(); i++) {
        if (map[monsters[i].first][monsters[i].second] ==
            map[monsters[i - 1].first][monsters[i - 1].second]) {
            repeat++;
        } else if (repeat >= 4) {
            i--;
            cout << map[monsters[i].first][monsters[i].second] * repeat << "\n"; 
            score += map[monsters[i].first][monsters[i].second] * repeat;
            // for (int del = 0; del < repeat; del++) {
                // score += map[monsters[i - del].first][monsters[i -
                // del].second];
            monsters.erase(monsters.begin() + i - repeat + 1,
                               monsters.begin() + i + 1);
                // map[monsters[i - del].first][monsters[i - del].second] = 0;
            // }
            // i -= repeat;
            // i = max(1, i - 4);
            i = 1;
            repeat = 1;
        } else {
            repeat = 1;
        }
    }
    return monsters;
}

void calcRoutes() {
    // 좌 하 우 상
    int dr[] = {0, 1, 0, -1};
    int dc[] = {-1, 0, 1, 0};
    int nr = sz / 2;
    int nc = sz / 2;
    player = make_pair(nr, nc);

    int d = 0;
    for (int cnt = 1;; cnt++) {
        for (int pair = 0; pair < 2; pair++) {
            for (int exe = 0; exe < cnt; exe++) {
                nr = nr + dr[d];
                nc = nc + dc[d];
                routes.push_back(make_pair(nr, nc));
                if ((nr == 0) && (nc == 0)) {
                    return;
                }
            }
            d = (d + 1) % 4;
        }
    }
}

void debug() {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            printf("%-3d", map[i][j]);
        }
        printf("\n");
    }
}