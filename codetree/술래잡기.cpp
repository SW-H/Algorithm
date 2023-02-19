// 플레이중에는 도망자들끼리 위치 겹칠 수 있음

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// methods
void calcCatcherRoutes(pair<int, int> start);
void calcReversed(pair<int, int> start);
void debug();
void moveRunners();
//

int people[100][100];
int tree[100][100];

int ID = 0;
int dr[] = {-1, 0, 1, 0}; // 상, 우, 하, 좌
int dc[] = {0, 1, 0, -1};

enum DTYPE { LR = 1, UD }; // 상하.좌우
enum LRUD { U, R, D, L };

class Person {
  public:
    pair<int, int> loc;
    int dType;
    int d;
    int id;

    Person(pair<int, int> loc, int dType) {
        this->loc = loc;
        this->id = ID++;
        this->dType = dType;
        d = 0;
    }
};

vector<Person> runners; // 도망자 : ID 1~
vector<pair<int, int> /**/> catcherRoutes;
int n, m, h, k; // n:격자크기, m : 도망자명수, h : 나무 개수, k: 라운드
Person catcher(make_pair(n / 2 + 1, n / 2 + 1), -1); // 술래 : ID 0

int main() {
    cin >> n >> m >> h >> k;

    int row, col, d;
    for (int i = 1; i <= m; i++) {
        // 도망자위치, 이동방법 d - 좌우(1)1,3, 상하(2)0,2
        cin >> row >> col >> d;
        runners[i] = (Person(make_pair(row, col), d));
        people[row][col] = runners[i].id;
    }

    for (int i = 1; i <= h; i++) { // 나무
        cin >> row >> col;
        tree[row][col] = 1;
    }
    int score = 0;
    calcCatcherRoutes(catcher.loc);
    for (int round = 1; round <= k; round++) {
        moveRunners(); // 도망자
        debug();
        // moveCatcher(); // 술래
        // score += calcScore();
    }
    // cout << score;
}

void moveRunners() {
    int nr, nc;
    int d; // 상우하좌
    for (int p = 1; p <= m; p++) {
        d = runners[p].dType + runners[p].d * 2;
        // 이동할 위치
        nr = runners[p].loc.first + dr[d];
        nc = runners[p].loc.second + dc[d];

        if (nr <= 0 || nr > n || nc <= 0 || nc > n) { // 격자를 벗어난 경우
            runners[p].d = (d + 1) % 2;
            d = runners[p].dType + runners[p].d * 2;
        }
        if (!(nr == catcher.loc.first &&
              nc == catcher.loc.second)) { // 술래 없음
            people[runners[p].loc.first][runners[p].loc.second] = 0;
            // people[nr][nc] = runners[p].id;
            // runners[p].loc = make_pair(nr, nc);
            // runners[p].d = (d + 1) % 2;
        }
    }
}

void calcCatcherRoutes(pair<int, int> start) {
    int d = 0, cnt = 1;
    pair<int, int> loc = start;

    while (true) {
        for (int i = 0; i < 2; i++) {
            for (int rep = 1; rep <= cnt; rep++) {
                int nr = loc.first + dr[d];
                int nc = loc.second + dc[d];
                catcherRoutes.push_back(make_pair(nr, nc));
                loc = catcherRoutes.back();
                if (nr <= 0 || nr > n || nc <= 0 || nc > n ||
                    (nr == 1 && nc == 1)) {
                    return calcReversed(start);
                }
            }
            d = (d + 1) % 4;
        }
        cnt++;
    }
}

void calcReversed(pair<int, int> start) {
    for (int i = catcherRoutes.size() - 2; i >= 0; i--) {
        catcherRoutes.push_back(catcherRoutes[i]);
    }
    catcherRoutes.push_back(start);
}

void debug() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%-6d ", people[i][j]);
        }
        printf("\n");
    }
}