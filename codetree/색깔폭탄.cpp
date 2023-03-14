#include <deque>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#define DIR_NUM 4
#define RED 0
#define BLK -1
#define MAX 444

int n, score, bombCnt; // bombCnt : 폭탄 종류 총 개수
int map[20][20];
// 상하좌우
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

vector<pair<int, int> /**/> bfs(pair<int, int> point, int color);
bool isInRange(pair<int, int> point);
vector<pair<int, int> /**/> findBombPacks();
int countRed(vector<pair<int, int> /**/> packs);
void debug();
void gravity();
int removeBombs(vector<pair<int, int> /**/> bombPacks);
void rotate();
bool validate(vector<pair<int, int> /**/> pack);

int main() {

    // input
    cin >> n >> bombCnt;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> map[r][c];
        }
    }
    // 터질 폭탄묶음이 없을 때까지
    while (true) {
        // 1. 가장 큰 폭탄 묶음 찾기
        vector<pair<int, int> /**/> bombPacks = findBombPacks();
        // cout << bombPacks.size() << "\n";
        if(bombPacks.size() < 2){
            break;
        }
        
        // 2. 폭탄 제거 - 점수 획득
        score += removeBombs(bombPacks);
        // 3. 중력작용(돌:x)
        gravity();
        // 4. 반시계 회전
        rotate();
        // 5. 중력작용(돌:x)
        gravity();
    }
    cout << score << "\n";
}

void rotate() {
    // (r,c) -> (n-c ,r)
    int newMap[20][20] = {};
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            newMap[r][c] = map[c][n - r - 1];
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            map[r][c] = newMap[r][c];
        }
    }
}

void gravity() {
    for (int c = 0; c < n; c++) {
        for (int r = n - 1; r >= 0; r--) {
            if ((map[r][c] == MAX) || (map[r][c] == BLK)) {
                continue;
            }
            int newR;
            for (newR = r; newR < n - 1; newR++) {
                if (map[newR + 1][c] < MAX) {
                    break;
                }
            }
            if (newR > r) {
                map[newR][c] = map[r][c];
                map[r][c] = MAX;
            }
        }
    }
}

int removeBombs(vector<pair<int, int> /**/> bombPacks) {
    int ret = 0;
    for (auto bomb : bombPacks) {
        map[bomb.first][bomb.second] = MAX; // 빈 공간 : MAX대입
        ret++;
    }
    return ret * ret;
}

vector<pair<int, int> /**/> findBombPacks() {
    vector<pair<int, int> /**/> ret;

    for (int r = 0; r < n; r++) {
        for (int c = n - 1; c >= 0; c--) { // 기준점 좌표
            if (map[r][c] == RED || map[r][c] == BLK || map[r][c] == MAX ) {
                continue;
            }
            vector<pair<int, int> /**/> tmp = bfs(make_pair(r, c), map[r][c]);
            if ((ret.size() < tmp.size()) ||
                ((ret.size() == tmp.size()) &&
                 (countRed(tmp) <= countRed(ret))) && validate(tmp)) {
                ret = tmp;
            }
        }
    }
    return ret;
}

bool validate(vector<pair<int, int> /**/> pack){
    if(pack.size() < 2){
        return false;
    }
    for(auto bomb : pack){
        if(map[bomb.first][bomb.second] != RED){
            return true;
        }
    }
    return false;
}

int countRed(vector<pair<int, int> /**/> packs) {
    int count = 0;
    if (packs.empty()) {
        return MAX;
    }
    for (auto bomb : packs) {
        if (map[bomb.first][bomb.second] == RED) {
            count++;
        }
    }
    return count;
}

vector<pair<int, int> /**/> bfs(pair<int, int> point, int color) {
    int nr, nc;
    bool visited[25][25] = {0};
    vector<pair<int, int> /**/> res;
    deque<pair<int, int> /**/> queue;

    queue.push_back(point);
    visited[point.first][point.second] = true;
    while (!queue.empty()) {
        nr = queue.front().first;
        nc = queue.front().second;
        res.push_back(make_pair(nr, nc));
        queue.pop_front();
        for (int d = 0; d < DIR_NUM; d++) {
            if (isInRange(make_pair(nr + dr[d], nc + dc[d])) &&
                (!visited[nr + dr[d]][nc + dc[d]]) &&
                ((map[nr + dr[d]][nc + dc[d]] == RED) ||
                 (map[nr + dr[d]][nc + dc[d]] == color))) {
                queue.push_back(make_pair(nr + dr[d], nc + dc[d]));
                visited[nr + dr[d]][nc + dc[d]] = true;
            }
        }
    }
    return res;
}

bool isInRange(pair<int, int> point) {
    return ((0 <= point.first) && (point.first < n) && (0 <= point.second) &&
            (point.second < n));
}

void debug() {
    printf("\n");
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%-5d", map[r][c]);
        }
        printf("\n");
    }
}