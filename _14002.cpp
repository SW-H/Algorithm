#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

int main(){
    int N, max=0,temp=1,maxIDX=0;
    int seq[1000], res[1000], history[1000];
    stack<int> ans;
    
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&seq[i]);
        res[i]=1;
        history[i]=-1; // 0으로 초기화를 하거나 초기화를 하지 않으면 메모리 초과/seg error가 뜬다 .. 이유를 모르겠음
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<i;j++){
            if(seq[j]<seq[i] && res[i]<=res[j]+1){
                history[i] = j;
                res[i] = res[j]+1;
            }
        }
    }
    
    
    
    for(int i=0;i<N;i++){
        if(res[i]>max){
            max=res[i];
            maxIDX=i; 
        }

    }
    printf("%d\n",max);
    int tempIDX=0;
    while(maxIDX>=0){
        ans.push(seq[maxIDX]);
        maxIDX = history[maxIDX];
    }
    
    for(int i=0;i<max;i++){
        printf("%d\n",ans.top());
        ans.pop();        
    }

}

