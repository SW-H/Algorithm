#include <cstdio>

bool isViewed(int* building_heights, int idx);
int setInput(int* building_heights);
void printSol(int idx, int res);
int solve(int testCaseCnt, int* building_heights);
void clearArr(int* arr);

int main() {
    int building_heights[1001];
    int testCaseCnt;
    for (int i = 0; i < 10; i++) {
        testCaseCnt = setInput(building_heights);
        printSol(i + 1, solve(testCaseCnt, building_heights));
        clearArr(building_heights);
    }
    return 0;
}

int setInput(int* building_heights) {
    int testCaseCnt;
    scanf("%d", &testCaseCnt);
    for (int i = 0; i < testCaseCnt; i++) {
        scanf("%d", &building_heights[i]);
    }
    return testCaseCnt;
}

void printSol(int idx, int res) {
    printf("#%d %d\n", idx, res);
}

int solve(int testCaseCnt, int* building_heights) {
    int res = 0;
    for (int i = 2; i < testCaseCnt - 2; i++) {
        while (isViewed(building_heights, i)) {
            res++;
            building_heights[i]--;
        }
    }
    return res;
}

bool isViewed(int* building_heights, int idx) {
    for (int i = idx - 2; i <= idx + 2; i++) {
        if (i!=idx && building_heights[i] >= building_heights[idx]) {
            return false;
        }
    }
    return true;
}

void clearArr(int* arr) {
    for (int i = 0; i < 1001; i++) {
        arr[i] = 0;
    }
}
