#include <cstdio>
#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
    string snt, order;
    int M;
    deque<char> left;
    deque<char> right;

    cin >> snt; //abcd
    cin.ignore(INT_MAX, '\n');
//    scanf("%d",&M);
    cin >> M;
    cin.ignore(INT_MAX, '\n');

    for (int i = 0; i < snt.length(); i++) {
        left.push_back(snt.at(i));
    }

    for (int i = 0; i < M; i++) {
//        cin >> order;
//        cin.ignore(INT_MAX, '\n');
        getline(cin,order);

        if (order.at(0) == 'L') { //l
            if (!left.empty()) {
                right.push_front(left.back());
                left.pop_back();
            }
        } else if (order.at(0) == 'D') { //D
            if (!right.empty()) {
                left.push_back(right.front());
                right.pop_front();
            }
        } else if (order.at(0) == 'B') { //B
            if (!left.empty()) {
                left.pop_back();
            }
        } else { //P
            left.push_back(order.at(2));
        }
        order.clear();
    }
    while (!left.empty()) {
        printf("%c", left.front());
        left.pop_front();
    }
    while (!right.empty()) {
        printf("%c", right.front());
        right.pop_front();
    }
}