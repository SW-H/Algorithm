// 오답 코드

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define INITIAL_SETTING                                                        \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
int x, y;
string N, gift;

void solve();
bool isDone();
bool checkZero();
int main() {
    INITIAL_SETTING
    int testCase;
    cin >> testCase;

    for (int t = 0; t < testCase; t++) {
        cin >> N >> x >> y;
        for (int cnt = 0; cnt < N.length(); cnt++) {
            gift += ('0' + y);
        }
        cout << "#" << t + 1 << " ";
        if (!isDone()) {
            solve();
        } else {
            cout << gift << "\n";
        }
        gift.clear();
    }
}

void solve() {
    for (int plc = 0; plc < N.length(); plc++) {
        if (gift[plc] > N[plc]) {
            for (int target = plc; target >= 0; target--) {
                if (gift[target] == ('0' + y)) {
                    gift[target] = ('0' + x);
                    if (isDone() && checkZero()) {
                        cout << gift << "\n";
                        return;
                    } else {
                        gift[target] = ('0' + y);
                    }
                }
            }
        }
    }

    if (N.length() == 1 || !checkZero()) {
        cout << "-1\n";
        return;
    } else {
        for (int cnt = 0; cnt < N.length() - 1; cnt++) {
            cout << y;
        }
        cout <<"\n";
    }
}
bool checkZero(){
    for(int i=0;i<gift.length();i++){
        if(gift[i] != '0'){
            return true;
        }
    }
    return false;
}

bool isDone() {
    for (int plc = 0; plc < N.length(); plc++) {
        if ((gift[plc] - '0') > (N[plc] - '0')) {
            return false;
        } else if (((gift[plc] - '0') < (N[plc] - '0'))) {
            return true;
        }
    }
    return true;
}