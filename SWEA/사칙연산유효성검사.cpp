#include <iostream>
#include <deque>
#include <cstring>
#include <cctype>
using namespace std;

#define INIT                                                                   \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#define T 10

struct node {
    node *child[2];
    int childCnt;
    char cont;
};

node nodes[201];
deque<char> stk;

void initialize(); 
int validate();
void traverse(int& ret, node* start);

int main() {
    INIT;
    int vertices;
    for (int tc = 1; tc <= T; tc++) {
        initialize();
        cin >> vertices;
        int id;
        char cont;
        for (int v = 1; v <= vertices; v++) {
            cin >> id >> cont;

            int child;
            nodes[id].cont = cont;
            if (cin.get() != '\n') {
                cin >> child;
                nodes[id].child[nodes[id].childCnt++] = &nodes[child];
                if (cin.get() != '\n') {
                    cin >> child;
                    nodes[id].child[nodes[id].childCnt++] = &nodes[child];
                }
            }
        }
        cout << "#" << tc << " " << validate() << "\n";
    }
}

void initialize(){ 
    memset(nodes, 0, sizeof(nodes)); 
    stk.clear();
}


int validate(){
    int res = 1;
    traverse(res,&nodes[1]);
    return res;
}

void traverse(int& ret, node* start){
    if(start->child[0]){
        traverse(ret, start->child[0]);
    }
    if(isdigit(start->cont)){
        if(!stk.empty()){
            if(isdigit(stk.back())){
                ret = 0;
            }
            stk.pop_back();
        }
    }else if((stk.empty()) || !isdigit(stk.back())){
            ret = 0;
    } 
    stk.push_back(start->cont);
    if(start->child[1]){
        traverse(ret, start->child[1]);
    }
}