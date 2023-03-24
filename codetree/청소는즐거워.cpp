#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int n, res, d = -1;
int dust[500][500];

// 좌, 하, 우, 상
int dr[] = {0, 1, 0, -1};
int dc[] = {-1, 0, 1, 0};

vector<pair<pair<int, int>, double> > rates[4];

void init();
void addDust(pair<int, int> loc);
int add(pair<int, int> loc, pair<pair<int, int>, double> r, int isLast = -1);
void debug();
int main() {
    cin >> n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> dust[r][c];
        }
    }
    init();
    int len = 1;
    int nr = n / 2;
    int nc = n / 2;
    while (true) {
        d = (d + 1) % 4;
        for (int l = 0; l < len; l++) {
            nc += dc[d];
            nr += dr[d];
            addDust(make_pair(nr, nc));
            debug();
            if (nc == 0 && nr == 0) {
                cout << res;
                return 0;
            }
        }
        if ((d == 1) || (d == 3)) {
            len++;
        }
    }
}

void init() {  // 위치별 먼지 비율 추가
    // 좌
    vector<pair<pair<int, int>, double> > tmp[] =
        // 좌
        {{{{-1, 0}, 0.07}, {{1, 0}, 0.07}, {{-1, 1}, 0.01}, {{1, 1}, 0.01}, {{-1, -1}, 0.1}, {{1, -1}, 0.1}, {{-2, 0}, 0.02}, {{2, 0}, 0.02}, {{0, -2}, 0.05}, {{0, -1}, 0}},
         // 하
         {{{0, -1}, 0.07}, {{0, 1}, 0.07}, {{0, -2}, 0.02}, {{0, 2}, 0.02}, {{-1, -1}, 0.01}, {{-1, 1}, 0.01}, {{1, -1}, 0.1}, {{1, 1}, 0.1}, {{2, 0}, 0.05}, {{1, 0}, 0}}};
    rates[0] = tmp[0];
    rates[1] = tmp[1];

    // 우
    for (auto r : tmp[0]) {
        rates[2].push_back({{r.first.first, -1 * r.first.second}, r.second});
    }
    // 상
    for (auto r : tmp[1]) {
        rates[3].push_back({{-1 * r.first.first, r.first.second}, r.second});
    }
}

void addDust(pair<int, int> loc) {
    int alpha = 0;
    int amount = dust[loc.first][loc.second];
    double rate;
    for (int i = 0; i < rates[d].size() - 1; i++) {
        auto r = rates[d][i];
        alpha += add(loc, r);
    }
    add(loc, rates[d][rates[d].size() - 1], alpha);
    dust[loc.first][loc.second] = 0;
}

int add(pair<int, int> loc, pair<pair<int, int>, double> r, int isLast) {
    double rate = r.second;
    int amount = dust[loc.first][loc.second];
    int alpha = (int)(amount * rate);
    int nr = loc.first + r.first.first;
    int nc = loc.second + r.first.second;
    int value = (int)(amount * rate);
    if (isLast >= 0) {
        value = max(dust[loc.first][loc.second] - isLast, 0);
    }

    if ((nr < 0) || (nr >= n) || (nc < 0) || (nc >= n)) {
        res += value;

    } else {
        dust[nr][nc] += value;
    }
    return value;
}

void debug() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << setw(5) << dust[r][c];
        }
        cout << "\n";
    }
    cout << "\n";
}
