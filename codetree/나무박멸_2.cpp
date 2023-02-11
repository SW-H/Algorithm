#include <deque>
#include <iostream>
#include <utility>
using namespace std;

#define WALL -9999

int forest[21][21];
int row[] = {-1, 1, 0, 0}; // 상하좌우
int col[] = {0, 0, -1, 1};

int n, m, k, c;
int finalRes = 0;

deque<pair<int, int> /**/> treeLocation;

void grow();
int countTree(pair<int, int> loc);
bool isInRange(pair<int, int> loc);
void spread();
pair<int, int> decideLoc();
int kill(pair<int, int> loc);
void debug(pair<int, int> decided);

int main() {

    cin >> n >> m >> k >> c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> forest[i][j];
            if (forest[i][j] == -1) {
                forest[i][j] = WALL;
            } else if (forest[i][j] > 0) {
                treeLocation.push_back(make_pair(i, j));
            }
        }
    }

    pair<int, int> decided = make_pair(0, 0);

    for (int year = 1; year <= m; year++) {
        grow();
        spread();
        debug(decided);
        decided = decideLoc();
        finalRes += kill(decided);
        debug(decided);
    }
    cout << finalRes;
}

void grow() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((forest[i][j] < 0) && (forest[i][j] != WALL)) {
                forest[i][j]++;
            }
        }
    }
    for (int tree = 0; tree < treeLocation.size(); tree++) {
        pair<int, int> loc = treeLocation.at(tree);
        if (forest[loc.first][loc.second] > 0) {
            forest[loc.first][loc.second] += countTree(loc);
        }
    }
}

int countTree(pair<int, int> loc) {
    int cnt = 0, r, c;
    for (int d = 0; d < 4; d++) {
        r = loc.first + row[d];
        c = loc.second + col[d];
        if (isInRange(make_pair(r, c)) && (forest[r][c] > 0)) {
            cnt++;
        }
    }
    return cnt;
}

bool isInRange(pair<int, int> loc) {
    int r = loc.first;
    int c = loc.second;
    if ((r >= 0 && r < n) && (c >= 0 && c < n)) {
        return true;
    }
    return false;
}

void spread() {
    int r, c, cnt;
    int tmp[21][21] = {0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cnt = 0;
            if (forest[i][j] > 0) {
                for (int d = 0; d < 4; d++) {
                    r = i + row[d];
                    c = j + col[d];
                    if (isInRange(make_pair(r, c)) && (forest[r][c] == 0)) {
                        cnt++;
                    }
                }
                for (int d = 0; d < 4; d++) {
                    r = i + row[d];
                    c = j + col[d];
                    if ((forest[r][c] == 0) && (cnt > 0)) {
                        tmp[r][c] += (forest[i][j] / cnt);
                        treeLocation.push_back(make_pair(r, c));
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            forest[i][j] += tmp[i][j];
        }
    }
}

pair<int, int> decideLoc() {
    int res[21][21] = {0}, diedTree = 0;
    pair<int, int> ret;
    int r, c;
    int row[] = {-1, -1, 1, 1}; // 대각선
    int col[] = {1, -1, -1, 1};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (forest[i][j] > 0) {
                res[i][j] += forest[i][j];
                for (int d = 0; d < 4; d++) {
                    for (int cnt = 1; cnt <= k; cnt++) {
                        r = i + row[d] * cnt;
                        c = j + col[d] * cnt;
                        if (isInRange(make_pair(r, c)) && forest[r][c] >= 0) {
                            res[i][j] += forest[r][c];
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (res[i][j] > diedTree) {
                ret = make_pair(i, j);
                diedTree = res[i][j];
            }
        }
    }
    // for (int tree = 0; tree < treeLocation.size(); tree++) {
    //     pair<int, int> loc = treeLocation.at(tree); // 제초제 뿌릴 위치
    //     if (forest[loc.first][loc.second] <= 0) {
    //         continue;
    //     }
    //     res[loc.first][loc.second] += forest[loc.first][loc.second];
    //     for (int d = 0; d < 4; d++) {
    //         for (int cnt = 1; cnt <= k; cnt++) {
    //             r = loc.first + row[d] * cnt;
    //             c = loc.second + col[d] * cnt;
    //             if (isInRange(make_pair(r, c)) && forest[r][c] >= 0) {
    //                 res[loc.first][loc.second] += forest[r][c];
    //             } else {
    //                 break;
    //             }
    //         }
    //     }
    // }

    // for (int tree = 0; tree < treeLocation.size(); tree++) {
    //     pair<int, int> loc = treeLocation.at(tree); // 제초제 뿌릴 위치
    //     if (res[loc.first][loc.second] > diedTree) {
    //         ret = loc;
    //         diedTree = res[loc.first][loc.second];
    //     }
    // }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%-6d", res[i][j]);
            // cout << forest[i][j] << " ";
        }
        cout << "\n";
    }

    // finalRes += diedTree;
    return ret;
}

int kill(pair<int, int> loc) {
    int ret = 0, row, col;
    int rowD[] = {-1, -1, 1, 1}; // 대각선
    int colD[] = {1, -1, -1, 1};
    ret += forest[loc.first][loc.second];
    forest[loc.first][loc.second] = -1 * (c + 1);
    for (int d = 0; d < 4; d++) {
        for (int cnt = 1; cnt <= k; cnt++) {
            row = loc.first + rowD[d] * cnt;
            col = loc.second + colD[d] * cnt;
            // printf("(%d,%d)\n", row, col);
            // if (isInRange(make_pair(row, col)) && forest[row][col] > 0) {
            if (isInRange(make_pair(row, col))) {
                if (forest[row][col] > 0) {
                    ret += forest[row][col];
                    forest[row][col] = -1 * (c + 1);
                } else if (forest[row][col] != WALL) {
                    forest[row][col] = -1 * (c + 1);
                    break;
                } else{
                    break;
                }
            }
        }
    }
    return ret;
}

void debug(pair<int, int> decided) {
    cout << "==============================\n";
    cout << decided.first << ", " << decided.second << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%-6d", forest[i][j]);
            // cout << forest[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "==============================\n";
}