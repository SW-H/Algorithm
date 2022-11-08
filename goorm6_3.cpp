#include <iostream>
#include <vector>
using namespace std;

#define ALPHA_CNT 26
void encrypt(string token);
void decrypt(string token);
string S, token, res;

int main() {
    int T;
    cin >> T;
    fflush(stdin);
    for (int i = 0; i < T; i++) {
        getline(cin, S);
        fflush(stdin);
        getline(cin, token);
        fflush(stdin);
        res.clear();
        if (token[0] == 'E') {
            encrypt(token.substr(2));
        } else {
            decrypt(token.substr(2));
        }
        cout << "\n";
    }
}

void encrypt(string token) {
    for (int i = 0; i < S.size(); i++) {
        if ('A' <= S[i] && S[i] <= 'Z') {
            cout << ((char)('A' + (S[i] - 'A' + token[i % token.size()]) %
                                      ALPHA_CNT));
        } else if ('a' <= S[i] && S[i] <= 'z') {
            cout << ((char)('a' + (S[i] - 'a' + token[i % token.size()]) %
                                      ALPHA_CNT));
        } else {
            cout << (S[i]);
        }
    }
}

void decrypt(string token) {
    for (int i = 0; i < S.size(); i++) {
        if ('A' <= S[i] && S[i] <= 'Z') {
            cout << (char)('A' + (S[i] - 'A' + ALPHA_CNT -
                                  token[i % token.size()] % ALPHA_CNT) %
                                     ALPHA_CNT);
        } else if ('a' <= S[i] && S[i] <= 'z') {
            cout << (char)('a' + (S[i] - 'a' + ALPHA_CNT -
                                  token[i % token.size()] % ALPHA_CNT) %
                                     ALPHA_CNT);
        } else {
            cout << S[i];
        }
    }
}