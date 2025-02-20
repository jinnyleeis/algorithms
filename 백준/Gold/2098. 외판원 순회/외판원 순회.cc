#include<iostream>
#include<algorithm>
#include<cstring>


// 어디서 시작할지는 모름 걍 - 선을 이엇는데, 가장 비용이 작은 연결 선을 찾는 것임 
// VISITED 한것 다시 못온다. 

using namespace std;

const int INF = 1e9;

int N;

const int visit = 1 << 16; // 이게 전체 방문되었단 것을 나타냄 
int dp[16][visit];

int w[16][16];
// 0-아무것도 방문xx 
//int visited[1<<17];

// 방문 상태가 그런 상태에서 해당 위치에 서있으면, 

int root;

// 어떤 엣지를 사용하는지에 따라서 달라진다. 
// 
int dfs(int s, int temp) {


	//cout << s <<"  "<< temp << "\n";
	// 모든 마을 방문 상태 --- 근데 이게 루트면, 다시갈 수 있게?>.. 
	if (temp == (1 << N) - 1) {
		if (w[s][root] != -1) {
			//cout << "finish " << temp << "\n";
			return w[s][root];
		}
		else {
		//	cout << "finish " << temp << "\n";
			return INF;
		}
		
		//  
	
	
	}
	if (dp[s][temp] != -1) {
		//cout << "just return "<< s << dp[s][temp] << "\n";
		return  dp[s][temp];

	}
		int res = INF;
	
	for (int i = 0; i < N; i++) {
		
		//if (temp != (1 << N-1))) {
		//	continue; // 이미 간거니까 탐색xx
	//	}
		if ((temp&(1 << i))) {
			continue;
		}
		if (w[s][i] == -1 )continue;
		//visited[i] = 1;
		int newTemp = temp | (1 << i); // 각각 경우마다 누적 안되게끔!!!
		res = min(res, dfs(i, newTemp) + w[s][i]); // 각각의 엣지별로 비용다르니까 min함수 이거 겉에 씌워줘야
	
	}
	dp[s][temp] = res;
	return dp[s][temp];

}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			cin >> temp;
			if (i != j && temp == 0) {
				w[i][j] = -1;
				
			}
			else {
				w[i][j] = temp;
			}
		}
	}

	 root = 0; 
	// dp[0][1] = 0; // 첫번쨰 도시만 방문한 비용은 1이다. 



	 cout << dfs(0, 1) << "\n";

	return 0;
}