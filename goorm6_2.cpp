#include <iostream>
#define ALPHA_CNT 26
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int len;
    string code;
    cin >> len;
    cin >> code;
    for (int i = 0; i < len; i += 2) {
        int cnt = code[i + 1] - '0';
        cnt = (cnt * cnt) % ALPHA_CNT;
        cout << (char)('a' + (code[i] - 'a' + cnt) % ALPHA_CNT);
    }
}
