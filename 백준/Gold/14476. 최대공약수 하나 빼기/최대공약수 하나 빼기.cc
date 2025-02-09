#include <iostream>
#include <vector>
#include <algorithm>
#include<set>
#include<string>
#include <limits>

// 빠진 수의 약수가 되면, 안된다!! 
// 이때, 최대공약수는 K의 약수가 되면 안 된다.
using namespace std;
int n;
long long maxN = -1e9;
long long target; 

const long long MAX = (1 << 20);
int a[2 * MAX];

// 최대공약수 
int gcd(int a, int b) {

	int x = a;
	int y = b;
	int r;
	while (y != 0) {

		r = x % y; // 나머지 
		x = y;
		y = r;
	}

	return x;
}

// 다시 원상 복구는 어떻게 할까? 
// restore(해당 줄만 다시 계산) 
void remove(long long idx) {
	if (idx >= MAX) {
		a[idx] = -1;
	}
	long long node = idx;

	while (node > 1) {
		node /= 2;

		// 원소가 안채워진 경우
		if (a[2 * node] == 0) {
			a[node] = 0; // 이때는 아예 고려를 안해. 
		}else if(a[2 * node+1] == 0) {
			a[node] = a[2 * node];
		}

		// 중간에 빼고 계산하는 경우 
		if (a[2 * node] == -1) {
			a[node] = a[2 * node + 1];
		}
		else if (a[2 * node + 1] == -1) {
			a[node] = a[2 * node];
		}
		else {
			a[node] = gcd(a[2 * node], a[2 * node + 1]);
		}

	}
}


void restore(long long idx) {
	long long node = idx;

	while (node > 1) {
		node /= 2;
		a[node] = gcd(a[2 * node], a[2 * node + 1]);
		
	}

	
}

int main() {
	ios_base::sync_with_stdio(false);   cout.tie(NULL); cin.tie(NULL);

	cin >> n;
	for (long long i = 0; i < n; i++) {
		cin >> a[MAX + i]; 
	}// 자신의 gcd는 자신임 

	for (long long i = MAX - 1; i >= 1; i--) {
		a[i] = gcd(a[2 * i], a[2 * i + 1]);
	}

	// update - 하나의 숫자를 뺀다. 
	// 리프 노드 하나씩 -1로 만들고, -1 제외인걸로만 업데이트 하도록 
	// 수정한다. 

	for (long long i = 0; i < n; i++) {

		int preserve = a[MAX + i];
		remove(MAX + i);
		// remove 끝나면 다시 복구하는 것도 해야!
		if (a[MAX] < maxN || (preserve% a[1] ==0)) {
			// 이 두경우는 해당 뺴는게 불가능한 경우이므로, 다른걸 뺴야!!
			a[MAX + i] = preserve;
		
			restore(MAX + i);
		}
		else {
			maxN = a[1];
			target = preserve;
		};
	}
	if (a[1] == 0 || maxN< 0) {
		cout << -1 << "\n";
		// a[1] == 0  이거는 4가 나오는데, 이걸로는 못걸러내나보네? 
	}
	else {
		cout << maxN << " " << target << "\n";
	}
	return 0;
}

//4가 8의