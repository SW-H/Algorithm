#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int n, year;
int trees[15][15];
int d, p;

vector<pair<int, int> /**/> locs; //(row,col)
// → ↗ ↑ ↖ ← ↙ ↓ ↘
int nr[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int nc[] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

int supplements[15][15];

void initialize();
void input();
void solve();
void debug();

int main() {
    input();
    initialize();
    solve();
    int res = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            res += trees[row][col];
        }
    }
    cout << res << "\n";
}

void solve() {
    // ↗ ↖ ↙ ↘
    int diagR[] = {-1, -1, 1, 1};
    int diagC[] = {1, -1, -1, 1};

    for (int y = 1; y <= year; y++) {
        cin >> d >> p;
        // 이동
        for (auto &loc : locs) {
            loc.first = (loc.first + (nr[d] + n) * p) % n; //?
            loc.second = (loc.second + (nc[d] + n) * p) % n;
        }
        // 특수영양제가 있는 땅 높이 1증가
        for (auto &loc : locs) {
            trees[loc.first][loc.second]++;
            supplements[loc.first][loc.second] = 1;
        }
        // 특수영양제가 있는 땅 대각선 나무 높이 1증가
        for (auto &loc : locs) {
            for (int d = 0; d < 4; d++) {
                if ((loc.first + diagR[d] < 0) || (loc.first + diagR[d] >= n) ||
                    (loc.second + diagC[d] < 0) ||
                    (loc.second + diagC[d] >= n)) {
                    continue;
                }
                if (trees[loc.first + diagR[d]][loc.second + diagC[d]] >= 1) {
                    trees[loc.first][loc.second]++;
                }
            }
        }
        locs.clear();
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if ((supplements[row][col] == 0) && (trees[row][col] >= 2)) {
                    trees[row][col] -= 2;
                    locs.push_back(make_pair(row, col));
                } else if (supplements[row][col] > 0) {
                    supplements[row][col] = 0;
                }
            }
        }
    }
}

void initialize() {
    locs.push_back(make_pair(n - 1, 0));
    locs.push_back(make_pair(n - 2, 0));
    locs.push_back(make_pair(n - 1, 1));
    locs.push_back(make_pair(n - 2, 1));
}

void input() {
    cin >> n >> year;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> trees[row][col];
        }
    }
}

void debug() {
    printf("\n");
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%-3d", trees[row][col]);
        }
        printf("\n");
    }
}