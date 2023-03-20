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