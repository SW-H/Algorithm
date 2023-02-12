#include <iostream>
using namespace std;

void grow();
void breed();
int isInRange(int r, int c);
int countTree(int r, int c);
pair<int, int> decideLoc();
int eradicate(pair<int, int> pesticide);
void debug();

int n, year, range, delay;
int forest[21][21];

int dirR[] = {-1, 1, 0, 0}; // 상하좌우
int dirC[] = {0, 0, -1, 1};
int diagR[] = {-1, -1, 1, 1}; // 대각선 - 왼쪽위부터 시계 방향
int diagC[] = {-1, 1, 1, -1};

#define WALL -9999

int main() {
    cin >> n >> year >> range >> delay;

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cin >> forest[r][c];
            if (forest[r][c] == -1) {
                forest[r][c] = WALL;
            }
        }
    }
    pair<int, int> pesticide;
    int res = 0;
    for (int y = 1; y <= year; y++) {
        grow();                  // 성장
        breed();                 // 번식
        pesticide = decideLoc(); // 제초제 뿌릴 위치 선정
        printf("(%d,%d)\n", pesticide.first, pesticide.second);
        res += eradicate(pesticide); // 박멸
        debug();
    }
    cout << res;
}

void grow() {
    int res[21][21] = {};

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            if (forest[r][c] > 0) {
                res[r][c] += countTree(r, c);
            } else if ((forest[r][c] != 0) && (forest[r][c] != WALL)) {
                forest[r][c]++;
            }
        }
    }

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            forest[r][c] += res[r][c];
        }
    }
}
int isInRange(int r, int c) { return (r > 0 && r <= n && c > 0 && c <= n); }

int countTree(int r, int c) {
    int row, col, cnt = 0;
    for (int d = 0; d < 4; d++) {
        row = r + dirR[d];
        col = c + dirC[d];
        if (isInRange(row, col) && forest[row][col] > 0) {
            cnt++;
        }
    }
    return cnt;
}

void breed() {
    int res[21][21] = {};
    int cnt, row, col;
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cnt = 0;
            if (forest[r][c] > 0) {
                for (int d = 0; d < 4; d++) {
                    row = r + dirR[d];
                    col = c + dirC[d];
                    if (isInRange(row, col) &&(forest[row][col] == 0)) {
                        cnt++;
                    }
                }
                for (int d = 0; d < 4; d++) {
                    if(forest[r + dirR[d]][c+dirC[d]] == 0){
                        res[r+dirR[d]][c+dirC[d]] += (forest[r][c] / cnt);
                    }
                }
            }
        }
    }

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            forest[r][c] += res[r][c];
        }
    }
}

pair<int, int> decideLoc() {
    int row, col, cnt = 0, tmp = 0;
    pair<int, int> ret;

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            tmp = 0;
            if (forest[r][c] > 0) {
                tmp += forest[r][c];
                for (int d = 0; d < 4; d++) {
                    for (int ran = 1; ran <= range; ran++) {
                        row = r + diagR[d] * ran;
                        col = c + diagC[d] * ran;

                        if (forest[row][col] <= 0) {
                            break;
                        } else {
                            tmp += forest[row][col];
                        }
                    }
                }
                if (cnt < tmp) {
                    cnt = tmp;
                    ret = make_pair(r, c);
                }
            }
        }
    }
    return ret;
}

int eradicate(pair<int, int> pesticide) {
    int row, col, ret;
    ret = forest[pesticide.first][pesticide.second];
    forest[pesticide.first][pesticide.second] = -1 * (delay + 1);
    for (int d = 0; d < 4; d++) {
        for (int ran = 1; ran <= range; ran++) {
            row = pesticide.first + diagR[d] * ran;
            col = pesticide.second + diagC[d] * ran;
            if (forest[row][col] != WALL) {
                forest[row][col] = -1 * (delay + 1);
            }
            if (forest[row][col] <= 0) {
                break;
            } else {
                ret += forest[row][col];
            }
        }
    }
    return ret;
}

void debug() {
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            printf("%-6d", forest[r][c]);
        }
        cout << "\n";
    }
    cout << "\n";
}
