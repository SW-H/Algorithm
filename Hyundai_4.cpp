#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define START                                                                  \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);

vector<pair<int, int> > pws;
int commonPW, n;
string button;
int main(){
    cin >> commonPW >> n;
    int loc, pw;
    for(int i=0;i<n;i++){
        cin >> loc >> pw;
        pws.push_back(make_pair(loc, pw));
    }
    cin >> button;
    cout << button.substr(0, button.find_first_of(" "));
}