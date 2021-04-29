#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int zeroCnt(int n);
int cntFive(int n);

int main() {
    int N, res = 0;
    scanf("%d", &N);
    printf("%d", zeroCnt(N));
}

// 팩토리얼을 구해서 하면 자료형에 안담겨서 마이너스가 됨!
// 그래서 곱해지는 숫자들 안에 5의 개수(2*5 가 10 이 되는데 항상 5의 개수가 적기 때문에 5의 개수만 세면 됨)를 세줌
// ex) 100 팩토리얼이라면 1~100 각각 소인수 분해했을 때 5의 개수



int zeroCnt(int n) {
    int res = 0;

    for (int i = 1; i <= n; i++) {
        res += cntFive(i);
    }
    return res;
}

int cntFive(int N) {
    vector<int> primes;
    int cntFive=0;
    for (int i = 2; i * i <= N; i++) { 
        while (N % i == 0) { 
            primes.push_back(i);
            N /= i;
        }
    }
    if (N > 1) {
        primes.push_back(N);
    }

    for (vector<int>::iterator i = primes.begin() ; i != primes.end(); ++i){
        if(*i == 5 ){
            cntFive++;
        }
    }
    return cntFive;
}