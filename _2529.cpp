#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int k;
string sequence;

bool checkOperator();
string toString(int *nums);

int main() {
    cin >> k;
    string tmp;
    for (int i = 0; i < k; i++) {
        cin >> tmp;
        sequence += tmp; // sequence : < >
    }
    vector<string> res;
    while (next_permutation(nums, nums + 10)) {
        if (checkOperator()) {
            string vecToStr = toString(nums);
            res.push_back(vecToStr);
        }
    }
    cout << *max_element(res.begin(), res.end()) << "\n"
         << *min_element(res.begin(), res.end());
}

string toString(int *nums) {
    string res;
    for (int i = 0; i < k + 1; i++) {
        res += to_string(nums[i]);
    }
    return res;
}

bool checkOperator() {
    for (int i = 0; i < k; i++) {
        if (!(sequence[i] == '>' && (nums[i] > nums[i + 1])) &&
            !(sequence[i] == '<' && (nums[i] < nums[i + 1]))) {
            return false;
        }
    }
    return true;
}
