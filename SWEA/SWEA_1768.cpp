#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define N              4
#define MAX_QUERYCOUNT 1000000

static int digits[N];
static int digits_c[10];

static int T;

extern void doUserImplementation(int guess[]);

static int querycount; 

// the value of limit_query will be changed in evaluation
static const int limit_query = 234;

typedef struct {
	int hit;
	int miss;
} Result;

static bool isValid(int guess[]) {
	int guess_c[10];
	
	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

// API : return a result for comparison with digits[] and guess[]
Result query(int guess[]) {
	Result result;
	
	if (querycount >= MAX_QUERYCOUNT) {
		result.hit = -1;
		result.miss = -1;
		return result;
	}
	
    querycount++;
		
	if (!isValid(guess)) {
		result.hit = -1;
		result.miss = -1;
		return result;
	}
	
	result.hit = 0;
	result.miss = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.hit++;
		else if (digits_c[guess[idx]] > 0)
			result.miss++;

	return result;
}

static void initialize() {
	for (int count = 0; count < 10; ++count) digits_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		char c;
		do scanf("%c", &c); while(c < '0' || c > '9');
		digits[idx] = c - '0';
		digits_c[digits[idx]]++;
	}
	
	querycount = 0;
}

static bool check(int guess[]) {
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx]) return false;
	return true;
}

int main() {
	int total_score = 0;
	int total_querycount = 0;;
	
    // freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
    for (int testcase = 1; testcase <= T; ++testcase) {
        initialize();

        int guess[N];
		doUserImplementation(guess);

		if (!check(guess)) querycount = MAX_QUERYCOUNT;
        if (querycount <= limit_query) total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
    }
	if (total_querycount > MAX_QUERYCOUNT) total_querycount = MAX_QUERYCOUNT;
	printf("total score = %d\ntotal query = %d\n", total_score * 100 / T, total_querycount);
	return 0;
}
///////////////////////

bool isChecked[9877];
int candidates[5040]; 
bool isFirst = true;
int MAX = 0;

Result greedyCmp(int target, int candidate) {
    Result ret = {0, 0};
    int chk[10] = {0};
    for (int i = 0; i < 4; i++) {
        if ((target % 10) == (candidate % 10)) {
            ret.hit++;
        } else {
            chk[target % 10]++;
            chk[candidate % 10]++;
        }

        if (chk[target % 10] == 2) {
            ret.miss++;
        }
        if(chk[candidate % 10] == 2){
            ret.miss++;
        }

        target /= 10;
        candidate /= 10;
    }
    return ret;
}

void initCandidates() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == j)
                continue;
            for (int k = 0; k < 10; k++) {
                if (i == k || j == k)
                    continue;
                for (int l = 0; l < 10; l++) {
                    if (i == l || j == l || k == l)
                        continue;
                    candidates[MAX++] = i * 1000 + j * 100 + k * 10 + l;
                }
            }
        }
    }
}

void initChecked() {
    for (int i = 0; i < MAX; i++) {
        isChecked[candidates[i]] = false;
    }
}

void itoArr(int num, int *arr) {
    arr[0] = num / 1000;
    arr[1] = (num % 1000) / 100;
    arr[2] = (num % 100) / 10;
    arr[3] = (num % 10);
}

void doUserImplementation(int guess[]) {
    if (isFirst) {
        isFirst = false;
        initCandidates();
    }
    initChecked();
    while (1) {
        int target;
        for (int i = 0; i < MAX; i++) {
            if (!isChecked[candidates[i]]) {
                target = candidates[i];
                itoArr(target, guess);
                break;
            }
        }
        Result target_result = query(guess);

        if (target_result.hit == 4)
            break;
        else
            isChecked[target] = true;

        for (int i = 0; i < MAX; i++) {
            if (!isChecked[candidates[i]]) {
                int candidate = candidates[i];
                Result temp = greedyCmp(target, candidate);

                // if 문 왜 이렇게 짜야 되는지 모르겠음..
                if ((target_result.hit != temp.hit) ||
                    (target_result.miss != temp.miss))
                    isChecked[candidate] = true;
            }
        }
    }
}