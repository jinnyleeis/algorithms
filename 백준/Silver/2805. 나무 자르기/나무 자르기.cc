#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

long long minAmount;
long long maxHeight;
long long maxHeightTree;
long long minHeightTree = 1e9+100;
int N, M;


long long trees[1000004];

long long checkAmount(long long cutHeight) {
	long long total = 0;
	for (int i = 0; i < N; i++) {
		long long perAmount = trees[i] - cutHeight; // 트리의 실제 높이 - 절단기 높이가 양에 해당
		if (perAmount > 0) {
			total += perAmount;
		}
	}

	return total;

}

void fn(long long start, long long end) {

	if (start < 0)return;
	if (start > end)return;
	long long mid = (start + end) / 2;
	long long curAmount = checkAmount(mid);
	
	if (curAmount < M) {
		// CURAMOUNT를 넘겨야!! 
		// 더 양을 늘리려면,더 앞으로 설정해야 한다. - 더 많이 자르게!!
		end = mid - 1;
		fn(start, end);

	}
	else if (curAmount >= M) {
		// 더 양을 줄이려면,더 뒤로 설정해야 한다. - 더 적게 자르게!!
		// st는 end 와 같을 때의 maxheight이 전역으로 설정되어 있을 것임 
		maxHeight = max(mid, maxHeight);
		start = mid + 1;
		fn(start, end);
	}
}




int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> trees[i];
		maxHeightTree = max(trees[i], maxHeightTree);
		minHeightTree = min(trees[i], minHeightTree);
	}

	// 
	fn(0, maxHeightTree);

	cout << maxHeight << "\n";
}
