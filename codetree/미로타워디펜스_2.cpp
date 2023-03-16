#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

int n, round, score;
int map[25][25];
// → ↓ ← ↑
int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};
vector<pair<int, int> /**/> routes;
pair<int, int> player;

void fillBlank();
void makeRoutes();
void debug();
void delMonsters();
void makeMap();

int main() {

    // input
    cin >> n >> round;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> map[r][c];
        }
    }
    player = make_pair(n / 2, n / 2);
    makeRoutes();
    int d, p;
    for (int r = 1; r <= round; r++) {
        // d:  → ↓ ← ↑
        cin >> d >> p;

        // 플레이어 공격
        for (int i = 1; i <= p; i++) {
            int nr = player.first + dr[d] * i;
            int nc = player.second + dc[d] * i;
            score += map[nr][nc];
            map[nr][nc] = 0;
        }
        // 빈 공간 채우기
        fillBlank();
        // 4번이상 반복 몬스터 제거
        delMonsters();
        makeMap();
    }
    cout << score << "\n";
}
void makeMap() {
    int count = 1;
    int newMap[25][25] = {};
    int idx = 0;
    for (int i = 0; i < routes.size() - 1; i++) {
        int r = routes[i].first;
        int c = routes[i].second;
        if (map[r][c] == 0) {
            break;
        }
        if ((map[r][c] == map[routes[i + 1].first][routes[i + 1].second]) &&
            (i + 2 < routes.size())) {
            count++;
        } else {
            if (idx >= routes.size()) {
                break;
            }
            newMap[routes[idx].first][routes[idx].second] = count;
            idx++;
            if (idx >= routes.size()) {
                break;
            }
            newMap[routes[idx].first][routes[idx].second] = map[r][c];
            idx++;
            count = 1;
            if (map[routes[i + 1].first][routes[i + 1].second] == 0) {
                break;
            }
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            map[r][c] = newMap[r][c];
        }
    }
}

void delMonsters() {
    int count = 1;
    bool didKill = false;
    int i, r, c;
    for (i = 0; i < routes.size() - 1; i++) {
        r = routes[i].first;
        c = routes[i].second;
        if (map[r][c] == 0) {
            break;
        }
        if (map[r][c] == map[routes[i + 1].first][routes[i + 1].second]) {
            count++;
        } else if (count >= 4) {
            score += map[r][c] * count;
            for (int del = 0; del < count; del++) {
                map[routes[i - del].first][routes[i - del].second] = 0;
            }
            didKill = true;
            count = 1;
        } else {
            count = 1;
        }
    }
    if (count >= 4) {
        score += map[r][c] * count;
        for (int del = 0; del < count; del++) {
            map[routes[i - del].first][routes[i - del].second] = 0;
        }
        didKill = true;
        i = -1;
        count = 1;
    }
    fillBlank();
    if (didKill) {
        delMonsters();
    }
}

void fillBlank() {
    int newMap[25][25] = {};
    int toIdx, fromIdx;
    for (toIdx = fromIdx = 0; fromIdx < routes.size() && toIdx < routes.size();
         toIdx++) {
        if (map[routes[fromIdx].first][routes[fromIdx].second] == 0) {
            while (fromIdx < routes.size() &&
                   map[routes[fromIdx].first][routes[fromIdx].second] == 0) {
                fromIdx++;
            }
        }
        newMap[routes[toIdx].first][routes[toIdx].second] =
            map[routes[fromIdx].first][routes[fromIdx].second];
        fromIdx++;
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            map[r][c] = newMap[r][c];
        }
    }
}

void makeRoutes() {
    int nr = player.first;
    int nc = player.second;
    // → ↓ ← ↑
    int cnt = 1, d = 2;
    while (true) {
        for (int r = 0; r < 2; r++) {
            for (int i = 0; i < cnt; i++) {
                nr += dr[d];
                nc += dc[d];
                routes.push_back(make_pair(nr, nc));
                if ((nr == 0) && (nc == 0)) {
                    return;
                }
            }
            d = (d + 3) % 4;
        }
        cnt++;
    }
}

void debug() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%-3d", map[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}