#include <cstdio>
#include <iostream>
#include <algorithm> //max
using namespace std; //max
int max(int a, int b, int c);
int main(){
    int T, n,res;
    scanf("%d",&T);
    
    for(int i=0;i<T;i++){
        res = 0;
        scanf("%d",&n);
        int D[n+1][3];
        int stickers[2][n+1];

        for(int i=0;i<2;i++){
            for(int j=0;j<n;j++){
                scanf("%d", &stickers[i][j]);
            }
        }

        D[0][0]=0;
        D[0][1]= stickers[0][0];
        D[0][2]= stickers[1][0];
        
        for(int i=1;i<=n;i++){ // D[i][j] = 2 * i 에서 얻을 수 있는 최대 점수, i번 열에서 뜯는 스티커는 j
            D[i][0] = max(D[i-1][0],D[i-1][1],D[i-1][2]);
            D[i][1] = max(D[i-1][0],D[i-1][2])+stickers[0][i];
            D[i][2] = max(D[i-1][0],D[i-1][1])+stickers[1][i];
        }        
        printf("%d\n",D[n][0]);
    
    }
}
int max(int a, int b, int c){
    return max(max(a,b),c);
}
