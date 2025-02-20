#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 100000;
int N, M;
typedef pair<int,int> pii;
//2.1×10⁹ 을 넘는다. 즉, 10^11정도까지 표현해야 하므로 long long 
typedef long long ll;
vector<pii> adj[MAX+1];

int depth[MAX+1];
ll cost[MAX+1][18];    // cost[u][k] : u에서 2^k번째 부모로 가는 경로 비용
int parent[MAX+1][18]; // parent[u][k] : u의 2^k번째 조상

void buildTree(int cur){
    for(auto &child : adj[cur]){
        int nxt = child.first;
        int w   = child.second;
        if(depth[nxt] != -1) continue;
        depth[nxt] = depth[cur] + 1;
        parent[nxt][0] = cur;
        cost[nxt][0]   = w;
        buildTree(nxt);
    }
}

void initDP(){
    for(int k=1; k<18; k++){
        for(int n=1; n<=N; n++){
            int p = parent[n][k-1];
            if(p == -1) continue;
            parent[n][k] = parent[p][k-1];
            cost[n][k]   = cost[n][k-1] + cost[p][k-1];
        }
    }
}

// LCA + 거리 
ll lca(int a,int b){
  
  if(depth[a]<depth[b]){
      swap(a,b);
  }
  
  // depth fit.
  int jump=depth[a]-depth[b]; // jump 횟수에 대응 
  
  int k=0;
  ll dist=0;
  while(jump){
      
      if(jump%2){
          dist+=cost[a][k];
          a=parent[a][k];
      }
      k++;
      jump/=2;
      
  }
  
  if(a==b){
      return dist;
  }
  
  // 동시에 점프 하기 
  for(int k=17; k>=0; k--){
      if(parent[a][k]!=parent[b][k]){
          dist+=(cost[a][k]+cost[b][k]);
          a=parent[a][k];
          b=parent[b][k];
      }
  }
  
  
  dist+=(cost[a][0]+cost[b][0]);
  a=parent[a][0];
  b=parent[b][0];
  
  return dist;
  
}

// 2번 쿼리용 "LCA만" 찾기
int getLCA(int a, int b){
    if(depth[a]<depth[b]) swap(a,b);
    // 높이 맞추기
    
    int diff=depth[a]-depth[b];
    int k=0;
    while(diff){
        
        if(diff%2){
            a=parent[a][k];
        }
        diff/=2;
        k++;
    }
    
   
    if(a==b) return a;
    for(int i=17; i>=0; i--){
        if(parent[a][i] != parent[b][i]){
            a=parent[a][i];
            b=parent[b][i];
        }
    }
    return parent[a][0];
}


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    for(int i=1; i<N; i++){
        int a,b,w;
        cin >> a >> b >> w;
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }

    memset(depth, -1, sizeof(depth));
    memset(parent, -1, sizeof(parent));
    memset(cost,   0, sizeof(cost));

    depth[1] = 0;
    buildTree(1);
    initDP();

    cin >> M;
   for(int i=0; i<M; i++){
        int type; cin >> type;
        if(type == 1){
            int u,v; cin >> u >> v;
            cout << lca(u,v)<< "\n";
        }
        else {
            int u,v,k;
           cin>>u>>v>>k;
           
           // k번쨰가
           // u ~ lca 
           // lca+1 ~ v인가에 따라 달라짐 
           int l= getLCA(u,v);
           int lenU=depth[u]-depth[l];  
           int lenV=depth[v]-depth[l];
           int totalNode=lenU+lenV+1; 
           if(lenU+1>=k){
                // k번쨰가 u ~ lca인 경우 
                int jump=k-1; // k번째라는게, u부터 포함해서 K번쨰 노드라는 거니까,
                // u가 1층 , k가 k층에 대응 -> so, u에서부터의 총 점프 횟수는, k-1일 것임 
                int step=0;
                while(jump){
                    if(jump%2){
                        u=parent[u][step];
                    }
                    jump/=2;
                    step++;
                }
                
                cout<<u<<"\n";
               
           }else if(lenU+1<k){
              // u의 입장에서 k번째 노드를 찾아야.
              // v가 처리해야 하는 노드 수 
            // totalNode-(k-1) = A 
            // -> 즉, 이는 v가 1층이라고 쳤을 때, v입장에서 A층에 도달하면, u의 입장에서 k번쨔 노드라는 것임 
            int jump=totalNode-(k-1)-1; // 1층에서 totalNode-(k-1)(A)에 도달하려면 , A-1 + 1번의 점프가 필요하다!
            int step=0;
            while(jump){
                if(jump%2){
                    v=parent[v][step];
                }
                step++;
                jump/=2;
                
            }
            
            cout<<v<<"\n";
               
               
           }
           
           
           
        }
   
    }
    return 0;
}

