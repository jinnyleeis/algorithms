#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>

using namespace std;


int N, K, result;
int a[1003][3] ; //0이 값 // 1이 - 소수여부 마킹 // 2가 - 지워졌는지 
int cnt; 


bool isPrime(int num) {
	bool isprime = true;
	// 1, num은 소수여도 나눠지는거 가능이니까 제외. 
	// o(n)
	for (int i = 2; i < num; i++) {
		if (num%i == 0) {
			isprime = false;
			break;
		}
	}
	return isprime;
}
int main() {

	cin >> N >> K;
	// 0. 
	for (int i = 2; i <= N; i++) {
		a[i][0] = i;
		if (isPrime(a[i][0])) {
			a[i][1] = 1;
		}
	}

	// 1. 

	for (int i = 2; i <= N; i++) {
		if(a[i][1]==1){ // 소수면, 
			a[i][2] = 1; // 소수가 자기 자신을 지움
			cnt++; 
			
			if (cnt == K) {
				result = a[i][0];
				break;
			}

			for (int j = pow(i, 2); j < N + 1; j+=i) {
				// 주의  j+=i가 아니라, j++하면,
				// j의 배수가 아닌 것도 지워진다!!!
				// 걍 뒤에 있는 것 다 지우게 되잖아
				if (a[j][2]==0) {
					a[j][2] = 1;
					cnt++;
					if (cnt == K) {
						result = a[j][0];
						break;
						
					}

				}
			}
	}
}
	cout << result << "\n";
	return 0; 
}


/*
에라토스테네스의 체는 N보다 작거나 같은 모든 소수를 찾는 유명한 알고리즘이다.

이 알고리즘은 다음과 같다.

0. 2부터 N까지 모든 정수를 적는다.

1. 아직 지우지 않은 수 중 가장 작은 수를 찾는다.
이것을 P라고 하고, 이 수는 소수이다.
-> 지우지 않은 수가 무조건 소수는 아닐 수도 있잖아?
근데, 소수이면서, 가장 작은 남아있는 수를 찾으라는건가?

2. P를 지우고, 아직 지우지 않은 P의 배수를 크기 순서대로 지운다.
-> 이걸 보니, 위의 나의 추측이 맞는 듯하다.
->  근데 이걸, target_idx = (p.idx)^2 부터 수행해도 된다는 것이다.
시간 복잡도 0(N*LOG(LOG(N)))인 것 참고해라.

아직 모든 수를 지우지 않았다면, 다시 2번 단계로 간다.


N, K가 주어졌을 때, K번째 지우는 수를 구하는 프로그램을 작성하시오.




*/