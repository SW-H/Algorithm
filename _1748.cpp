#include <cstring>
#include <iostream>
#include <math.h>
using namespace std;
long long len[11] = {0,      9,       90,       900,       9000, 90000,
                     900000, 9000000, 90000000, 900000000, 1};

int main() {
    int N;
    int res = 0;
    cin >> N;
    int Nlen = to_string(N).size();
    for (int i = 1; i <= Nlen - 1; i++) {
        res += (len[i] * i);
    }
    res += (Nlen * (N - pow(10.0, Nlen - 1) + 1));
    cout << res;
}