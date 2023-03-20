#include <algorithm>
#include <iostream>
using namespace std;

int n, finalScore;
bool likes[400][401];
int rides[21][21] = {};

void rideOn(int stu, bool *likes);
int calcFriends(pair<int, int> loc, bool *likes);
int calcBlank(pair<int, int> loc);
void debug();

int main() {
    cin >> n;
    int stu, like;
    for (int i = 0; i < n * n; i++) {
        cin >> stu;
        for (int lv = 0; lv < 4; lv++) {
            cin >> like;
            likes[stu][like] = true;
        }

        rideOn(stu, likes[stu]);
        // debug();
    }

    // 최종 점수 계산
    int board[] = {0, 1, 10, 100, 1000};
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            finalScore +=
                board[calcFriends(make_pair(r, c), likes[rides[r][c]])];
        }
    }

    cout << finalScore << "\n";
}

void rideOn(int stu, bool *likes) {
    int score = 0, tmp;
    pair<int, int> seat(-1, -1);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (rides[r][c] == 0) {
                tmp = calcFriends(make_pair(r, c), likes);
                if ((score < tmp) ||
                    ((score == tmp) &&
                     (calcBlank(seat) < calcBlank(make_pair(r, c))))) {
                    score = tmp;
                    seat = make_pair(r, c);
                }
            }
        }
    }
    rides[seat.first][seat.second] = stu;
}

int calcBlank(pair<int, int> loc) {
    if ((loc.first == -1) && (loc.second == -1)) {
        return -1;
    }
    // 상하좌우
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int nr = loc.first + dr[d];
        int nc = loc.second + dc[d];
        if ((0 <= nr) && (nr < n) && (0 <= nc) && (nc < n)) {
            if (rides[nr][nc] == 0) {
                ret++;
            }
        }
    }
    return ret;
}

int calcFriends(pair<int, int> loc, bool *likes) {
    if ((loc.first == -1) && (loc.second == -1)) {
        return -1;
    }
    // 상하좌우
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int nr = loc.first + dr[d];
        int nc = loc.second + dc[d];
        if ((0 <= nr) && (nr < n) && (0 <= nc) && (nc < n)) {
            if (likes[rides[nr][nc]]) {
                ret++;
            }
        }
    }
    return ret;
}

void debug() {
    printf("\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%-5d", rides[r][c]);
        }
        printf("\n");
    }
}