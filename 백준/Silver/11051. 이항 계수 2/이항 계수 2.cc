#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

/*
모듈러는 나눗셈 분배xx
but 덧셈은 가능!! dp이용하기 매우 편리

손계산으론 어려우니까, dp를 사용해서 써보자. 
DP[n][k]=nCk(mod p)= (n-1Ck+n-1Ck-1)(mod p) 
= (n-1Ck)(mod p)+(n-1Ck-1)(mod p) 
=dp[n-1][k]+dp[n-1][k-1]
*/
long long dp[1004][1004];
int N, K;

int main() {

	cin >> N >> K;

	// if i=1이면, 이미 기저에 해당하는 [1][0]// [1][1]의 값만 존재할 것이므로
	// 반복문 내에서, i=2부터 돌리면 된다! - j는 1부터 돌리면 됨(0은 이미 기저에서 계산)

	for (int i = 0; i <= N; i++) {
		dp[i][0] = 1;
	}
	for (int i = 0; i <= N; i++) {
		dp[i][i] = 1;
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			dp[i][j] = (dp[i - 1][j]+dp[i - 1][j - 1])%10007;
		}

	}

	cout << dp[N][K] << "\n";
}