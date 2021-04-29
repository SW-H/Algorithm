#include <cstdio>
bool solution(int target);
int main(){
    int N,target,cnt;
    scanf("%d",&N);
    cnt=0;
    for(int i=0;i<N;i++){
        scanf("%d",&target);
        if(solution(target)){
            cnt++;
        }
    }
    printf("%d",cnt);
}

bool solution(int target){
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