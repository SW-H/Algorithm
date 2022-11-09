#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define STATES 8

int wheelCnt, rotation, target, direction;
string tmp;
vector<vector<int> > wheels(1001, vector<int>(STATES));
int rotationDir[1001];
void input();
void solve();
void shiftClockwise(vector<int>& arr, int shift);
void shiftCounterClock(vector<int>& arr, int shift);
void rotate(int *direction);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();
    solve();
    int res = 0;
    for (int i = 1; i <= wheelCnt; i++) {
        if (wheels[i][0] == 1) {
            res++;
        }
    }
    cout << res;
}

void input() {
    cin >> wheelCnt;
    for (int i = 1; i <= wheelCnt; i++) {

        cin >> tmp;
        for (int state = 0; state < STATES; state++) {
            wheels[i][state] = (tmp[state] - '0');
        }
    }
    cin >> rotation;
}

void solve() { // direction) 1 = 시계, -1=반시계
    int state = wheels[target][6];

    for (int r = 0; r < rotation; r++) {
        fill_n(rotationDir, 1001, 0);
        cin >> target >> direction;
        state = wheels[target][6];
        rotationDir[target] = direction;
        for (int i = target - 1; i >= 1; i--) {
            if (i > 0 && state != wheels[i][2]) {
                rotationDir[i] = rotationDir[i + 1] * -1;
                state = wheels[i][6];
            }
        }
        state = wheels[target][2];
        for (int i = target + 1; i <= wheelCnt; i++) {
            if (i <= wheelCnt && state != wheels[i][6]) {
                rotationDir[i] = rotationDir[i - 1] * -1;
                state = wheels[i][2];
            }
        }
        rotate(rotationDir);
    }
}

void rotate(int *direction) {
    for (int i = 1; i <= wheelCnt; i++) {
        if (direction[i] == 1) {
            shiftClockwise(wheels[i], 1);
        } else if (direction[i] == -1) {
            shiftCounterClock(wheels[i], 1);
        }
    }
}

void shiftClockwise(vector<int>& arr, int shift) {
    reverse(arr.begin(), arr.begin() + STATES - shift);
    reverse(arr.begin() + STATES - shift, arr.end());
    reverse(arr.begin(), arr.end());
}

void shiftCounterClock(vector<int>& arr, int shift) {
    reverse(arr.begin(), arr.begin() + shift);
    reverse(arr.begin() + shift, arr.end());
    reverse(arr.begin(), arr.end());
}