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


/*
예시 답안

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+100;
char s[N], f, k[N];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("\n%[^\n]\n%c %[^\n]",s,&f,k);
        if(f=='E'){
            for(int i=0, j=0; s[i]; ++i, ++j){
                if(!k[j]) j=0;
                if('a'<=s[i] && s[i]<='z') s[i]=(s[i]+k[j]-'a')%26+'a';
                if('A'<=s[i] && s[i]<='Z') s[i]=(s[i]+k[j]-'A')%26+'A';
            }
        }
        else{
            for(int i=0, j=0; s[i]; ++i, ++j){
                if(!k[j]) j=0;
                if('a'<=s[i] && s[i]<='z') s[i]=(s[i]+(26-k[j]%26)-'a')%26+'a';
                if('A'<=s[i] && s[i]<='Z') s[i]=(s[i]+(26-k[j]%26)-'A')%26+'A';
            }
        }
        puts(s);
    }
}
*/