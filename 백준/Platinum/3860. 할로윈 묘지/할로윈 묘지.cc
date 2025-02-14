#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int W, H, G, E;
const int MAX = 900;  // 0-based로 처리하면 최대 노드 수는 W*H (최대 900)
const int INF = 1e9;
typedef pair<int,int> pii;

int mudeom[MAX]; // 묘비 여부: 해당 노드가 묘비이면 1
int ghost[MAX];  // ghost 여부: 해당 노드가 귀신 구멍 출발지이면 1

vector<pii> adj[MAX]; // 각 노드에서 갈 수 있는 간선들
// 노드 번호: (x,y) 좌표 -> node = y * W + x (0부터 시작)

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

// Bellman–Ford용 최단 거리
int dist[MAX];
bool mCycle = false;

// visited 배열 (노드 단위 방문 처리; 0-based)
bool visited[MAX];

// (x,y)를 0-based 노드 번호로 변환
int toIndex(int x, int y) {
    return y * W + x;
}

/*
 DFS 함수 (0-based node 인덱스 사용)
 - 일반 셀(ghost가 false)인 경우, 사방 인접 셀로 가는 간선을 추가하고 DFS 재귀호출.
 - 귀신 구멍 셀인 경우, 입력 단계에서 추가한 ghost 간선의 도착 노드에 대해 DFS 호출.
*/
void dfsNode(int node) {
    if(visited[node]) return;
    visited[node] = true;
    
    // 만약 출구 (W-1, H-1)라면 더 이상 인접 간선을 추가xxx
    if(node == toIndex(W-1, H-1)) return;
    
    // 일반 셀인 경우 (귀신 구멍이 아니라면)
    if(!ghost[node]) {
        int x = node % W;   // 0-based이므로 바로 계산
        int y = node / W;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            // 범위 체크
            if(nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
            int nextNode = toIndex(nx, ny);
            if(mudeom[nextNode]) continue; // 묘비면 이동 불가
            // 일반 이동 간선 (비용 1)
            adj[node].push_back({nextNode, 1});
            dfsNode(nextNode);
        }
    }
    // ghost 셀이라면, 입력 단계에서 추가한 ghost 간선의 도착지에 대해 DFS 호출
    if(ghost[node]) {
        for(auto edge : adj[node]) {
            // ghost 간선은 비용 t (일반 이동과 구분)
            int dest = edge.first;
            dfsNode(dest);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while(true){
        cin >> W >> H;
        if(W == 0 && H == 0) break;
        int N = W * H;
        
        // 초기화
        for(int i = 0; i < N; i++){
            adj[i].clear();
        }
        memset(mudeom, 0, sizeof(mudeom));
        memset(ghost, 0, sizeof(ghost));
        memset(visited, 0, sizeof(visited));
        mCycle = false;
        fill(dist, dist + N, INF);
        
        cin >> G;
        for(int i = 0; i < G; i++){
            int x, y;
            cin >> x >> y;
            // 입력은 (0,0)부터 시작한다고 가정
            int cell = toIndex(x, y);
            mudeom[cell] = 1;
        }
        
        cin >> E;
        for(int i = 0; i < E; i++){
            int x1, y1, x2, y2, t;
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            int from = toIndex(x1, y1);
            int to = toIndex(x2, y2);
            // ghost 간선: 입력 단계에서 바로 추가
            adj[from].push_back({to, t});
            ghost[from] = 1;
        }
        
        // 0번 노드가 (0,0)
        dfsNode(0);
        
        // Bellman–Ford: 노드 0부터 N-1까지 사용
        dist[0] = 0; // 시작 노드 (0,0)
        for(int t = 1; t <= N; t++){
            for(int u = 0; u < N; u++){
                if(dist[u] == INF) continue;
                for(auto edge : adj[u]){
                    int v = edge.first;
                    int cost = edge.second;
                    if(dist[v] > dist[u] + cost){
                        dist[v] = dist[u] + cost;
                        if(t == N) { // N번째에도 갱신되면 음의 사이클
                            mCycle = true;
                        }
                    }
                }
            }
        }
        
        int exitNode = toIndex(W-1, H-1);
        if(mCycle){
            cout << "Never" << "\n";
        } else if(dist[exitNode] == INF){
            cout << "Impossible" << "\n";
        } else {
            cout << dist[exitNode] << "\n";
        }
    }
    return 0;
}
