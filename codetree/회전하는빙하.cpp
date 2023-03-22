#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
using namespace std;

int n, q;  //  2^n*2^n, 회전 횟수 q
int glacier[65][65];

int nextGlacier[65][65];

// 우, 하, 상, 좌
int dr[] = {0, 1, -1, 0};
int dc[] = {1, 0, 0, -1};
int rotateLv, sz, unitSz;

void restore();
void move(pair<int, int> from);
void debug();
void mapCopy(int fromR, int fromC, int toR, int toC);
void melt();
int calcIce(int r, int c);
void calcRes();
int bfs(int r, int c);

int main() {
    cin >> n >> q;
    n = pow(2, n);
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cin >> glacier[r][c];
        }
    }
    for (int rnd = 0; rnd < q; rnd++) {
        // 2^L * 2^L 격자 안에서 4등분해서 회전
        cin >> rotateLv;        // ex)2
        sz = pow(2, rotateLv);  // ex)4
        // 가로,세로로 sz/unitSz개씩
        unitSz = sz / 2;  // 4등분 했을 때 사이즈 , ex)2
        if (rotateLv > 0) {
            memset(nextGlacier, 0, sizeof(nextGlacier));
            for (int r = 1; r <= n; r += sz) {
                for (int c = 1; c <= n; c += sz) {  // 범위 선택
                    move(make_pair(r, c));
                }
            }
            restore();
        }
        melt();
    }
    calcRes();
}

void calcRes() {  // bfs
    int res = 0;
    int sum = 0;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (glacier[r][c] == 0) {
                continue;
            }
            sum += glacier[r][c];
            int tmp = bfs(r, c);
            if (res < tmp) {
                res = tmp;
            }
        }
    }

    cout << sum << "\n"
         << res;
}

int bfs(int r, int c) {
    int res = 0;
    bool visitied[65][65] = {};

    deque<pair<int, int> > queue;
    queue.push_back(make_pair(r, c));

    while (!queue.empty()) {
        pair<int, int> ice = queue.front();
        queue.pop_front();
        if (!visitied[ice.first][ice.second]) {
            visitied[ice.first][ice.second] = true;

            res++;
            for (int d = 0; d < 4; d++) {
                int nr = ice.first + dr[d];
                int nc = ice.second + dc[d];
                if ((1 <= nr) && (nr <= n) &&
                    (1 <= nc) && (nc <= n) &&
                    (!visitied[nr][nc]) &&
                    (glacier[nr][nc] > 0)) {
                    queue.push_back(make_pair(nr, nc));
                }
            }
        }
    }
    return res;
}

void melt() {
    int tmp[65][65] = {};
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (calcIce(r, c) < 3) {
                tmp[r][c] = max(glacier[r][c] - 1, 0);
            } else {
                tmp[r][c] = glacier[r][c];
            }
        }
    }
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            glacier[r][c] = tmp[r][c];
        }
    }
}

int calcIce(int r, int c) {
    int ice = 0;
    for (int d = 0; d < 4; d++) {
        if ((1 <= r + dr[d]) && (r + dr[d] <= n) &&
            (1 <= c + dc[d]) && (c + dc[d] <= n) &&
            (glacier[r + dr[d]][c + dc[d]] > 0)) {
            ice++;
        }
    }
    return ice;
}

void restore() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            glacier[r][c] = nextGlacier[r][c];
        }
    }
}

void move(pair<int, int> from) {  // 선택된 범위
    int nr = from.first;
    int nc = from.second;

    mapCopy(nr, nc, nr, nc + unitSz);
    mapCopy(nr, nc + unitSz, nr + unitSz, nc + unitSz);
    mapCopy(nr + unitSz, nc + unitSz, nr + unitSz, nc);
    mapCopy(nr + unitSz, nc, nr, nc);
}

void mapCopy(int fromR, int fromC, int toR, int toC) {
    for (int r = 0; r < unitSz; r++) {
        for (int c = 0; c < unitSz; c++) {
            nextGlacier[toR + r][toC + c] = glacier[fromR + r][fromC + c];
        }
    }
}

void debug() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cout << setw(5) << glacier[r][c];
        }
        cout << "\n";
    }
    cout << "\n";
}