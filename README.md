## 알고리즘
문제 풀이 시 실수했던 내용/주의할 사항들을 정리합니다.

<br>

🚨 조건문에서 and/or 연산자 사용시 : 괄호, ! 위치 주의

`!((moveTo.first == pacMan.first) && (moveTo.second == pacMan.second))`

-> ! 연산자가 조건 전체에 대한 것인지 특정 괄호내에 있는 내용만 해당되는 것인지 주의

<br>
<br>


🚨 for문 주의 : 초기값 지정하는 첫 루프를 돌때도 조건식 확인함

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
🚨 vector에서 erase 함수 + for 문 쓸 때 주의

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

> 💻 2 4 5
> 

∵ 1 지우고 iterator는 2를 가리키는데 ++하면 3 가리킴

+) iterator로 순회하는 중에 erase 하면 꼬임

`it = array.erase(it)` 이런식으로 재할당 해주는 방식으로 부분적으로 해결 가능(항상 해결되는 것x)