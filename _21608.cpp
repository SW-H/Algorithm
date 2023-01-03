#include <algorithm> // max
#include <iostream>
#include <utility> //pair
#include <vector>
using namespace std;

#define PREV_SETTING                                                           \
    ios_base::sync_with_stdio(false);                                          \
    cout.tie(NULL);                                                            \
    cin.tie(NULL);

int N;
int friends[4];
int emptySeats[21][21];
int score[21][21];
int seats[21][21];
int x[] = {0, 0, -1, 1}; // 상하좌우
int y[] = {-1, 1, 0, 0};
int stu;

void solve();

int main() {
    PREV_SETTING

    cin >> N;
    for (int i = 0; i < N * N; i++) {
        cin >> stu;
        for (int i = 0; i < 4; i++) {
            cin >> friends[i];
        }
        solve();
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << seats[i][j] << " ";
        }
        cout << "\n";
    }
}

void solve() {
    memset(score, 0, sizeof(score));
    int max = 0;
    pair<int, int> selected = make_pair(0, 0);
    // 1. 비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를
    // 정한다.
        // for (int i = 0; i < 4; i++) {
        //     cout << friends[i] << " ";
        // }
        // cout << "\n"; 
    int test;
    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {
            test = 0;
            if (seats[row][col] == 0) {
                for (int i = 0; i < 4; i++) {
                    if (row + y[i] > 0 && row + y[i] <= N && col + x[i] > 0 &&
                        col + x[i] <= N) {
                        if (seats[row + y[i]][col + x[i]] == 0) {
                            emptySeats[row][col]++;
                        } else {
                            for (int f = 0; f < 4; f++) {
                                if (seats[row + y[i]][col + x[i]] ==
                                    friends[f]) {
                                    test++;
                                }
                            }
                        }
                    }
                }
                // cout << test << "\n";
            }
        }
    }
    max = 0;
    selected = make_pair(0, 0);
    for (int row = N; row >= 1; row--) {
        for (int col = N; col >= 1; col--) {
            if (score[row][col] >= max && seats[row][col] == 0) {
                if (score[row][col] > max) {
                    max = score[row][col];
                    selected = make_pair(row, col);
                } else {
                    // 2. 1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서
                    // 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
                    if (emptySeats[row][col] >=
                        emptySeats[selected.first][selected.second]) {
                        selected.first = row;
                        selected.second = col;
                    }
                }
            }
        }
    }
    // cout << "\n********************************\n";
    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j <= N; j++) {
    //         cout << score[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    seats[selected.first][selected.second] = stu;
    for (int i = 0; i < 4; i++) {
        if (emptySeats[selected.first + y[i]][selected.second + x[i]] > 0) {
            emptySeats[selected.first + y[i]][selected.second + x[i]]--;
        }
    }
}