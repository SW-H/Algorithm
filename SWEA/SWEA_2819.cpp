#include <cstdio>
#include <set>
using namespace std;

#define SIZE 4
void makeNumRecursive(set<long long>& nums,
                      int num,
                      int idx_x,
                      int idx_y,
                      int grid[][SIZE],
                      int digit);
void printSol(int idx, int res);
void setInput(int grid[SIZE][SIZE]);
int solve(int grid[SIZE][SIZE]);

int main() {
    int T;
    int grid[SIZE][SIZE];
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        setInput(grid);
        printSol(i, solve(grid));
    }
}

int solve(int grid[SIZE][SIZE]) {
    set<long long> nums;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            makeNumRecursive(nums, 0, i, j, grid, 0);
        }
    }
    return nums.size();
}

void makeNumRecursive(set<long long>& nums,
                      int num,
                      int idx_x,
                      int idx_y,
                      int grid[][SIZE],
                      int digit) {
    if (digit > 7) {
        return;
    }
    if (digit == 7) {
        nums.insert(num);
    } else {
        if (idx_x - 1 >= 0) {
            makeNumRecursive(nums, num * 10 + grid[idx_x][idx_y], idx_x - 1,
                             idx_y, grid, digit + 1);
        }
        if (idx_x + 1 < SIZE) {
            makeNumRecursive(nums, num * 10 + grid[idx_x][idx_y], idx_x + 1,
                             idx_y, grid, digit + 1);
        }
        if (idx_y - 1 >= 0) {
            makeNumRecursive(nums, num * 10 + grid[idx_x][idx_y], idx_x,
                             idx_y - 1, grid, digit + 1);
        }
        if (idx_y + 1 < SIZE) {
            makeNumRecursive(nums, num * 10 + grid[idx_x][idx_y], idx_x,
                             idx_y + 1, grid, digit + 1);
        }
    }
}

void printSol(int idx, int res) {
    printf("#%d %d\n", idx, res);
}

void setInput(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}