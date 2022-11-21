#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> seats;
int main() {
    int tmp;
    do {
        cin >> tmp;
        seats.push_back(tmp);
    } while (getc(stdin) == ' ');
    sort(seats.begin(), seats.end());
    int distance = seats[seats.size() - 1] * seats[seats.size() - 1],
        sum = seats[seats.size() - 1] * 2;
    pair<int, int> res;
    for (int i = 0; i < seats.size(); i++) {
        for (int j = i + 1; j < seats.size(); j++) {
            if (seats[j] - seats[i] < distance && seats[j] + seats[i] < sum) {
                res.first = seats[i];
                res.second = seats[j];
                distance = seats[j] - seats[i];
                sum = seats[j] + seats[i];
            }
        }
    }
    cout << res.first << " " << res.second;
}