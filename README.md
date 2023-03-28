## 알고리즘
문제 풀이 시 실수했던 내용/주의할 사항들을 정리합니다.

<br>

**🚨 조건문에서 and/or 연산자 사용시 : 괄호, ! 위치 주의**

`!((moveTo.first == pacMan.first) && (moveTo.second == pacMan.second))`

-> ! 연산자가 조건 전체에 대한 것인지 특정 괄호내에 있는 내용만 해당되는 것인지 주의

<br>
<br>


**🚨 for문 주의 : 초기값 지정하는 첫 루프를 돌때도 조건식 확인함**

→ 아래 코드는 아무것도 출력되지 않음

```c
for(int i=10;i<10;i++){
	cout << i << "\n";
}
```

구조체 배열(메모리풀) 초기화시 함부로 0으로 채우지 않기

ex) `memset(pool, 0, sizeof(dir) * n);`

<br>

<br>
**🚨 vector에서 erase 함수 + for 문 쓸 때 주의**

ex) `vector<int> array;`


| 1 | 2 | 3 | 4 | 5 |
| --- | --- | --- | --- | --- |


1,2,3 지우기

```c
for (auto it = array.begin(); it != array.end(); it++) {
      if (*it < 4) {
	        array.erase(it);
      }
}

for(int i : array){
    cout << i <<" ";
}
```

> 💻 2 4 5
> 

∵ 1 지우고 iterator는 2를 가리키는데 ++하면 3 가리킴

+) iterator로 순회하는 중에 erase 하면 꼬임

`it = array.erase(it)` 이런식으로 재할당 해주는 방식으로 부분적으로 해결 가능(항상 해결되는 것x)

<br>
<br>

**🚨 ”동시에 일어난다” vs “순차적으로 일어난다” 구분**

동시에 일어난다면 임시 배열 만들어서 처리

ex)

![Screenshot 2023-03-17 at 8 40 24 AM](https://user-images.githubusercontent.com/49016275/226225165-d0cef2fc-4944-4aa6-a66d-450642db7e11.png)

<br>
<br>

**🚨 차례대로 업데이트할 때 방향 주의**

ex) 인덱스 1→2→3→4→5 순서대로 업데이트시 인덱스 1에 있는 내용이 5까지 따라 올라갈 수 있음 ⇒ 이 경우 5→…→1 순서로 업데이트
<img width="476" alt="Screenshot 2023-03-20 at 10 19 11 AM" src="https://user-images.githubusercontent.com/49016275/226225222-5c1261f8-5719-46b0-aa88-71a6b26d3a9d.png">



<br>
<br>

**🚨 연결리스트 통째로 옮기는 경우 : 기존 위치의 head, tail 끼리 연결 필요**

(옮기는 도착지점 연결은 하고 기존 위치 head-tail끼리의 연결 까먹음..)

![Untitled Diagram drawio](https://user-images.githubusercontent.com/49016275/226225269-13adbbd5-f01c-405b-8857-84524682de0b.png)

<br>
<br>

**🚨 2차원 배열 중 가장 큰﹒작은 값 찾을 때 : 기준값 설정 주의**

ex) 배열에 요소들 값 : 0~

초기 기준값 ≠ 0, 배열에 있을 수 없는 값으로 초기값을 두고 최대(최소)값 찾기

```cpp
int calcFriends(pair<int, int> loc, bool *likes) {

// 기준값 (0,0)이 로직상 맞는지도 유의!!
// 최댓값 구할 때 - (0,0)이 아예 불가능 한 값인데 모든 가능한 값들보다 (0,0)에 있는 값이 큰 경우

    if ((loc.first == -1) && (loc.second == -1)) { 
        return -1;
    }
    // 상하좌우
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int nr = loc.first + dr[d];
        int nc = loc.second + dc[d];
        if ((0 <= nr) && (nr < n) && (0 <= nc) && (nc < n)) {
            if (likes[rides[nr][nc]]) {
                ret++;
            }
        }
    }
    return ret;
}
```

**🚨 메모리풀 사용시 크기 충분히 크게 두기!**

**🚨 방향 입력 받을 때 for문 인덱스 변수와 for문 내의 변수 이름이 같지 않도록 주의!**

ex)

```c
int d; //!!
...
for (int i = 1; i <= players; i++) { 
        for (int d = 0; d < 4; d++) { //!!
            for (int pr = 0; pr < 4; pr++) { 
                cin >> d; //!!
            }
        }
    }
```