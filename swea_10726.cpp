#include <iostream>
#include <string>
using namespace std;
#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

int main() {
    INIT int T, N, M;
    string test = "";
    for (int i = 0; i < 30; i++) {
        test += "1";
    }
    cin >> T;
    bool isTurned;
    for (int t = 1; t <= T; t++) {
        isTurned = true;
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
            if (M % 2 == 0) {
                isTurned = false;
                break;
            }
            M /= 2;
        }
        if (isTurned) {
            cout << "#" << t << " ON\n";
        } else {
            cout << "#" << t << " OFF\n";
        }
    }
}