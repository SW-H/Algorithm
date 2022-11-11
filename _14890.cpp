#include <iostream>
using namespace std;
bool isHorizontalSlope(int (*map)[101], int row, int col);
// bool isVerticalSlope(int row, int col);
int map[101][101];
int tranposedMap[101][101];
int N, L;
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
    int res = 0;
    bool allSame = true;
    for (int i = 0; i < N; i++) {
        allSame = true;
        for (int j = 1; j < N; j++) {
            if ((map[i][j] != map[i][j - 1]) && !isHorizontalSlope(map, i, j)) {
                allSame = false;
            }
        }
        if (allSame) {
            // cout << "#" << i << "\n";
            res++;
        }
        allSame = true;
        for (int j = 1; j < N; j++) {
            if ((tranposedMap[i][j] != tranposedMap[i][j - 1]) &&
                !isHorizontalSlope(tranposedMap, i, j)) {
                allSame = false;
            }
        }
        if (allSame) {
            // cout << "#" << i << "\n";
            res++;
        }
    }

    cout << res;
}

bool isHorizontalSlope(int (*map)[101], int row, int col) {
    if (abs(map[row][col] - map[row][col - 1]) != 1) {
        return false;
    }
    if (map[row][col] < map[row][col - 1]) { // 내리막길
        if ((col + L < N) && (map[row][col] != map[row][col + L - 1])) {
            return false;
        }
        for (int i = 1; i < L; i++) {
            if (col + i >= N || map[row][col + i] != map[row][col]) {
                return false;
            }
        }
    } else { // 오르막길
        if (col < L) {
            return false;
        }
        for (int i = 1; i <= L; i++) {
            if (col - i < 0 || (map[row][col - 1 - i] != map[row][col - 1])) {
                return false;
            }
        }
    }
    return true;
}

// bool isVerticalSlope(int row, int col) {
//     if (abs(map[row][col] - map[row][col - 1]) != 1) {
//         return false;
//     }
//     if (map[row][col] < map[row][col - 1]) { // 내리막길
//         if ((col + L < N) && (map[row][col] != map[row][col + L - 1])) {
//             return false;
//         }
//         for (int i = 1; i < L; i++) {
//             if (col + i >= N || map[row][col + i] != map[row][col]) {
//                 return false;
//             }
//         }
//     } else { // 오르막길
//         if (col < L) {
//             return false;
//         }
//         for (int i = 1; i <= L; i++) {
//             if (col - i < 0 || (map[row][col - 1 - i] != map[row][col - 1]))
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }