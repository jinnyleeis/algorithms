#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

int N, K;
vector<int> state;
int cnt; 

void fn(int curi, int level) {
	if (level==K-1) {
	//	for (auto &i : state) {
	//		cout << i << " ";
//
	//	}
	//	cout << "\n";
		cnt++;
		return;
	}
	
	for (int i = curi+1; i < N; i++) {
		state.push_back(i);
		fn(i,level+1);
		state.pop_back();
	}
}

int main() {

	cin >> N >> K;
	//nCk = n!/(n-k)!k! 
	
	for (int i = 0; i < N; i++) {
		state.push_back(i);
		fn(i,0);
	    state.pop_back();
	}

	if (K == 0) {
		cout << 1 << "\n";
	}
	else {
		cout << cnt << "\n";
	}
	return 0;
}