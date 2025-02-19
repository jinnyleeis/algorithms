#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>
#include<set>

using namespace std;


const int MAX=100000;
const int INF=1e9;
int N;
typedef pair<int,int> pii;

vector<pii> adj[MAX+1];

int power[MAX+1];
int depth[MAX+1];

int parent[MAX+1][18];
int cost[MAX+1][18];

void buildTree(int cur){
    
    for(auto child : adj[cur]){
        if(depth[child.first]!=-1)continue;
         depth[child.first]=depth[cur]+1;
         parent[child.first][0]=cur;
        // cout<<"parent "<<cur<<"child "<<child.first<<"weight "<<child.second<<"\n";
         cost[child.first][0]=child.second;
         buildTree(child.first);
        }
        
    }
    

void initDP(){
    
    
    for(int k=1; k<=17; k++){
        for(int n=2; n<=MAX; n++){
            if(parent[n][k-1]!=-1){
                  //  cout<<"in";
            parent[n][k]=parent[parent[n][k-1]][k-1];
            //cost[n][k]=cost[cost[n][k-1]][k-1];
            cost[n][k]=cost[n][k-1]+cost[parent[n][k-1]][k-1];
         //   cout<<cost[n][k]<<"\n";
            }
            
        }
    }
    
    
}

int lca(int ant){
    
   // cout<<"in";
    if(ant==1)return 1;
    // depth 맞출 필요없다!! 
    // 최대한 어디까지 올라갈 수 있는지를 희소 배열로 log n만에 수행하는게 목표이므로
    int leftPower=power[ant];
    for(int k=17; k>=0; k--){
        // 주의 : 남은 에너지가 0일경우도 이동 가능해야 한다!!!
        if((leftPower-cost[ant][k])>=0){
         //   cout<<leftPower<<"\n";
            leftPower=leftPower-cost[ant][k];
            ant=parent[ant][k];
            
        }
        
    }
    
   // if(ant==-1)return 1;
    return ant;
    
}



int main(){
    
    
    cin>>N;
    for(int i=1; i<=N; i++){
        
        cin>>power[i];
    }
    
    for(int i=1; i<=N-1; i++){
        int a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back(pii(b,w));
        adj[b].push_back(pii(a,w));
    }
    
    memset(depth,-1,sizeof(depth));
    memset(parent,-1,sizeof(parent));
    
    for(int i=0; i<=MAX; i++){
        for(int j=0; j<=17; j++){
            cost[i][j]=INF;
        }
    }

    

    
    depth[1]=0;
    buildTree(1);
    initDP();
    
    for(int n=1; n<=N; n++){
        cout<<lca(n)<<"\n";
    }
    
    
    
    return 0;
}