#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

int n, cnt;
int map[21][21];

struct DICE {
    pair<int, int> loc; // (row,col)
    int d;              // 상우하좌(0,1,2,3)
    int bottom;
};

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int score;
bool visited[21][21];
int diceN[] = {0, 1, 2, 3, 4, 5, 6};
DICE dice = {make_pair(1, 1), 1, 6};

void calcScore(pair<int, int> loc, int crt);
void move();
void changeD();
int getNextDice(int d);

int main() {
    // input
    cin >> n >> cnt;

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            cin >> map[row][col];
        }
    }
    score = 0;
    for (int round = 1; round <= cnt; round++) {
        move();
        changeD();
        memset(visited, false, sizeof(visited));
        calcScore(dice.loc, map[dice.loc.first][dice.loc.second]);
    }
    cout << score;
}

void move() {
    pair<int, int> nr(dice.loc.first + dr[dice.d],
                      dice.loc.second + dc[dice.d]);

    if ((1 <= nr.first && nr.first <= n) &&
        (1 <= nr.second && nr.second <= n)) {
        dice.loc = nr;
        dice.bottom = getNextDice(dice.d);
    } else {
        dice.d = (dice.d + 2) % 4;
        return move();
    }
}

void calcScore(pair<int, int> loc, int crt) {
    if ((map[loc.first][loc.second] == crt) &&
        !visited[loc.first][loc.second]) {
        score += crt;
        visited[loc.first][loc.second] = true;
        for (int d = 0; d < 4; d++) {
            if (loc.first + dr[d] <= 0 || loc.first + dr[d] > n ||
                loc.second + dc[d] <= 0 || loc.second + dc[d] > n) {
                continue;
            }
            calcScore(make_pair(loc.first + dr[d], loc.second + dc[d]), crt);
        }
    }
}

void changeD() {
    if (map[dice.loc.first][dice.loc.second] == dice.bottom) {
        return;
    }
    if (map[dice.loc.first][dice.loc.second] < dice.bottom) { // 시계방향 회전
        dice.d = (dice.d + 1) % 4;
    } else {
        dice.d = (dice.d + 3) % 4;
    }
}


int getNextDice(int d) {
    int newDice[7] = {0};
    switch (d) {
    case 0: // 상
        newDice[1] = diceN[2];
        newDice[2] = diceN[6];
        newDice[3] = diceN[3];
        newDice[4] = diceN[4];
        newDice[5] = diceN[1];
        newDice[6] = diceN[5];
        break;
    case 1: // 우
        newDice[1] = diceN[4];
        newDice[2] = diceN[2];
        newDice[3] = diceN[1];
        newDice[4] = diceN[6];
        newDice[5] = diceN[5];
        newDice[6] = diceN[3];
        break;
    case 2: // 하
        newDice[1] = diceN[5];
        newDice[2] = diceN[1];
        newDice[3] = diceN[3];
        newDice[4] = diceN[4];
        newDice[5] = diceN[6];
        newDice[6] = diceN[2];
        break;
    case 3: // 좌
        newDice[1] = diceN[3];
        newDice[2] = diceN[2];
        newDice[3] = diceN[6];
        newDice[4] = diceN[1];
        newDice[5] = diceN[5];
        newDice[6] = diceN[4];
        break;
    }
    for (int i = 1; i <= 6; i++) {
        diceN[i] = newDice[i];
    }
    return diceN[6];
}