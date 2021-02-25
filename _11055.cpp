#include <cstdio>


int main(){
    int N,seq[1000],accumSum[1000]={0};
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&seq[i]);
    }
    accumSum[0]=seq[0];
    
    for(int i=0;i<N;i++){
        accumSum[i]=seq[i];
            // printf("accumSum[%d]:%d\n",i,accumSum[i]);
        for(int j=0;j<N;j++){
            // printf("5%d\n",accumSum[j]+seq[i]);
            if(seq[j]<seq[i] && accumSum[i]<seq[i]+accumSum[j]){
                accumSum[i]=seq[i]+accumSum[j];
            }
        }
    }
    int maxSum=0;
    for(int i=0;i<N;i++){
        if(maxSum<accumSum[i]){
            maxSum=accumSum[i];
        }
    }
    
    printf("%d\n",maxSum);

}

