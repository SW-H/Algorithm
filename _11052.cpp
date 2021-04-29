#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    int N;
    cin>>N;
    
    int costs[2*N];
    int res[2*N];

    for (int i=0; i<N+1; i++){
        costs[i]=res[i]=0;
    }
    for (int i=1; i<N+1; i++){
        cin>>costs[i];
    }

    for(int i=1; i<N+1; i++){
        for(int j=1; j<i+1; j++){
            res[i] = max( res[i], res[i-j] + costs[j] );
        }    
    }
    
    cout << res[N];

    
}