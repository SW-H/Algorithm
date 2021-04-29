#include <cstdio>
#include <stack>
#include <string>
#include <iostream>

using namespace std;
int check(string snt);
//bool check(string snt);

int main() {
    int T;
    string snt;
    cin >> T;
//    cin.ignore(INT_MAX, '\n');
//    scanf("%d", &T);

//    for (int i = 0; i < T; i++) {
    cin >> snt;
    printf("%d",check(snt));

//    }
}
int check(string snt) {
    stack<int> stk;
    int temp;
    int lazer = 0, res = 0;
    for (int i = 0; i < snt.length(); i++) {
        if (snt.at(i) == '(') {
            stk.push(i); //index를 넣음
        } else {
            if(stk.empty()){
                res+=lazer+1;
                lazer=0;
            }
            if (stk.top() == i - 1) {
                lazer++;
            }
            stk.pop();
        }
    }
    return res;
/*    if (stk.empty()) {
        return true;
    } else {
        return false;
    }*/
}


/*

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
*/