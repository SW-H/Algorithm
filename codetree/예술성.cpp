#include <deque>
#include <iostream>
#include <utility>
using namespace std;

void divideTeam();
void dfs(int row, int col);

void debug();
int calcScore();
int countAdj(int gr1, int gr2);
// int sumOf(int gr);
void rotate();

int picture[30][30];
int group[30][30];
int groupCnt[30 * 30 + 1];
int consistOf[30 * 30 + 1];
bool visited[30][30];
int n, groupN;

int dr[] = {-1, 1, 0, 0}; // 상하좌우
int dc[] = {0, 0, -1, 1};

#define isInRange(row, col) (1 <= row && row <= n && 1 <= col && col <= n)

int main() {
    cin >> n;

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            cin >> picture[row][col];
        }
    }

    int score = 0;
    // divideTeam();
    // score += calcScore(); // 초기 예술 점수
    // cout << score;
    // for (int r = 1; r < 3; r++) {
    rotate();
    debug();
    // score += calcScore();
    // }
}
int calcScore() {
    int ret = 0;
    int adjCnt;
    for (int g1 = 1; g1 <= groupN - 1; g1++) {
        for (int g2 = g1 + 1; g2 <= groupN; g2++) {
            adjCnt = countAdj(g1, g2);
            if (adjCnt > 0) {
                ret += ((groupCnt[g1] + groupCnt[g2]) * consistOf[g1] *
                        consistOf[g2] * countAdj(g1, g2));
                // cout << g1 << "," << g2 << ":" << countAdj(g1, g2) << "\n";
            }
        }
    }
    return ret;
}

int countAdj(int gr1, int gr2) { //!
    int ret = 0;
    memset(visited, false, sizeof(visited));

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            if ((group[row][col] == gr1) && !visited[row][col]) {
                visited[row][col] = true;
                for (int d = 0; d < 4; d++) {
                    int nx = row + dr[d];
                    int ny = col + dc[d];
                    if (isInRange(nx, ny) && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        if (group[nx][ny] == gr2) {
                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
}

// int sumOf(int gr) {
//     int sum = 0;
//     for (int row = 1; row <= n; row++) {
//         for (int col = 1; col <= n; col++) {
//             if (group[row][col] == gr) {
//                 sum += picture[row][col];
//             }
//         }
//     }
//     return sum;
// }

void divideTeam() { 
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            if (!visited[row][col]) {
                groupN++;
                consistOf[groupN] = picture[row][col];
                visited[row][col] = true;
                group[row][col] = groupN;
                groupCnt[groupN] = 1;
                dfs(row, col);
            }
        }
    }
}

void dfs(int row, int col) {
    for (int d = 0; d < 4; d++) {
        int nx = row + dr[d];
        int ny = col + dc[d];
        if (isInRange(nx, ny) && !visited[nx][ny] &&
            picture[nx][ny] == picture[row][col]) {
            visited[nx][ny] = true;
            group[nx][ny] = groupN;
            groupCnt[groupN]++;
            dfs(nx, ny);
        }
    }
}

///////
void debug() {
    // for (int i = 1; i <= groupN; i++) {
    //     cout << groupCnt[i] << "\n";
    // }

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            printf("%-6d", picture[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

void rotate() {
    // 십자모양
    int res[30][30] = {};
    // int row = n / 2;

    // for (int col = 1; col <= n; col++) { // ㅁㅁㅁㅁㅁ
    //     res[row][col] = picture[col][row];
    // }
    // int col = n/2;
    // for (int row = 1; row <= n; row++) {
    //     res[row][col] = picture[col][n-row+1];
    // }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) {
            // 세로줄 : (i, j) -> (j, i)
            if(j == n / 2){
                res[j][i] = picture[i][j];
            }
            // 가로줄: (i, j) -> (n - j - 1, i)
            else if(i == n / 2){
                res[n - j - 1][i] = picture[i][j];
            }
        }
    }

    // 나머지 정사각형
    int size = (n - 1) / 2;

    // //1사분면
    // for (int row = 1; row <= size; row++) {
    //     for (int col = 1; col <= size; col++) {
    //         res[row][col] = picture[col][row];
    //     }
    // }

    for (int row = 1; row <= size; row++) {
        for (int col = 1; col <= size; col++) {
            picture[row][col] = res[row][col];
        }
    }

    // //2사분면
    // for (int row = 1; row <= size; row++) {
    //     for (int col = 1; col <= size; col++) {
    //     }
    // }

    // //3사분면
    // for (int row = 1; row <= size; row++) {
    //     for (int col = 1; col <= size; col++) {
    //     }
    // }

    // //4사분면
    // for (int row = 1; row <= size; row++) {
    //     for (int col = 1; col <= size; col++) {
    //     }
    // }
}