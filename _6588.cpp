/*
#include <cstdio>
bool isPrime(int target);

int main(){
    int n,a,b;
    bool res;
    while(1){
        res = false;
        scanf("%d",&n);
        if (n==0){
            return 0;
        }
        else{
            for(int i=1;i<n;i++){
                if (isPrime(i) && isPrime(n-i)){
                    // printf("%d = %d + %d\n",n,i,n-i);
                    res = true;
                    a = i;
                    b= n-i;
                    break;
                }
            }
            if(res){
                printf("%d = %d + %d\n",n,a,b);
            }
            else{
                printf("Goldbach's conjecture is wrong.");
            }

        }
    }
}



bool isPrime(int target){
    if(target==1){
        return false;
    }
    for(int i=2;i*i<=target;i++){
        if (target%i==0){
            return false;
        }
    }
    return true;
}
*/

#include <iostream>
using namespace std;
void solve(int n);
void initialize();
#define MAX 1000000

bool isPrime[MAX + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    initialize();

    while (1) {
        cin >> n;
        if (n == 0) {
            return 0;
        }
        solve(n);
    }
}

void solve(int n) {
    int i = 1, j = max(n - 1, 1);
    while (0 < i && i <= j && j < n) {
        if (isPrime[i] && isPrime[j] && i + j == n) {
            cout << n << " = " << i << " + " << j << "\n";
            return;
        }
        i += 2;
        j -= 2;
    }
    cout << "Goldbach's conjecture is wrong.\n";
}

void initialize() {
    fill_n(isPrime, MAX + 1, true);
    isPrime[1] = false;
    for (int i = 2; i <= MAX; i++) {
        for (int j = 2; i * j <= MAX; j++) {
            isPrime[i * j] = false;
        }
    }
}
