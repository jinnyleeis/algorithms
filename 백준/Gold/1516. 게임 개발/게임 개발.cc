#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <cmath>
#include <queue>
#include <limits> 

using namespace std;


int n, m;
//queue<int> q;
queue<int> start;

// 1이 필수로 있는 애들 



vector<int> required[501];
int indegree[501];
int time[501]; // 이 타임을 누적해서 업데이트 한다. 
int ans[501];

//priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> sizes; // 사이즈, 번호 




int main() {


	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	

	for (int i = 1; i <= n; i++) {
		int t, b;
		cin >> t;
		time[i] = t;
		cin >> b;
		while (b != -1) {
		required[b].push_back(i); //
		indegree[i]++; // i에게 B가 필요로 되므로 -  i가 필요로 하는  다른 것들의 횟수임!!!!!!

		cin >> b;
		}	
	}

	// 초기 시작점들 
	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0) {
			ans[i] = time[i];
			start.push(i); // 일단 다 0인 애들 모음 
		}		
	}

	
	while (!start.empty()) {
		int cur = start.front(); 
		start.pop();
		

			for (auto &after : required[cur]) {
				indegree[after]--;
				ans[after] = max(ans[after], ans[cur] + time[after]);
				if (indegree[after] == 0) {
					start.push(after);

				}
			}
			
		}
		



	for (int i = 1; i <= n; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
	

}

		
		
	