#include <cmath>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skills) {
    int result[1005][1005];
    int degree;
    for (auto skill : skills) {
        degree = pow(-1.0, skill[0]) * skill[5];
        result[skill[1]][skill[2]] += degree;
        result[skill[3] + 1][skill[4] + 1] += degree;
        result[skill[3] + 1][skill[2]] += -degree;
        result[skill[1]][skill[4] + 1] += -degree;
    }
    for (int i = 0; i < board.size(); i++) {
        for (int j = 1; j < board[0].size(); j++) {
            result[i][j] += result[i][j - 1];
        }
    }
    for (int j = 0; j < board[0].size(); j++) {
        for (int i = 1; i < board.size(); i++) {
            result[i][j] += result[i - 1][j];
        }
    }
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            board[i][j] += result[i][j];
        }
    }

    int count = 0;
    for (auto eachRow : board) {
        for (auto r : eachRow) {
            if (r > 0) {
                count++;
            }
        }
    }
    return count;
}

//  https://kimjingo.tistory.com/155
