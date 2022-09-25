#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> alphabet;
void make(int end, string password);
int L, C;

int main() {
    cin >> L >> C;
    for (int i = 0; i < C; i++) {
        string tmp;
        cin >> tmp;
        alphabet.push_back(tmp);
    }

    sort(alphabet.begin(), alphabet.end());
    for (int i = 0; i < C; i++) {
        make(i, alphabet[i]);
    }
}

void make(int end, string password) {
    string tmp = password;
    int found = 0;
    if (password.length() == L) {
        found = tmp.find_first_of("aeiou");
        while (found != string::npos) {
            tmp.erase(found, 1);
            found = tmp.find_first_of("aeiou");
        }
        if (tmp.length() == password.length() || tmp.length() < 2) {
            return;
        }
        cout << password << "\n";
    } else if (end == C - 1) {
        return;
    } else {
        for (int i = end + 1; i < C; i++) {
            make(i, password + alphabet[i]);
        }
    }
}