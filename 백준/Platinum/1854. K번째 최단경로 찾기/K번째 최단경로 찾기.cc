
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;


typedef pair<int,int> pii;

const int INF=1e9;
const int MAX=1001;
int dist[MAX];
int visited[MAX];
vector<pii> adj[MAX];
int answer[MAX];
int n,m,k;

struct cmp{
    bool operator()(const pii& a, const pii& b){
        // 5 4 3 2 1 -> 1 2 3 4 5 
       return a.first > b.first;
    }
};



priority_queue<pii,vector<pii>,cmp> q;




int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m>>k;
    for(int i=0; i<m; i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(pii(c,b));
    }
    
    fill(dist,dist+MAX,INF);
    memset(answer,-1,sizeof(answer));
    
    dist[1]=0;
    q.push({0,1});
    while(!q.empty()){
        int curCost= q.top().first;
        int curNode=q.top().second;
        q.pop();
      //  cout<<curNode<<"\n";
        
        visited[curNode]++;
        if(visited[curNode]==k){
         //   cout<<"\n";
         //   cout<<curNode<<curCost<<"\n";
        answer[curNode]=curCost;
        }
        if(visited[curNode]>k)continue;
        
        
        
        
        
        // 조건x...
        for(auto next:adj[curNode]){
            
        //if(visited[next.second]>=k)continue;
            int curToNextEdge=next.first;
            int nextNode=next.second;
            int startToNext=curCost+curToNextEdge;
            
          ///   if(visited[nextNode]>=k)continue;
             dist[nextNode]=startToNext;
           // if(dist[nextNode]>startToNext){
        //   if(visited[nextNode]==k-1){
        //       ans.push_back(pii(nextNode,dist[nextNode]));
        //   }
        
             q.push(pii(startToNext,nextNode));
            //  visited[curNode]++;
           //    
           
            
        }
        
    }
    
    for(int i=1; i<=n; i++){
        if(answer[i]==-1){
            cout<<-1<<"\n";}
        else{
        cout<<answer[i]<<"\n";}
    }
   

    return 0;
}