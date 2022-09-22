#include <iostream>
#include <algorithm> //count, max_element
using namespace std;

int accumSum[501]; // 스테이지별 인원 누적합
double failureRate[501];

vector<int> solution(int N, vector<int> stages) {
    for(int i = 1; i <= N; i ++){
        accumSum[i] = count(stages.begin(), stages.end(), i) + accumSum[i-1];
    }
    int onStage; // 스테이지에 도달한 플레이어 수
    for(int i = 1; i <= N; i ++){
        onStage = stages.size() - accumSum[i-1];
        if(onStage != 0){
            failureRate[i] = (double)(accumSum[i] - accumSum[i-1]) / onStage;
        }
    }
    vector<int> res;
    int tmp;
    for(int i = 1; i <= N; i++){
        tmp = (max_element(failureRate + 1, failureRate + N + 1) - failureRate);
        res.push_back(tmp);
        failureRate[tmp] = -1;
    }
    return res;
}

