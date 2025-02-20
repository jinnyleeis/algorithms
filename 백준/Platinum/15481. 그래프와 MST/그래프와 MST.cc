#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include<cstring>
using namespace std;



const int MAX = 200000;
const int INF = 1e9;

typedef pair<int,int> pii;
typedef pair<pii,pii> edge;
//typedef pair<pii,pii> edge2;


int N,M;

vector<pii> trees[MAX+1];
int parent[MAX+1];

typedef long long ll;
// 각각은 int 가능.
// 합이 ll 필요.
ll totalW;
edge edges[MAX];




struct cmp{
    
    bool operator()(const edge &a, const edge &b){
        return a.first.first > b.first.first;
        
    }
        
        
};

    

priority_queue<edge,vector<edge>,cmp> q;

int dp[MAX+1][19];
int cost[MAX+1][19];
int depth[MAX+1];


void buildTree(int cur){
    
    for(auto child:trees[cur]){
        if(depth[child.first]==-1){
            depth[child.first]=depth[cur]+1;
            dp[child.first][0]=cur;
            cost[child.first][0]=child.second;
            buildTree(child.first);
        }
    }
    
    
}



void initDP(){
    
    for(int k=1; k<=18; k++){
        for(int i=2; i<=N; i++){
            int p=dp[i][k-1];
            if(p!=-1){
                dp[i][k]=dp[p][k-1];
                cost[i][k]=max(cost[p][k-1],cost[i][k-1]);
                
            }
            
        }
    }
    
    
}


int lca(int a,int b){
    
    // 뎁스
    if(depth[a]<depth[b]){
        swap(a,b);
    }
    
    int jump=depth[a]-depth[b];
    
    int step=0;
    int maxWeight=0;
    
    while(jump){
        
        if(jump%2){
            maxWeight=max(maxWeight,cost[a][step]);
            a=dp[a][step];
        }
        jump/=2;
        step++;
    }
    
    if(a==b)return maxWeight;
    
    for(int k=18; k>=0; k--){
        if(dp[a][k]!=dp[b][k]){
            maxWeight=max(maxWeight,max(cost[b][k],cost[a][k]));
            a=dp[a][k];
            b=dp[b][k];
        }
    }
    
    maxWeight=max(maxWeight,max(cost[b][0],cost[a][0]));
    a=dp[a][0];
    b=dp[b][0];
    
    return maxWeight;
}




int find(int x){
    if(parent[x]<0)return x;
    
    int notRootParent=parent[x];
   // int rootParent=find(parent[notRootParent]);
   parent[x]=find(notRootParent);
   // 건너띄어 버림!!! 
    // root의 직전 자식까지, 인자로 들어갈 것이다!!
    // 그러고 걔는 if에서 걸려서 나갈 것이다. 
    // 루트가 들어갈 일은 없음 - 즉, 여기까지 왔다는 것은 루트의 손자/손녀임 
    // 직전 자식일 리는 없음 그래서 변수명 적절함 
    return parent[x];
}

void unions(int a,int b){
    
    int rootA=find(a);
    int rootB=find(b);
    
    if(rootA==rootB)return;
    if(parent[rootA]<parent[rootB]){
        // a의 자식수가 더 많은 것임 -음수 절댓값 
        swap(rootA,rootB);
    }
    
    // rootA의 자식 수를, rootB에서 관리할 수 있도록!!
    parent[rootB]+=parent[rootA];
   // cout<<parent[rootB]<<"\n";
    // a를 b의 서브 트리로 합치자.
    parent[rootA]=rootB;
    
    // path compression은 넘 복잡하니까 수행하지 말자 일단 
}


void kruskal(){
    
    int numE=0;
   
    
    // q에 일단 다 push해놔야 한다!
    while(numE<N-1 && !q.empty()){
        
        edge e = q.top();
        
        int edgenum = e.first.second;
        int u = e.second.first;
        int v = e.second.second;
        int w=e.first.first;
   
        q.pop();
        
        if(find(u)==find(v)){continue;}
        unions(u,v);
        
        // 어떤 엣지가 MST에 포함되어 있는지를 저장한다! 
         trees[u].push_back(pii(v,w));
         trees[v].push_back(pii(u,w));
         
         edges[edgenum].first.second=-1;
      
        
        totalW+=w;
        numE++;

    }
    
    
    
}




int main(){
   ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(NULL);
    
    cin>>N>>M;
    for(int i=0; i<M; i++){
        int u,v,w;
        cin>>u>>v>>w;
        
        q.push(edge(pii(w,i), pii(u,v)));
        edges[i]=edge(pii(w,i), pii(u,v));
    }
    
    memset(parent,-1,sizeof(parent));
    memset(depth,-1,sizeof(depth));
    memset(dp,-1,sizeof(dp));
    memset(cost,-1,sizeof(cost));

    
    kruskal();
    
    depth[1]=0;
    buildTree(1);
    
    initDP();
    
    for(int i=0; i<M; i++){
        
        edge e= edges[i];
        int w=e.first.first;
        int isMST=e.first.second;
        int u=e.second.first;
        int v=e.second.second;
        
        if(isMST==-1){
            cout<<totalW<<"\n";
        }else{
            
            int maxEdge=lca(u,v);
            cout<<totalW-maxEdge+w<<"\n";
        }
        
        
    }
    
 
    
    return 0;
}
