// 정답 코드

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define INITIAL_SETTING                                                        \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

string N;
int x, y;
void solve();

int main() {
    INITIAL_SETTING
    int testCase;
    cin >> testCase;

    for (int t = 0; t < testCase; t++) {
        cin >> N >> x >> y;
        cout << "#" << t + 1 << " ";
        solve();
        cout << "\n";
    }
}

void solve() {
    if (N.length() == 1 && x > N[0] - '0' && y > N[0] - '0') {
        cout << "-1";
        return;
    }
    string target;
    for (int i = 0; i < N.length(); i++) {
        target += ('0' + y);
    }
    vector<int> sequence;
    sequence.push_back(0);
    sequence.push_back(x);
    sequence.push_back(y);
    sort(sequence.begin(), sequence.end());

    for (int place = 0; place < N.length(); place++) {
        for (int i = 2; i >= 0; i--) {
            if (sequence[i] > (N[place] - '0')) {
                continue;
            } else if (sequence[i] < N[place] - '0') {
                target[place] = '0' + sequence[i];
                if (place + 1 < N.length()) {
                    place = N.length();
                }
                break;
            } else {
                target[place] = '0' + sequence[i];
                break;
            }
        }
    }
    int pos;
    for (int i = 0; i < target.length(); i++) {
        if (target[i] == '0' && x != 0) {
            for (int c = max(i - 1, 0); c >= 0; c--) {
                if (target[c] - '0' > x) {
                    target[c] = '0' + x; // 수정완
                    for (int r = c + 1; r < target.length(); r++) {
                        target[r] = '0' + y;
                    }
                    cout << target;
                    return;
                }
            }
            for (int i = 0; i < N.length() - 1; i++) {
                cout << y;
            }
            return;
        }
    }
    if (target[0] == '0') {
        if ((pos = target.find_first_not_of("0")) == string::npos) {
            cout << "-1";
            return;
        } else {
            for (int i = 0; i < N.length() - 1; i++) {
                cout << y;
            }
            return;
        }
    } else {
        cout << target;
    }
}
