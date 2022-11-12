#include <iostream>
using namespace std;
bool isHorizontalSlope(int (*map)[101], int row, int col);
void solve(int (*map)[101]);

int map[101][101];
int tranposedMap[101][101];
bool slope[101][101];
int res, N, L;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> L;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            tranposedMap[j][i] = map[i][j];
        }
    }

    solve(map);
    solve(tranposedMap);

    cout << res;
}

void solve(int (*map)[101]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            slope[i][j] = false;
        }
    }
    bool allSame = true;
    for (int i = 0; i < N; i++) {
        allSame = true;
        for (int j = 1; j < N; j++) {
            if ((map[i][j] != map[i][j - 1]) && !isHorizontalSlope(map, i, j)) {
                allSame = false;
            }
        }
        if (allSame) {
            res++;
        }
    }
}

bool isHorizontalSlope(int (*map)[101], int row, int col) {
    bool isGrowing = false; // F : 내리막길, T : 오르막길
    if (abs(map[row][col] - map[row][col - 1]) != 1) {
        return false;
    }
    if (map[row][col] < map[row][col - 1]) { // 내리막길
        if ((col + L - 1 < N) && (map[row][col] != map[row][col + L - 1])) {
            return false;
        }
        for (int i = 1; i < L; i++) {
            if (col + i >= N || map[row][col + i] != map[row][col]) {
                return false;
            }
        }
    } else { // 오르막길
        isGrowing = true;
        if (col < L) {
            return false;
        }
        for (int i = 1; i < L; i++) {
            if (col - i < 0 || (map[row][col - 1 - i] != map[row][col - 1])) {
                return false;
            }
        }
    }
    if (isGrowing) {
        for (int i = 1; i <= L; i++) {
            if (slope[row][col - i]) {
                return false;
            }
        }
    } else {
        for (int i = 0; i < L; i++) {
            if (slope[row][col + i]) {
                return false;
            }
        }
    }
    if (isGrowing) {
        for (int i = 1; i <= L; i++) {
            slope[row][col - i] = true;
        }
    } else {
        for (int i = 0; i < L; i++) {
            slope[row][col + i] = true;
        }
    }
    return true;
}
