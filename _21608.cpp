#include <iostream>
#include <vector>

using namespace std;

vector<int> likes(4);
vector<vector<int>> seat(21, vector<int>(21));
int N;

// void input();
void test();
void solve();
bool comp(pair<int, int> a, pair<int, int> b);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // test();
    solve();
}

void solve() {
    int student;
    pair<int, int> res;
    vector<pair<int, int> > candidates;
    cin >> N;
    for (int i = 0; i < N * N; i++) {
        cin >> student;
        for (int j = 0; j < 4; j++) {
            cin >> likes[j];
        }
    }
    int likeCnt = 0, tmp, student;
    bool solved;
    // 1.
    for(int stu = 0 ; stu < N ; stu++){
        candidates.erase(candidates.begin());
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if(likeCnt > (tmp = calcLikes(stu, i,j))){
                    res.first = i;
                    res.second = j;
                    candidates.erase(candidates.begin());
                    solved = true;
                }
                else if(likeCnt == tmp){
                    candidates.push_back(res);
                    candidates.push_back(make_pair(i,j));
                    solved = false;
                }   
            }
        }
        // 2
        int emptySeat;
        sort(candidates.begin(), candidates.end(), comp);
        if(!solved){
            for(auto seat : candidates){
                if(tmp < (emptySeat = calcEmpty(seat))){
                    res = seat;
                    tmp = emptySeat;
                }
            }
        }
        test();

        // 결과 계산
        
    }

}

int calcLikes(int stu, int row, int col){

}

int calcEmpty(pair<int, int> seat){
    int row = seat.first;
    int col = seat.second;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if((abs(row-i)+abs(col-j) == 1) && seat[i][j] == 0){
                
            }
        }
    }
}

bool comp(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

void test() {
    cout << "\n========================";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << seat[i][j] << " ";
        }
        cout << "\n";
    }
}