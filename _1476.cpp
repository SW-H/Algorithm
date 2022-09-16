#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int E, S, M;
    cin >> E >> S >> M;

    int year;
    if (E == M && M == S) {
        cout << E;
    } 
    else { 
        for (int i = 0;; i++) {
            int tmp = 28 * i + S;
            if ((tmp - M) % 19 == 0 && (tmp - E) % 15 == 0) {
                cout << tmp;
                break;
            }
        }
    }
}