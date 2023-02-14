#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void debug();
void move();
bool isInRange(int row, int col);
pair<int, int> throwBall(int round);
int getScore(pair<int, int> scorer);
int calcScore(int score, pair<int, int> now, pair<int, int> target);
pair<int, int> findHead(pair<int, int> scorer);
pair<int, int> findTail(pair<int, int> scorer);
bool isPlayer(int row, int col);
int findLines(vector<pair<int, int> /**/> &lines, pair<int, int> now);

int n, m, k;
int input[21][21];
int tmp[21][21];
bool visited[21][21];
int dirR[] = {-1, 1, 0, 0}; // 상하좌우
int dirC[] = {0, 0, -1, 1};

vector<pair<int, int> /**/> headPlayers;

#define HEAD 1
#define PLAYER 2
#define TAIL 3
#define LINE 4

int main() {
    cin >> n >> m >> k; // 격자의 크기 n, 팀의 개수 m, 라운드 수 k
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cin >> input[r][c];
            if (input[r][c] == HEAD) {
                headPlayers.push_back(make_pair(r, c));
            }
        }
    }

    int score = 0;
    pair<int, int> scorer;
    pair<int, int> head;
    pair<int, int> tail;

    for (int round = 1; round <= k; round++) {
        move();
        debug();
        scorer = throwBall(round % (4 * n));
        if (scorer.first != 0) {
            score += getScore(scorer);
            // printf("(%d,%d)\n", scorer.first, scorer.second);
            // cout << round << " : " << score << "\n";
        }
        // cout << score << "\n";
    }
    cout << score;
}

int getScore(pair<int, int> scorer) {
    int ret;
    std::vector<pair<int, int> /**/>::iterator it;

    memset(visited, false, sizeof(visited));
    pair<int, int> head = findHead(scorer);
    vector<pair<int, int> /**/> lines;
    memset(visited, false, sizeof(visited));
    findLines(lines, head);
    it = find(lines.begin(), lines.end(), scorer);
    ret = it - lines.begin() + 1;
    ret = ret * ret;

    it = find(headPlayers.begin(), headPlayers.end(), head);
    *it = lines.back();

    input[head.first][head.second] = TAIL;
    input[lines.back().first][lines.back().second] = HEAD;
    return ret;
}

int calcScore(int score, pair<int, int> now, pair<int, int> target) {
    if (now.first == target.first && now.second == target.second) {
        return (score + 1) * (score + 1);
    }
    if (input[now.first][now.second] == TAIL) {
        return 0;
    }
    int row, col;
    visited[now.first][now.second] = true;
    for (int dir = 0; dir < 4; dir++) {
        row = now.first + dirR[dir];
        col = now.second + dirC[dir];
        if (isInRange(row, col) && visited[row][col] == false &&
            isPlayer(row, col)) {
            return calcScore(score + 1, make_pair(row, col), target);
        }
    }
    return 0;
}

pair<int, int> findHead(pair<int, int> scorer) { // DFS
    int row, col;
    if (input[scorer.first][scorer.second] == HEAD) {
        return scorer;
    }
    visited[scorer.first][scorer.second] = true;
    for (int dir = 0; dir < 4; dir++) {
        row = scorer.first + dirR[dir];
        col = scorer.second + dirC[dir];
        if (isInRange(row, col) && (visited[row][col] == false) &&
            isPlayer(row, col)) {
            pair<int, int> tmp;
            if ((tmp = findHead(make_pair(row, col))).first != 0) {
                return tmp;
            }
        }
    }
    return make_pair(0, 0);
}
pair<int, int> findTail(pair<int, int> scorer) { // DFS
    int row, col;
    if (input[scorer.first][scorer.second] == TAIL) {
        return scorer;
    }
    visited[scorer.first][scorer.second] = true;
    for (int dir = 0; dir < 4; dir++) {
        row = scorer.first + dirR[dir];
        col = scorer.second + dirC[dir];
        if (isInRange(row, col) && (visited[row][col] == false) &&
            isPlayer(row, col)) {
            pair<int, int> tmp;
            if ((tmp = findTail(make_pair(row, col))).first != 0) {
                return tmp;
            }
        }
    }
    return make_pair(0, 0);
}

