// 예시 답안
#include <iostream>
using namespace std;

const int MAX = 1004;
int S[MAX][MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        S[y1][x1]++;
        S[y1][x2]--;
        S[y2][x1]--;
        S[y2][x2]++;
    }
    for (int i = 0; i < MAX; ++i)
        for (int j = 1; j < MAX; ++j)
            S[i][j] += S[i][j - 1];
    for (int j = 0; j < MAX; ++j)
        for (int i = 1; i < MAX; ++i)
            S[i][j] += S[i - 1][j];
    int ans = 0;
    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            if (S[i][j] == K)
                ans++;
    cout << ans;
    return 0;
}