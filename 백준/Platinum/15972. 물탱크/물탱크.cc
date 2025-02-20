#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;

const int MAX = 1000;
const int MAX2=MAX*MAX;
const int INF=1e9;

int N,M,H;
typedef pair<int,int> pii;

int wallsinGaro[MAX+2][MAX+2]; 
// 세로벽 길이가 1000이면, 가로벽줄은 총 1001개일 것이므로,
// 인덱스 1부터 시작하려면 +2를 해야함 
int wallsinSero[MAX+2][MAX+2]; 


int waters[MAX+1][MAX+1]; // 내부의 칸을 의미 - 나중에 채워넣을 부분임 
// 일단 입력은 WALls에다 받음 

vector<pii> adj[MAX2+1];
int dist[MAX2+1]; 
int visited[MAX2+1]; 


int toIndex(int y,int x){
    return M*(y-1)+x;
    //M=3일시,
    // (0,1)이면, -> 0+1=2번쨰
    //(0,0)이면 -> 1번째
    // (1,2)면, -> 3*1+2=6번쨰 
}


void fn(int start){
    
    // 주의 : 다 연결된 컴폰너트 그래프가 아니므로, 고립된 컴포넌트별로 수행해야!!
     // toindex를 통해, 이웃한 노드까지 그래프로 세팅 완료 해놓았음!!! 
   // 이제, pq 돌면서, 다익스트라를 수행하자!!
   // 가중치 - current tank의 물의 높이 
   priority_queue<pii,vector<pii>,greater<pii>> q;
   
 //  cout<<"방문"<<"\n";
   // 시작을 제일 작은 애부터 해야 할 것 같다!!!!
   q.push(pii(dist[start],start));
  // cout<<start<<"\n";
  // cout<<dist[start]<<"\n";
  // cout<<"\n";
   // 일단 걍 첫번쨰 노드부터 시작!!!
   
   while(!q.empty()){
       
       int curheight = q.top().first;
       int cur=q.top().second;
       visited[cur]=1;
       q.pop();
       
       if(dist[cur]<curheight)continue;
       
       for(auto next:adj[cur]){
           int nextnode=next.first;
           int middleholeheight=next.second;
         //  visited[nextnode]=1;

           
         //  if(dist[nextnode]>middleholeheight){
               // 영향 주는게 가능한 것임!!!
               int newCost = max(curheight, middleholeheight);
               if(dist[nextnode] > newCost){
             //  dist[nextnode]=min(dist[nextnode],max(middleholeheight,curheight));
             // 이렇게 하면, 원래 자기 값이랑 같아도, 계속해서 삽입이 일어나므로, 무한루프에 빠지게된다!!
             // 즉, 현재 자신 보다 작은 cost를 current height과 Hole로부터 얻을 수 있을 때만 업데이트를 수행한다. 
                 dist[nextnode]=min(dist[nextnode],newCost);
                q.push(pii(dist[nextnode],nextnode));
           //   cout<<nextnode<<"-"<<dist[nextnode]<<"\n";
           
           }
           
          
       }
       
    
      
       
       
       
   }
   
   
    
    
}



int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin>>N>>M>>H; // 세로 길이 / 가로 길이 
    
  
    // i는 열기준!
   for(int i=1; i<=N; i++){
       for(int j=1; j<=M; j++){
           waters[i][j]=H;
           dist[toIndex(i,j)]=H;
         //  cout<<dist[toIndex(i,j)]<<"\n";
       }
   }
   // n-1, n 연결 m은 동일!!!
    for(int n=1; n<=N+1; n++){
        for(int m=1; m<=M; m++){
            cin>>wallsinGaro[n][m];
            if(wallsinGaro[n][m]!=-1){
            if(n==1){
                waters[n][m]=min(waters[n][m],wallsinGaro[n][m]);
                dist[toIndex(n,m)]=waters[n][m];
                //q.push(pii(waters[n][m],toIndex(n,m)));

            }else if(n==N+1){
                 waters[n-1][m]=min(waters[n-1][m],wallsinGaro[n][m]);
                  dist[toIndex(n-1,m)]=waters[n-1][m];
               //  q.push(pii(waters[n-1][m],toIndex(n-1,m)));
            }else{
                // 2~N까지
                // 내부 연결된 부분이라는 것임 
                int u=toIndex(n-1,m);
                int v=toIndex(n,m);
                adj[u].push_back(pii(v,wallsinGaro[n][m]));
                adj[v].push_back(pii(u,wallsinGaro[n][m]));
                
            }
            
            
            
            
            
          //  cout<<"("<<n<<" , "<<m<<") "<<"\n";
        }
        }
    }
    
    
     
        for(int n=1; n<=N; n++){
            for(int m=1; m<=M+1; m++){
            cin>>wallsinSero[n][m];
            if(wallsinSero[n][m]!=-1){
            if(m==1){
                // 주의 첨에 m-1말고, m 해버림 
                 waters[n][m]=min(waters[n][m],wallsinSero[n][m]);
                  dist[toIndex(n,m)]=waters[n][m];
               //  q.push(pii(waters[n][m],toIndex(n,m)));
            }else if(m==M+1){
                 waters[n][m-1]=min(waters[n][m-1],wallsinSero[n][m]);
                  dist[toIndex(n,m-1)]=waters[n][m-1];
                // q.push(pii(waters[n][m-1],toIndex(n,m-1)));
            }else{
                
                 // 2~M까지
                // 내부 연결된 부분이라는 것임 
                int u=toIndex(n,m-1);
                int v=toIndex(n,m);
                adj[u].push_back(pii(v,wallsinSero[n][m]));
                adj[v].push_back(pii(u,wallsinSero[n][m]));
                
            }
            
            
            }
           // cout<<"("<<m<<" , "<<n<<") "<<"\n";
        }
    }
    
    
    for(int i=1; i<=M*N; i++){
        if(visited[i]){
            continue;
        }
       // cout<<i<<"\n";
      fn(i);
    
    }

    
    int sum=0;
    for(int i=1; i<=M*N; i++){
       // cout<<i<<" : "<<dist[i]<<" ";
        sum+=dist[i];
    }
    cout<<sum<<"\n";
    
    

    return 0;
}

/*
2 3 5
1 -1 -1
3 2 -1
4 -1 2
-1 -1 4 3
-1 -1 -1 -1
(1 , 1) 
(1 , 2) 
(1 , 3) 
(2 , 1) 
(2 , 2) 
(2 , 3) 
(3 , 1) 
(3 , 2) 
(3 , 3) 
(1 , 1) 
(1 , 2) 
(2 , 1) 
(2 , 2) 
(3 , 1) 
(3 , 2) 
(4 , 1) 
(4 , 2) 


*/
