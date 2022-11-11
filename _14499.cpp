#include <iostream>
using namespace std;

int map[21][21];
int dice[7];
int tmp[7];
int mapRow, mapCol;
int x, y; // 주사위 위치

int main() {
    int moveCnt, direction, bottom;
    bool isMoved;
    cin >> mapRow >> mapCol >> y >> x >> moveCnt;
    for (int row = 0; row < mapRow; row++) {
        for (int col = 0; col < mapCol; col++) {
            cin >> map[row][col];
        }
    }

    for (int i = 0; i < moveCnt; i++) {
        cin >> direction;
        isMoved = true;
        copy(dice, dice + 7, tmp);
        if (direction == 1 && x + 1 < mapCol) { // 동
            x++;
            dice[3] = tmp[1];
            dice[6] = tmp[3];
            dice[1] = tmp[4];
            dice[4] = tmp[6];
        } else if (direction == 2 && x - 1 >= 0) { // 서
            x--;
            dice[1] = tmp[3];
            dice[3] = tmp[6];
            dice[4] = tmp[1];
            dice[6] = tmp[4];

        } else if (direction == 3 && y - 1 >= 0) { // 북
            y--;
            dice[2] = tmp[1];
            dice[6] = tmp[2];
            dice[1] = tmp[5];
            dice[5] = tmp[6];

        } else if (direction == 4 && y + 1 < mapRow) { // 남
            y++;
            dice[1] = tmp[2];
            dice[2] = tmp[6];
            dice[5] = tmp[1];
            dice[6] = tmp[5];
        } else {
            isMoved = false;
        }
        if (isMoved) {
            if (map[y][x] == 0) {
                map[y][x] = dice[6];
            } else {
                dice[6] = map[y][x];
                map[y][x] = 0;
            }
            cout << dice[1] << "\n";
        }
    }
    return 0;
}
