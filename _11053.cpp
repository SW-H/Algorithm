#include <cstdio>

int main(){
    int N,max=1,temp=1;
    int seq[1001]={0};
    int res[1001]={0};
    
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&seq[i]);
        res[i]=1;
    }
    
    for(int i=1;i<N;i++){
        temp=1;
        for(int j=i-1;j>=0;j--){
            if(seq[j]<seq[i] && res[j]+1>=temp){
                temp = res[j]+1;  
                res[i] = temp;
            }
        }
    }
    for(int i=0;i<N;i++){
        // printf("%3d",res[i]);
        if(max<res[i]){
            max = res[i];
        }
    }
    printf("%d\n",max);
}