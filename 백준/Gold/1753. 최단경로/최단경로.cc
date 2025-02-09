#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;



// 

/*
. (1 ≤ V ≤ 20,000, 1 ≤ E ≤ 300,000) 

ElogV^2 - 최악 (즉, 방향 그래프 - 모든 노드 간 엣지 양방향으로)
-> 근데 결국 이 경우도 ElogE임 
*/


typedef pair<int,int> pii;

// pii를 받았으므로, greater 따지는 대상도 pii 
// 그럼 - first로 자동으로 오름차순 정렬될 것임 
priority_queue<pii,vector<pii>,greater<pii>> q;
vector<pii> adj[20004];
int dist[20004];
int INF=1e9;


int V,E,K;


// 첨에 int를 in으로 씀 하핳...
void fn(int start){
    
    // 시작 정점의 초기화 
    dist[start]=0; // 자기 자신으로 가는 것은 거리가 0일 것임 
    q.push({0,start}); // q는 push back이 아닌, push다!!!!
    
    while(!q.empty()){
        
        // q.front는 존재하지 않는다. 일반 queue가 front ㅇㅇ
        //  pq는, q.top이다 주의!!!!!
        pii u=q.top();
        q.pop();
        
        int cur=u.second;
        int startToCurCost=u.first;
        
        if(dist[cur]<startToCurCost)continue; // 버려지는 쓸모없는길임 
        
        for(auto &next: adj[cur]){
            int curToNextCost=next.first;
            int newStartToNextCost=startToCurCost+ curToNextCost;
            if(newStartToNextCost<dist[next.second]){
                dist[next.second]=newStartToNextCost;
                // q에 dist 업데이트 된거 집어넣는거 까먹은거 주의
                q.push({newStartToNextCost,next.second});
            }

            
        }
        
        
    }
    
}



int main(){
    
    
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    cin>>V>>E;
    cin>>K; // 시작 정점의 번호
    
    // memset 함수는 메모리의 각 바이트를 지정한 값(0~255)으로 채움 -> inf 저장 불가!!!
   // memset(dist,INF,sizeof(dist));
    fill(dist, dist + 20004, INF);
    // or 아예 dist 생성시, 벡터로 만들어서 vector<int> dist(20004, INF); 이게 젤 깔끔

    
    for(int i=1; i<=E; i++){
        int s,e,w;
       cin>>s>>e>>w;
       adj[s].push_back({w,e});
           
       }
        
    
    
    fn(K); 
    
    /*
    for(int i=1; i<=V; i++){
     for(auto &e:adj[i]){
         cout<<e.first<<e.second<<" ";
     }
     cout<<"\n";
    }
    */
    
    for(int i=1; i<=V; i++){
        if(dist[i]==INF){
            cout<<"INF"<<"\n";
        }else{
        cout<<dist[i]<<"\n";
            
        }
    }
    

  
    return 0;
}
    
    