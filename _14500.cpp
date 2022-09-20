#include <iostream>
using namespace std;

int paper[502][502];
int N, M;
int solve();
int calcCase1();
int calcCase2();
int calcCase3();
int calcCase4();
int calcCase5();
int maxAmong(int _1, int _2, int _3, int _4, int _5, int _6);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    /*
            M
        ㅡ ㅡ ㅡ ㅡ ㅡ
        |
    N   |
        |

    */
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> paper[i][j];
        }
    }

    cout << solve();
}

int solve() {
    int res = 0;
    int tmp;
    if ((tmp = calcCase1()) > res) {
        res = tmp;
    }
    if ((tmp = calcCase2()) > res) {
        res = tmp;
    }
    if ((tmp = calcCase3()) > res) {
        res = tmp;
    }

    if ((tmp = calcCase4()) > res) {
        res = tmp;
    }
    if ((tmp = calcCase5()) > res) {
        res = tmp;
    }
    return res;
}

int calcCase1() {
    /*
    ㅁㅁ
    ㅁㅁ
    */
    int res = 0;
    int sum = 0;
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 1; j <= M - 1; j++) {
            sum = (paper[i][j] + paper[i][j + 1] + paper[i + 1][j] +
                   paper[i + 1][j + 1]);
            if (sum > res) {
                res = sum;
            }
        }
    }
    return res;
}

int calcCase2() {
    /*

    ㅁ
    ㅁ
    ㅁ
    ㅁ,   ㅁㅁㅁㅁ

    */

    int res = 0;
    int sum = 0;
    for (int i = 1; i <= N; i++) { // ㅁㅁㅁㅁ
        for (int j = 1; j <= M - 3; j++) {
            sum = (paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                   paper[i][j + 3]);
            if (sum > res) {
                res = sum;
            }
        }
    }

    for (int i = 1; i <= N - 3; i++) {
        for (int j = 1; j <= M; j++) {
            sum = (paper[i][j] + paper[i + 1][j] + paper[i + 2][j] +
                   paper[i + 3][j]);
            if (sum > res) {
                res = sum;
            }
        }
    }

    return res;
}

int calcCase3() {
    int res = 0;
    int sum = 0;
    for (int i = 1; i <= N; i++) { // ㅁㅁㅁ + ㅁ
        for (int j = 1; j <= M - 2; j++) {
            sum = (paper[i][j] + paper[i][j + 1] + paper[i][j + 2] +
                   maxAmong(paper[i + 1][j], paper[i + 1][j + 1],
                            paper[i + 1][j + 2], paper[i - 1][j],
                            paper[i - 1][j + 1], paper[i - 1][j + 2]));
            if (sum > res) {
                res = sum;
            }
        }
    }
    return res;
}

int calcCase4() {
    int res = 0;
    int sum = 0;

    /*
        ㅁ
        ㅁ
        ㅁ
        ㅁ
        +
          ㅁ
    */

    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= M; j++) {
            sum = (paper[i][j] + paper[i + 1][j] + paper[i + 2][j] +
                   maxAmong(paper[i][j + 1], paper[i + 1][j + 1],
                            paper[i + 2][j + 1], paper[i][j - 1],
                            paper[i + 1][j - 1], paper[i + 2][j - 1]));
            if (sum > res) {
                res = sum;
            }
        }
    }
    return res;
}

int calcCase5() {
    /*
    ㅁ
    ㅁ ㅁ
      ㅁ
    */
    int res = 0;
    int sum = 0;
    for (int i = 1; i <= N - 2; i++) {
        for (int j = 1; j <= M - 1; j++) {
            sum = max(paper[i][j] + paper[i + 1][j] + paper[i + 1][j + 1] +
                          paper[i + 2][j + 1],
                      paper[i][j + 1] + paper[i + 1][j] + paper[i + 1][j + 1] +
                          paper[i + 2][j]);
            if (sum > res) {
                res = sum;
            }
        }
    }
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 1; j <= M - 2; j++) {
            sum = max(paper[i][j] + paper[i][j + 1] + paper[i + 1][j + 1] +
                          paper[i + 1][j + 2],
                      paper[i][j + 1] + paper[i][j + 2] + paper[i + 1][j] +
                          paper[i + 1][j + 1]);
            if (sum > res) {
                res = sum;
            }
        }
    }
    return res;
}

int maxAmong(int _1, int _2, int _3, int _4, int _5, int _6) {
    return max(max(max(max(max(_1, _2), _3), _4), _5), _6);
}