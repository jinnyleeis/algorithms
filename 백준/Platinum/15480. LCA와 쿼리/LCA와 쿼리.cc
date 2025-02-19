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
int N,M;
typedef pair<int,int> pii;
vector<int> adj[MAX+1];

int depth[MAX+1];

int parent[MAX+1][18];

void buildTree(int cur){
    
    for(auto child : adj[cur]){
        if(depth[child]!=-1)continue;
         depth[child]=depth[cur]+1;
         parent[child][0]=cur;
         buildTree(child);
        }
        
    }
    

void initDP(){
    
    
    for(int k=1; k<=17; k++){
        for(int n=2; n<=MAX; n++){
            if(parent[n][k-1]!=-1){
            parent[n][k]=parent[parent[n][k-1]][k-1];
           

            }
            
        }
    }
    
    
}

int lca(int a,int b){
    
  if(depth[a]<depth[b]){
      int temp;
      temp=b;
      b=a;
      a=temp;
  }
  
  // depth 맞추기! - a to b까지 양방향 경로 다 탐색해야 하는 것이므로 필요!
  int diff=depth[a]-depth[b];
  
  int k=0; // 얘는 작 to 큰임!!- diff 10진수를 이진수로 만들 때 lsb to msb로 만들어서
  // depth를 맞추는게 맞으므로!!
 

  while(diff){
      if(diff%2){
          a=parent[a][k];
      }
      diff/=2;
      k++;
      
  }
  

  if(a==b)return a;
  
  // 17을 max로 잘못 했더니, 잘못 나왔다!!! - 즉, 배열에 존재하지 않는 값이였던 건데 흠
  for(int k=17; k>=0; k--){
      if(parent[a][k]!=parent[b][k]){
          a=parent[a][k];
          b=parent[b][k];
          
      }
  }
  
  a=parent[a][0];
  b=parent[b][0];

  return a;
}



int main(){
    
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin>>N;
  
    for(int i=1; i<=N-1; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    memset(depth,-1,sizeof(depth));
    memset(parent,-1,sizeof(parent));

    
    depth[1]=0;
    buildTree(1);
    initDP();
    
     cin>>M;
    
    for(int m=1; m<=M; m++){
       int r,u,v;
       cin>>r>>u>>v;
       set<int> s;
       int a=lca(r,u);
       int b=lca(r,v);
       int c=lca(u,v);
       pii temp[]={pii(depth[a],a),pii(depth[b],b),pii(depth[c],c)};
       sort(temp,temp+3);
       // 1 -> 2 -> 3 일시, 2 맞음 
       // 1 -> 1 -> 2 일시, 2여야
       // 1 -> 1 -> 1 일시, 다 상관없음 - 이럴 일이 없겠지??.... 
       // 루트랑 동일한 레벨인 애는 루트가 유일하니까.. 무조건 3개중 하나는 루트일 것이므로 a bb or a bc 케이스 밖에 없을 것임 
       
       if(temp[0]==temp[1]){
           cout<<temp[2].second<<"\n";
       }else{
           cout<<temp[1].second<<"\n";
       }
   
        
    }
    
    
    return 0;
}