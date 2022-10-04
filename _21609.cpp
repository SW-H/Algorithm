#include <iostream>
#include <vector>
using namespace std;

int N, colorCnt;
vector<vector<int> > block(21, vector<int>(21));
int dx[]={1,0};
int dy[]={0,1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> colorCnt;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> block[i][j];
        }
    }
    int nx, ny, cnt = 0, score = 0;
    pair<int, int> res = make_pair(-1,-1);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (block[y][x] != -1) {
                for (int d = 0; d < 2; d++) {
                    nx = x + dx[d];
                    ny = y + dy[d];
                    if (nx >= N || ny >= N) {
                        continue;
                    }
                    if (block[y][x] == block[ny][nx]) {
                        if(res.first == -1 && res.second==-1){
                            res = make_pair(y,x);
                        }
                        if (block[ny][nx] == 0) {
                            score++;
                        }
                        cnt++;
                    }
                    else{
                        cnt = 0; score=0;
                        res.first = res.second = -1;
                    }
                }
            }
        }
    }
    cout << res.first << " " << res.second;
}