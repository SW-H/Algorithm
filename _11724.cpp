#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int node, edge; // 정점 = vertex/node, 간선 = edge
bool visited[1001];

vector<vector<int> > graph(1001, vector<int>());
bool isAllVisited();
void DFS(int start);

int main() {
    cin >> node >> edge;
    int node1, node2;
    if (edge == 0) {
        cout << node;
        return 0;
    }
    for (int i = 0; i < edge; i++) {
        cin >> node1 >> node2;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    int res = 0;
    for (int i = 1; i <= node; i++) {
        // if ((visited[i] == false) && DFS(i)) {
        if (visited[i] == false) {
            res++;
        }
        DFS(i);
    }
    cout << res;
}

bool isAllVisited() {
    for (int i = 1; i <= node; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

deque<int> buffer;
void DFS(int start) {
    bool isAdjVisited = true;
    // if(isAllVisited()){
    //     return true;
    // }
    if (visited[start] == false) {
        buffer.push_back(start);
        visited[start] = true;

        // cout << start << " ";

        return DFS(start);
    }
    // else {
    for (int next : graph[start]) {
        if (visited[next] == false) {
            isAdjVisited = false;
            return DFS(next);
        }
    }
    // }
    if (!buffer.empty() && isAdjVisited) {
        // 정점 start와 인접한 노드를 모두 방문한 경우
        int next = buffer.back();
        buffer.pop_back();
        DFS(next);
    } else {
        return;
    }
}
