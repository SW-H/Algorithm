#include <iostream>
using namespace std;

/* 시간 초과
int main() {
    int N, count, sum = 0;
    cin >> N;
    for(int divisor = 1; divisor <= N ; divisor++){
        count = 0;
        for (int n = 1; n <= N; n++) {
            if(n % divisor == 0){
                count++;
            }
        }
        sum += divisor * count;
    }

    cout << sum;
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    long long sum = 0;
    cin >> N;

    for (int divisor = 1; divisor <= N; divisor++) {
        sum += (divisor * (N / divisor));
    }

    cout << sum;
}