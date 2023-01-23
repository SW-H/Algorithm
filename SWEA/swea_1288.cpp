// 새로운 불면증 치료법

#include <iostream>
#include <string>

using namespace std;

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);

bool check[10];

bool allChecked();

int main() {
    INIT int T, N;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> N;
        fill_n(check, 10, false);
        for (int times = 1;; times++) {
            string tmp = to_string(N * times);
            for (int plc = 0; plc < tmp.length(); plc++) {
                check[tmp[plc] - '0'] = true;
            }
            if (allChecked()) {
                cout << "#" << t << " " << tmp << "\n";
                break;
            }
        }
    }
}

bool allChecked() {
    for (int i = 0; i < 10; i++) {
        if (check[i] == false) {
            return false;
        }
    }
    return true;
}

