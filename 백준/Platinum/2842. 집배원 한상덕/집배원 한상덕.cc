#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

int N;
int a[51][51]; // 지도: -1: 우체국, 1: 집, 0: 빈 칸
int h[51][51]; // 각 칸의 고도
int sy, sx;   // 우체국 좌표
int housesNum = 0;
int globalMin = 1e9, globalMax = 0; // 우체국과 집들 중 최소, 최대 고도

// 8방향 이동
int dx[] = {-1,-1,-1, 0, 1, 1, 1, 0};
int dy[] = {-1, 0, 1, 1, 1, 0,-1,-1};

bool visited[51][51];

// DFS: 현재 고도 범위 [lowBound, highBound] 내에서 모든 집을 방문할 수 있는지 확인
bool dfs(int y, int x, int lowBound, int highBound) {
    if(y < 0 || y >= N || x < 0 || x >= N) return false;
    if(visited[y][x]) return false;
    // 현재 칸의 고도가 범위 밖이면 이동 불가
    if(h[y][x] < lowBound || h[y][x] > highBound) return false;
    
    visited[y][x] = true;
    
    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        dfs(ny, nx, lowBound, highBound);
    }
    return true;
}

// 주어진 고도 범위 [lowBound, highBound] 내에서 모든 집에 도달 가능한지 검사
bool checkConnectivity(int lowBound, int highBound) {
    // 우체국과 모든 집의 고도가 현재 범위에 포함되어야 함.
    if(h[sy][sx] < lowBound || h[sy][sx] > highBound) return false;
    if(globalMin < lowBound || globalMax > highBound) return false;
    
    memset(visited, 0, sizeof(visited));
    dfs(sy, sx, lowBound, highBound);
    
    // 지도 내의 모든 집을 방문했는지 확인
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(a[i][j] == 1 && !visited[i][j]) return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    vector<int> uniqHeights; // 모든 칸의 고도들을 저장할 벡터
    
    for (int i = 0; i < N; i++){
        string row;
        cin >> row;
        for (int j = 0; j < N; j++){
            char c = row[j];
            if(c == 'P'){
                a[i][j] = -1;
                sy = i; sx = j;
            } else if(c == 'K'){
                a[i][j] = 1;
                housesNum++;
            } else {
                a[i][j] = 0;
            }
        }
    }
    
    // 고도 입력 및 global 최소/최대 고도 갱신 (우체국과 집에 해당하는 칸만 고려)
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> h[i][j];
            uniqHeights.push_back(h[i][j]);
            // 우체국 또는 집인 경우에만 global 범위 갱신
            if(a[i][j] == -1 || a[i][j] == 1){
                globalMin = min(globalMin, h[i][j]);
                globalMax = max(globalMax, h[i][j]);
            }
        }
    }
    
    // 유니크 고도 배열 생성 (정렬 및 중복 제거)
    sort(uniqHeights.begin(), uniqHeights.end());
    uniqHeights.erase(unique(uniqHeights.begin(), uniqHeights.end()), uniqHeights.end());
    
    int ans = 1e9;
    int j = 0;
    // 두 포인터를 이용하여 altitude range [uniqHeights[i], uniqHeights[j]] 후보를 조절
    for (int i = 0; i < uniqHeights.size(); i++){
        // 만약 우체국 및 집들의 고도가 현재 i보다 작다면 의미 없으므로 건너뛰기
        if(uniqHeights[i] > globalMin) continue;
        
        // j는 항상 i 이상부터 시작
        while(j < uniqHeights.size()){
            // 후보 범위가 우체국과 집들의 고도를 모두 포함하는지 먼저 확인
            if(uniqHeights[j] < globalMax) {
                j++;
                continue;
            }
            // 범위 [uniqHeights[i], uniqHeights[j]] 내에서 연결 가능한지 체크
            if(checkConnectivity(uniqHeights[i], uniqHeights[j])){
                ans = min(ans, uniqHeights[j] - uniqHeights[i]);
                break;  // i가 증가하면 범위가 좁아지므로 j를 더 줄일 수 없음
            } else {
                j++; // 연결이 불가능하면 high값을 늘려야 함.
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}
