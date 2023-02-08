// priority queue

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef struct _Player {
    pair<int, int> location;
    int direction;
    int initialPower;
    int gun;
} Player;

int point[401];
vector<int> gunMap[21][21];
int playerMap[21][21];
Player players[401];

vector<pair<int, int> /**/> moveTo;

int n, m, k;

int main() {
    cin >> n >> m >> k;
    moveTo.push_back(make_pair(-1, 0));
    moveTo.push_back(make_pair(0, 1));
    moveTo.push_back(make_pair(1, 0));
    moveTo.push_back(make_pair(0, -1));
    int gun;
    for (int i = 0; i < n; i++) {
        gunMap[i]->clear();
        for (int j = 0; j < n; j++) {
            cin >> gun;
            if (gun > 0) {
                gunMap[i][j].push_back(gun);
            }
        }
    }
    for (int player = 1; player <= m; player++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        playerMap[x][y] = player;
        players[player].location = make_pair(x, y);
        players[player].direction = d;
        players[player].initialPower = s;
        players[player].gun = 0;
    }
    for (int round = 1; round <= k; round++) {
        memset(point, 0, sizeof(point));
        for (int player = 1; player <= m; player++) {
            // 이동
            pair<int, int> to;
            to.first = players[player].location.first +
                       moveTo[players[player].direction].first;
            to.second = players[player].location.second +
                        moveTo[players[player].direction].second;
            if (to.first <= 0 || to.first > n || to.second <= 0 ||
                to.second > n) {
                to.first = players[player].location.first +
                           moveTo[(players[player].direction + 2) % 4].first;
                to.second = players[player].location.second +
                            moveTo[(players[player].direction + 2) % 4].second;

                players[player].direction = (players[player].direction + 2) % 4; //!           
            }
            playerMap[players[player].location.first]
                     [players[player].location.second] = 0;

            // cout << players[player].location.first << " "
            //      << players[player].location.second << "\n";

            // 플레이어 없다면 총 확인
            int gunMaxPoint;
            if (playerMap[to.first][to.second] == 0) {
                if (!(gunMap[to.first][to.second].empty())) {
                    vector<int>::iterator maxGun =
                        max_element(gunMap[to.first][to.second].begin(),
                                    gunMap[to.first][to.second].end());
                    if (players[player].gun > *maxGun) {
                        gunMap[to.first][to.second].push_back(
                            players[player].gun);
                        players[player].gun = *maxGun;
                        gunMap[to.first][to.second].erase(maxGun);
                    }
                }
            } else { // 플레이어 있다면 싸움
                int winner, loser;
                // player vs opponent
                int opponent = playerMap[to.first][to.second];
                if ((players[player].initialPower + players[player].gun >
                     players[opponent].initialPower + players[opponent].gun) ||
                    ((players[player].initialPower + players[player].gun ==
                      players[opponent].initialPower + players[opponent].gun) &&
                     (players[player].initialPower >
                      players[opponent].initialPower))) { // 승자 : player
                    winner = player;
                    loser = opponent;
                } else {
                    winner = opponent;
                    loser = player;
                }
                // 포인트 획득
                point[winner] +=
                    (players[winner].initialPower + players[winner].gun -
                     players[loser].initialPower + players[loser].gun);

                // 패자 이동
                if (players[loser].gun > 0) {
                    gunMap[to.first][to.second].push_back(players[loser].gun);
                }
                players[loser].gun = 0;
                for (int cnt = 0; cnt < 4; cnt++) {
                    int dir = (dir + 1) % 4;
                    if (to.first + moveTo[dir].first <= 0 ||
                        to.first + moveTo[dir].first > n ||
                        to.second + moveTo[dir].second <= 0 ||
                        to.second + moveTo[dir].second > n ||
                        playerMap[to.first + moveTo[dir].first][to.second] >
                            0) {
                        continue;
                    } else {
                        players[loser].location.first =
                            to.first + moveTo[dir].first;
                        players[loser].location.second =
                            to.second + moveTo[dir].second;
                        break;
                    }
                }
                // 총 줍기
                pair<int, int> loserLocation = players[loser].location;
                if (!(gunMap[loserLocation.first][loserLocation.second]
                          .empty())) {
                    vector<int>::iterator maxGun = max_element(
                        gunMap[loserLocation.first][loserLocation.second]
                            .begin(),
                        gunMap[loserLocation.first][loserLocation.second]
                            .end());
                    if (players[loser].gun > *maxGun) {
                        gunMap[to.first][to.second].push_back(
                            players[player].gun);
                        players[loser].gun = *maxGun;
                        gunMap[loserLocation.first][loserLocation.second].erase(
                            maxGun);
                    }
                }

                // 승자 총줍기
                if (!(gunMap[to.first][to.second].empty())) {
                    vector<int>::iterator maxGun =
                        max_element(gunMap[to.first][to.second].begin(),
                                    gunMap[to.first][to.second].end());
                    if (players[player].gun > *maxGun) {
                        gunMap[to.first][to.second].push_back(
                            players[player].gun);
                        players[player].gun = *maxGun;
                        gunMap[to.first][to.second].erase(maxGun);
                    }
                }
            }
            // 이동
            playerMap[to.first][to.second] = player;
            players[player].location = to;
            cout << player << ":" << players[player].location.first << " "
                 << players[player].location.second << "\n";
        }
        for (int res = 1; res <= m; res++) {
            // cout << "player " << res << " :(" << players[res].location.first
            // << ", "
            //      << players[res].location.second << ") "
            //      << players[res].initialPower << " " << players[res].gun <<
            //      "\n";
            cout << point[res] << " ";
        }
    }
}
