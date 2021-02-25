#include <cstdio>
#include <stack>
#include <string>
#include <iostream>

using namespace std;
bool check_using_stack(string snt);
bool check(string snt);

int main() {
    int T;
    string snt;
    cin>>T;
//    cin.ignore(INT_MAX, '\n');
//    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        cin >> snt;
        if (check(snt)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

bool check(string snt){
    int cntOfOpen=0;
    for (int i = 0; i < snt.length(); i++) {
        if (snt.at(i) == '(') {
            cntOfOpen++;
        }
        else {
            if (!cntOfOpen) {
                return false;
            }
            else {
                cntOfOpen--;
            }
        }
    }
    if (!cntOfOpen) {
        return true;
    }
    else {
        return false;
    }
}

bool check_using_stack(string snt) {
    stack<char> stk;
    for (int i = 0; i < snt.length(); i++) {
        if (snt.at(i) == '(') {
            stk.push('(');
        }
        else {
            if (stk.empty()) {
                return false;
            }
            else {
                stk.pop();
            }
        }
    }
    if (stk.empty()) {
        return true;
    }
    else {
        return false;
    }
}

