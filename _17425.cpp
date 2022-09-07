#include <iostream>
using namespace std;
#define MAX 1000000

long long f[MAX + 1];
long long g[MAX + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fill_n(f, MAX + 1, 1);
    for (int i = 2; i <= MAX; i++) {
        for (int j = 1; i * j <= MAX; j++) {
            f[i * j] += i;
        }
    }
    g[1] = f[1];
    for (int i = 2; i <= MAX; i++) {
        g[i] = g[i - 1] + f[i];
    }

    int testSize;
    int n;
    cin >> testSize;

    for (int i = 0; i < testSize; i++) {
        cin >> n;
        cout << g[n] << endl;
    }
}