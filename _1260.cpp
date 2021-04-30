#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

bool isvisited[1001];
bool tree[1001][1001];
void initArr();
void DFS(int vertex, int startVertex);
void BFS(int vertex, int startVertex);

int main(){
  int x,y;
  int vertex, edge, startVertex;

  scanf("%d%d%d", &vertex, &edge, &startVertex);

  initArr();

  for(int i=0;i<edge;i++){
    scanf("%d%d", &x, &y);
    tree[x][y] = true;
    tree[y][x] = true;
  }
  DFS(vertex, startVertex);
  printf("\n");
  initArr();
  BFS(vertex, startVertex);
}

void initArr(){
  for(int i=0;i<1001;i++){
    isvisited[i] = false;
  }
}


void DFS(int vertex, int startVertex){
  int target;
  target = startVertex;
  printf("%d ", target);
  isvisited[target] = true;

  for(int i=1;i<=vertex;i++){
    if(i==target){
      continue;
    }
    if(!isvisited[i] && tree[target][i] && tree[i][target]){
      DFS(vertex, i);
    }
  }
}

void BFS(int vertex, int startVertex){
  queue<int> que;
  que.push(startVertex);
  isvisited[startVertex] = true;

  int target;
  while(!que.empty()){
    target = que.front();
    que.pop();
    printf("%d ", target);

    for(int i=1;i<=vertex;i++){
      if(i==target){
        continue;
      }
      if(!isvisited[i] && tree[target][i] && tree[i][target]){
        que.push(i);
        isvisited[i] = true;
      }

    }
  }
}
