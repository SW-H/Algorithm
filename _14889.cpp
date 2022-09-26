#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int S[21][21];
int allStat;
int calcOpposite(vector<int> members);
int calcSum(int sum, int added, vector<int> members);
int solve(int sum, int added, vector<int> members);

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> S[i][j];
            allStat += S[i][j];
        }
    }
    vector<int> mem;
    int res = allStat, tmp;
    for (int i = 1; i <= N; i++) {
        if (res > (tmp = solve(0, i, mem))) {
            res = tmp;
        }
    }
    cout << res;
}

int solve(int sum, int added, vector<int> members) {

    if (added == N + 1 || members.size() == (N / 2)) {
        if (members.size() == (N / 2)) {
            return abs(sum - calcOpposite(members));
        } else {
            return allStat;
        }
    }
    vector<int> tmp(members);
    tmp.push_back(added);
    return min(solve(calcSum(sum, added, members), added + 1, tmp),
               solve(sum, added + 1, members));
}

int calcSum(int sum, int added, vector<int> members) {
    if (!members.empty()) {
        for (int member : members) {
            sum += S[added][member];
            sum += S[member][added];
        }
    }
    return sum;
}

int calcOpposite(vector<int> members) {
    vector<int> oppositeTeam;
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        if (find(members.begin(), members.end(), i) == members.end()) {
            sum = calcSum(sum, i, oppositeTeam);
            oppositeTeam.push_back(i);
        }
    }
    return sum;
}
