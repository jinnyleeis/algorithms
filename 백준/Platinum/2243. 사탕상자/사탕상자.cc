#include <iostream>


using namespace std;

// 말을 잘들은 정도에 따라서, 맛있는 사탕 

/*

 정수 A, B, C가 주어진다.
 A가 1인 경우는 사탕상자에서 사탕을 꺼내는 경우이다.
 이때에는 한 정수만 주어지며, B는 꺼낼 사탕의 순위를 의미한다.
 이 경우 사탕상자에서 한 개의 사탕이 꺼내지게 된다.

 또, A가 2인 경우는 사탕을 넣는 경우이다.
 이때에는 두 정수가 주어지는데,
 B는 넣을 사탕의 맛을 나타내는 정수이고
 C는 그러한 사탕의 개수이다.
 C가 양수일 경우에는 사탕을 넣는 경우이고,
 음수일 경우에는 빼는 경우이다.

*/

int N;
const long long MAX = 1 << 20;
long long arr[2 * MAX];

// 해당 index , 바뀌는 숫자
void update(long long idx, long long num) {
	idx += MAX - 1;
	arr[idx] += num;
	while (idx > 1) {
		idx /= 2;
		arr[idx] = arr[2 * idx] + arr[2 * idx + 1];
	}
}

long long search(int idx, long long rank) {

	// 기저 리프 노드일 때, 인덱스를 리턴(드디어 찾음)하고, 
	// 뺴기 수행하면 됨(업데이트 이용)!!-이땐 이미 RANK는
	// 다 쓰고 필요없어진 상황임 
	if (idx >= MAX) {
		update(idx - MAX + 1, -1);
		return idx - MAX + 1;
	}
	if (rank <= arr[2 * idx]) {
		long long tempIdx = search(2 * idx, rank);
		return tempIdx;
	}
	else if (rank > arr[2 * idx]) {
		//	int tempIdx = search(2 * idx + 1, rank);
		long long tempIdx = search(2 * idx + 1, rank - arr[2 * idx]);
		// 해당 노드 입장에서 몇 위니까, 
		// 앞에 왼쪽노드 순위 포함된거 빼버림

		return tempIdx;
	}

}
// 말을 잘 들은 정도를 어떻게 수치화할 수 있을까?

int main() {

	ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
	cin >> N; // 사탕에 손댄 횟수 

	for (int i = 0; i < N; i++) {
		long long a, b, c;

		cin >> a;
		if (a == 1) {
			// 사탕 꺼내기 
			cin >> b;

			cout << search(1,b) << "\n";

			// 1은 루트 노드부터 서치 시작!!!!


		}
		else if (a == 2) {
			cin >> b >> c;
			// 사탕 넣기
			update(b, c);
		}

	}

	return 0;

}