bool isPlayer(int row, int col) {
    return (HEAD <= input[row][col] && input[row][col] <= TAIL);
}

pair<int, int> throwBall(int round) {
    if (1 <= round && round <= n) {
        for (int col = 1; col <= n; col++) {
            if (HEAD <= input[round][col] && input[round][col] <= TAIL) {
                return make_pair(round, col);
            }
        }
    }
    if (n + 1 <= round && round <= 2 * n) {
        for (int row = n; row >= 1; row--) {
            if (HEAD <= input[row][round % n] &&
                input[row][round % n] <= TAIL) {
                return make_pair(row, round % n);
            }
        }
    }
    if (2 * n + 1 <= round && round <= 3 * n) {
        for (int col = n; col >= 1; col--) {
            if (HEAD <= input[round % 2 * n][col] &&
                input[round % 2 * n][col] <= TAIL) {
                return make_pair(round % 2 * n, col);
            }
        }
    }
    if (3 * n + 1 <= round && round <= 4 * n) {
        for (int row = 1; row <= n; row++) {
            if (HEAD <= input[row][round % 3 * n] &&
                input[row][round % 3 * n] <= TAIL) {
                return make_pair(row, round % 3 * n);
            }
        }
    }
    return make_pair(0, 0);
}
int findLines(vector<pair<int, int> /**/> &lines, pair<int, int> now) {
    lines.push_back(now);
    if ((input[now.first][now.second] == TAIL) && (lines.size() >= 3)) {
        return 0;
    }
    visited[now.first][now.second] = true;
    int row, col;
    for (int dir = 0; dir < 4; dir++) {
        row = now.first + dirR[dir];
        col = now.second + dirC[dir];
        if (isInRange(row, col) && (visited[row][col] == false) &&
            isPlayer(row, col)) {
            if (((input[now.first][now.second] == TAIL) &&
                (input[row][col] != HEAD)) || (((input[now.first][now.second] == HEAD) &&
                (input[row][col] == TAIL) && (lines.size()<3)))) {
                continue;
            }
            return findLines(lines, make_pair(row, col));
        }
    }
    return 0;
}

void move() {
    vector<pair<int, int> /**/> lines;
    int row, col;
    memset(visited, 0, sizeof(visited));
    for (int team = 0; team < m; team++) {
        lines.clear();
        for (int dir = 0; dir < 4; dir++) {
            row = headPlayers[team].first + dirR[dir];
            col = headPlayers[team].second + dirC[dir];
            if (isInRange(row, col) &&
                (input[row][col] == TAIL || input[row][col] == LINE)) {
                break;
            }
        }
        headPlayers[team] = make_pair(row, col);
        findLines(lines, make_pair(row, col));
        if (input[row][col] == TAIL) {
            lines.push_back(make_pair(row, col));
        }

        int newValue;
        if ((lines.front().first == lines.back().first) &&
            (lines.front().second == lines.back().second)) {
            input[lines.front().first][lines.front().second] = HEAD;
            for (int loc = 1; loc < lines.size() - 1; loc++) {
                input[lines[loc].first][lines[loc].second] = PLAYER;
            }
            input[lines[lines.size() - 2].first]
                 [lines[lines.size() - 2].second] = TAIL;
        } else {
            for (int loc = 1; loc < lines.size(); loc++) {
                newValue = input[lines[loc].first][lines[loc].second];
                input[lines[loc].first][lines[loc].second] = LINE;
                input[lines[loc - 1].first][lines[loc - 1].second] = newValue;
            }
        }
    }
}

bool isInRange(int row, int col) {
    return ((1 <= row && row <= n) && (1 <= col && col <= n));
}

/// debug /////////////////////

void debug() {
    printf("\n");
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            printf("%-6d", input[r][c]);
        }
        printf("\n");
    }
}