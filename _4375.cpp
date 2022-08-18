#include <iostream>
using namespace std;

int main() {
    int n;
    int res;
    while (cin >> n) {
        long target = 1;
        res = 1;
        while (1) {
            // (A+B)%C = ((A%C) + (B%C))%C
            // X % C = (X % C) % C
            // target %= n;
            target = target % n;
            if (target == 0) {
                break;
            }
            target = (target * 10) % n + (1 % n);
            res++;
        }
        cout << res << endl;
    }
}