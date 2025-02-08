#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits>

using namespace std;



// 

/*
한 도시에서 출발하여 다른 도시에 도착하는 m(1 ≤ m ≤ 100,000)개의 버스 : 엣지에 해당 
n(2 ≤ n ≤ 100)개의 도시 - 노드
모든 도시의 쌍 (A, B)에 대해서 도시 A에서 B로 가는데 필요한 비용의 최솟값 
-> 모든 도시의 쌍 -> 플로이드임 
*/

/*
 fill(&dist[0][0],&dist[101][101],1e8); -> xx 
 만약 dist가 int dist[101][101];로 선언되었다면 유효한 인덱스는 0부터 100까지
즉, &dist[101][101]는 실제 배열 범위를 벗어난 one‐past‐the‐end 포인터를 직접 사용하는 형태
이렇게 쓰는 것은 xx

대신, 배열의 시작 주소인 &dist[0][0]에 전체 원소의 개수(101*101)를 더한 포인터를 사사용하는
배열의 첫 원소부터 (101×101)개의 원소를 올바르게 초기화 가능 

*/

int dist[101][101];
int adj[101][101];



int N,M;

int main(){
    
    
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    fill(&dist[0][0], &dist[0][0] + 101 * 101, 1e8);
    fill(&adj[0][0], &adj[0][0] + 101 * 101, 1e8);
    
   // for(int i=0; i<=101; i++){ 배열 인덱스 안벗어나게 ..
   
    for(int i=0; i<=100; i++){
        dist[i][i]=0;
        adj[i][i]=0;
    }
    cin>>N;
    cin>>M;
    for(int i=0; i<M; i++){
        int s,e,w;
       cin>>s>>e>>w;
       if(w<adj[s][e]){
           // 이유 - 최소 비용 구하는 것이므로, 두 노드간 엣지 여러개 중에, 
           // 최소 비용 엣지를 저장하는 것이 맞을 것임 
       adj[s][e]=w;
           
       }
        
    }
    
    // 이거 옮겨담는거 초기화 주의!!!!
    for(int s=1; s<=N; s++){
        for(int e=1; e<=N; e++){
            //    if(adj[s][e]<1e5){ 등호 필요!! 10만도 포함이므로 
            if(adj[s][e]<=1e5){
            dist[s][e]=adj[s][e];
        }
    
        }
    }
    
    // 버텀업 dp 
    for(int k=1; k<=N; k++){
        for(int s=1; s<=N; s++){
            for(int e=1; e<=N; e++){
                dist[s][e]=min(dist[s][e],dist[s][k]+dist[k][e]);
            }
        }
    }
    
    for(int s=1; s<=N; s++){
        for(int e=1; e<=N; e++){
            
            // 주의 : 1e5도 유효한 값이므로, 
            // 모든 노드가 1e5라면, 1e5*100번 방문해서, 거리가 이렇게될수도!!
            // so, >=1e5는 안된다!
            if(dist[s][e]>=1e8){
                cout<<0<<" ";
            }else{
            cout<<dist[s][e]<<" ";
                
            }
        
            
        }
        cout<<"\n";
    }
    


  
    return 0;
}
    
    