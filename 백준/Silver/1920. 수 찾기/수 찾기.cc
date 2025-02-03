#include <iostream>
#include <algorithm>

using namespace std;

int arr[100004];
int q[100004];
int N, M;

/*

l,r을 맨 끝으로 설정한다.
우리가 찾는 값보다 작으니까, L,R을 조정 MID는 포함XXXX

*/

int bs(int x) {

	int l = 0, r = N - 1; // return 0를 추가할 필요가 없는게,

	while (l <= r) {

		int mid = (l + r) / 2;
		// 이렇게 아예 처음부터 기본 값으로 설정해 놓으면 되기 때문이다. 
		if (arr[mid] == x) {
			return 1; // 이 BC 위치 때문에 내꺼는 시간 초과 나는 건가?
		}
		if (arr[mid] < x) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}

	return 0;
}

int main() {

	cin >> N;
	for (int i = 0; i < N;  i++) {
		cin >> arr[i];
	}
	sort(arr, arr + N);

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> q[i];
	}
	for (int i = 0; i < M; i++) {

		cout << bs(q[i]) << "\n";
	}

	return 0;
}
