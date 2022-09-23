#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> adj(17);
vector<int> info;
int N, res;
void solve(set<int> vertex, int now, int sheep, int wolf);
void solve(set<int> vertex, int now, int sheep, int wolf) {
    if (info[now]) {
        wolf++;
    } else {
        sheep++;
    }
    if (wolf >= sheep) {
        return;
    }
    res = max(sheep, res);
    vertex.erase(now);
    for (auto next : adj[now]) {
        vertex.insert(next);
    }
    for (auto v : vertex) {
        solve(vertex, v, sheep, wolf);
    }
}

int solution(vector<int> _info, vector<vector<int>> edges) {
    N = info.size();
    info = _info;
    for (auto edge : edges) {
        adj[edge[0]].push_back(edge[1]);
    }
    solve({0}, 0, 0, 0);
    return res;
}