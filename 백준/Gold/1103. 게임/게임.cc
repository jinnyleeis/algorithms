#include <bits/stdc++.h>
using namespace std;

int n, m, ny, nx;
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, 1, 0, -1};

int mp[51][51];
int dp[51][51];  // 2차원 dp 배열로 수정
bool visited[51][51];  // 무한 루프 감지를 위한 방문 추적

// dp[y][x]: 현재 위치에서 최대 몇 번 이동할 수 있는가?
int move(int y, int x) {


    // 현재 경로에서 방문 중이라면, 무한 루프가 발생했음을 의미
    if (visited[y][x]) {
     cout << -1 << "\n";  // 무한 루프가 발생한 경우
       exit(0);
    }
    
// 이미 계산된 값이 있으면 그 값을 반환
    if (dp[y][x] != -1) return dp[y][x];

    visited[y][x] = true;  // 현재 경로에 방문했음을 표시
    dp[y][x] = 1;  // 이동을 시작할 수 있는 상태로 초기화

    // 4방향 탐색
    for (int i = 0; i < 4; i++) {
        ny = y + mp[y][x] * dy[i];
        nx = x + mp[y][x] * dx[i];

        // 오버플로우 처리 및 구멍 처리
        if (ny >= n || nx >= m || ny < 0 || nx < 0 || mp[ny][nx] == 0) continue;

        int ret = move(ny, nx);
        dp[y][x] = max(dp[y][x], ret + 1);  // 현재 위치에서 한 번 이동하고 나서 계산

       
    }
    
    //재귀 호출이 끝난 후에 해당 경로에서 방문을 해제 필요 
    // 다른 경로에서 다시 방문할 때 꼬이게됨
    
    visited[y][x] = false;  // 현재 경로에서 벗어났으므로 방문 해제
    
    return dp[y][x];
}

int main() {
    cin >> n >> m;

    // 입력 받기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char v;
            cin >> v;
            if (v == 'H') {
                mp[i][j] = 0;  // 'H'는 구멍이므로 0으로 처리
            } else {
                mp[i][j] = v - '0';  // 숫자는 변환해서 저장
            }
        }
    }

    // DP 테이블 초기화 (-1로)
    memset(dp, -1, sizeof(dp));
    memset(visited, false, sizeof(visited));  // 방문 배열 초기화

    // 첫 위치에서 최대 이동 횟수 계산
    int result = move(0, 0);
   
        cout << result << "\n";  // 정상적인 경우 최대 이동 횟수 출력
  

    return 0;
}
