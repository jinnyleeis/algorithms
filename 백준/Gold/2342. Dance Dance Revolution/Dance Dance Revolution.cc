#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std; 

typedef long long ll; 

ll dp[100002][5][5];
const int INF = 1e9;
vector<int> query;

ll moveCost(int cur, int next) {
    if (cur == 0) return 2;       // 아직 정중앙에 위치했다면,
    if (cur == next) return 1;      // 같은 지점을 다시 누를 경우
    if (abs(cur - next) == 2) return 4;  // 반대방향이면,
    return 3;
    // 이 외의 경우는 인접 이동 (3의 비용)
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    
    fill(&dp[0][0][0], &dp[0][0][0] + 100002 * 5 * 5, INF);
    
    while (true) {
        int q;
        cin >> q; 
        if (q == 0) break;
        query.push_back(q);
    }
    
    int N = query.size();
    dp[0][0][0] = 0; // 초기 상태: 두 발 모두 중앙(0)에 있음

    for (int i = 1; i <= N; i++) {
        int q = query[i - 1]; // 이번 i번째에 해당하는 쿼리의 위치
        for (int l = 0; l <= 4; l++) {
            for (int r = 0; r <= 4; r++) {
                if (dp[i - 1][l][r] == INF)
                    continue;
                
                if (i == 1) {
                    dp[i][q][0] = dp[0][0][0] + moveCost(0, q);
                    dp[i][0][q] = dp[0][0][0] + moveCost(0, q);
                } else {
                    // min 적용했으니까 (q,r) or (l,q)가 (4,4)과 같이 동일 지점 되는 것은
                    // 원래 있던 쪽에서 누르는 것보다 비용이 무조건 클 것이므로, if문 여기서도 안써도 될듯?
                    
                        dp[i][q][r] = min(dp[i][q][r], dp[i - 1][l][r] + moveCost(l, q));
                  
                   
                        dp[i][l][q] = min(dp[i][l][q], dp[i - 1][l][r] + moveCost(r, q));
                    }
                }
            }
        }
    
    
    ll res = INF;
    for (int l = 0; l <= 4; l++) {
        for (int r = 0; r <= 4; r++) {
            res = min(res, dp[N][l][r]);
        }
    }
    cout << res << "\n";
    
   
    
    return 0;
}