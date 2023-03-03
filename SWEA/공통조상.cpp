#include <iostream>
#include <cstring>
using namespace std;

struct node {
    int data;
    node *parent;
    node *child[2];
    int childCnt;
};

node tree[100001] = {0, NULL, NULL, 0};
bool visited[100001] = {};

void debug(node *start);
int findParent(node *start);
int countChild(int &subTree, node *start);

int main() {
    int tc, V, E, target1, target2;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        memset(tree, 0, sizeof(tree));
        cin >> V >> E >> target1 >> target2;
        for (int edge = 1; edge <= E; edge++) {
            int parent, child;
            cin >> parent >> child;
            tree[parent].data = parent;
            tree[parent].child[tree[parent].childCnt++] = &tree[child];
            tree[child].data = child;
            tree[child].parent = &tree[parent];
        }
        memset(visited, 0, sizeof(visited));
        findParent(&tree[target1]);
        int commonParent = findParent(&tree[target2]);
        int subTree = 0;
        countChild(subTree, &tree[commonParent]);
        cout << "#" << t << " " << commonParent << " " << subTree << "\n";
    }
}

int findParent(node *start) {
    if (visited[start->data]) {
        return start->data;
    }
    visited[start->data] = true;
    if (start->data == 1) {
        return 0;
    }
    return findParent(start->parent);
}

void debug(node *start) { // DFS
    cout << start->data << " ";
    if (start->childCnt > 0) {
        for (int i = 0; i < start->childCnt; i++) {
            debug(start->child[i]);
        }
    }
}

int countChild(int &subTree, node *start) {
    subTree++;

    if (start->childCnt > 0) {
        for (int i = 0; i < start->childCnt; i++) {
            countChild(subTree, start->child[i]);
        }
    }
}