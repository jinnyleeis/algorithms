#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int,int> pii;

vector<pii> adj[502];    // 정방향 인접 리스트: s → {w, e}
vector<pii> radj[502];   // 역방향 인접 리스트: e → {w, s}

int dist[502];
int INF = 1e9;
int V, E;
int S, D;              // 시작 정점 S, 도착 정점 D

// 다익스트라 함수: 시작 정점 start부터 각 정점까지의 최단 거리를 dist[]에 저장
void fn(int start) {
    // dist는 호출 전에 초기화되어 있어야 함
    priority_queue<pii, vector<pii>, greater<pii>> q;
    dist[start] = 0;
    q.push({0, start});
    
    while(!q.empty()){
        pii u = q.top();
        q.pop();
        int cur = u.second;
        int startToCurCost = u.first;
        if(dist[cur] < startToCurCost) continue;
        for(auto &next: adj[cur]){
            int curToNextCost = next.first;
            int newStartToNextCost = startToCurCost + curToNextCost;
            if(newStartToNextCost < dist[next.second]){
                dist[next.second] = newStartToNextCost;
                q.push({newStartToNextCost, next.second});
            }
        }
    }
}

// 최단 경로에 포함된 모든 간선을 제거하는 함수 (역방향 탐색 이용)
// radj를 통해, u -> cur 간선이 최단 경로에 포함되면, forward 인접 리스트(adj[u])에서 해당 간선을 제거
// 각 정점을 한 번만 처리하도록 visited 배열을 사용
void removeShortestEdges(int dest) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(dest);
    visited[dest] = true;
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        // cur로 들어오는 모든 간선(역방향)
        for(auto &edge: radj[cur]) {
            int u = edge.second;  // radj에 저장된 형식: {w, s}
            int cost = edge.first;
            // 만약 u -> cur 간선이 최단 경로에 포함된다면
            if(dist[u] + cost == dist[cur]){
                // forward 인접 리스트에서 u -> cur 간선을 제거 (순서가 중요하지 않으므로 find_if 사용)
                auto it = find_if(adj[u].begin(), adj[u].end(), [cur, cost](const pii &p) {
                    return (p.second == cur && p.first == cost);
                });
                if(it != adj[u].end()){
                    adj[u].erase(it);
                }
                if(!visited[u]){
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true) {
        cin >> V >> E;
        if(V == 0 && E == 0)
            break;
        cin >> S >> D;
        
        // 테스트 케이스마다 인접 리스트 초기화
        for (int i = 0; i < 502; i++) {
            adj[i].clear();
            radj[i].clear();
        }
        
        // dist 배열 초기화
        fill(dist, dist + 502, INF);

        for(int i = 0; i < E; i++){
            int s, e, w;
            cin >> s >> e >> w;
            // 정방향 간선: s에서 e로 (가중치 w)
            adj[s].push_back({w, e});
            // 역방향 간선: e에서 s로 (가중치 w)
            radj[e].push_back({w, s});
        }
        
        // 1. S에서 D까지의 최단 경로 탐색
        fill(dist, dist + 502, INF);
        fn(S);
        
        // 최단 경로가 존재하지 않으면 바로 -1 출력
        if(dist[D] == INF) {
            cout << -1 << "\n";
            continue;
        }
        
        // 2. 최단 경로에 포함된 모든 간선 제거
        removeShortestEdges(D);
        
        // 3. 최단 경로 간선 제거 후, S에서 D까지 다시 다익스트라 수행 (거의 최단 경로 탐색)
        fill(dist, dist + 502, INF);
        fn(S);
        
        if(dist[D] == INF){
            cout << -1 << "\n";
        } else {
            cout << dist[D] << "\n";
        }
    }
    
    return 0;
}

