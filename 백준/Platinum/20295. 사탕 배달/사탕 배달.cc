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

vector<int> adj[MAX+1];

int candyAble[6];
int candy[MAX+1];
int depth[MAX+1];

int parent[MAX+1][18];
int canBuy[MAX+1][18][6];

void buildTree(int cur){
    
    for(auto child : adj[cur]){
        if(depth[child]!=-1)continue;
         depth[child]=depth[cur]+1;
         parent[child][0]=cur;
        // cout<<"parent "<<cur<<"child "<<child.first<<"weight "<<child.second<<"\n";
         canBuy[child][0][candy[cur]]=1; // child의 2^0번쨰 부모에선 Cur캔디를 살 수 있다
         canBuy[child][0][candy[child]]=1;
         buildTree(child);
        }
        
    }
    

void initDP(){
    
    
    for(int k=1; k<=17; k++){
        for(int n=2; n<=MAX; n++){
            if(parent[n][k-1]!=-1){
            parent[n][k]=parent[parent[n][k-1]][k-1];
            for(int i=1; i<=5; i++){
                canBuy[n][k][i]=canBuy[n][k-1][i]||canBuy[parent[n][k-1]][k-1][i];
            // 둘 중 하나라도 1이면, 가능!!
            }
            
           

            }
            
        }
    }
    
    
}

int lca(int a,int b,int candyType){
    
    // 목적지, 출발지 동일한 경우, 이런 식으로 처리
   if(a==b){
       return candy[a]==candyType ? 1:0;
   }
   // b를 더 높게!!
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
 
  int canbuy=0;// 결과를 담을 변수!!
  
  while(diff){
      if(diff%2){
          canbuy=canbuy||canBuy[a][k][candyType];
          a=parent[a][k];
      }
      diff/=2;
      k++;
      
  }
  
  if(a==b)return canbuy; // 이렇게 했는데 공통 조상이면, 하나를 리턴한다!!
  if(canbuy)return canbuy; // 살 수 있으면, 굳이 더 탐색할 필요xxx
  
  
  // 17을 max로 잘못 했더니, 잘못 나왔다!!! - 즉, 배열에 존재하지 않는 값이였던 건데 흠
  for(int k=17; k>=0; k--){
      if(parent[a][k]!=parent[b][k]){
         canbuy=canbuy||canBuy[a][k][candyType]||canBuy[b][k][candyType];
          a=parent[a][k];
          b=parent[b][k];
          if(canbuy)return canbuy;
      }
  }
  
  // 이거 위치 a,b aprent로 바꾸기 전에썼어야!!
  canbuy=canbuy||canBuy[a][0][candyType]||canBuy[b][0][candyType];
  a=parent[a][0];
  b=parent[b][0];

  return canbuy;
}



int main(){
    
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin>>N;
    for(int i=1; i<=N; i++){
        int temp;
        cin>>temp;
        candy[i]=temp;
        candyAble[temp]=1;
    }
    
    for(int i=1; i<=N-1; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    memset(depth,-1,sizeof(depth));
    memset(parent,-1,sizeof(parent));
    memset(canBuy,0,sizeof(canBuy));
    
    
    
    
    depth[1]=0;
    buildTree(1);
    initDP();
    
     cin>>M;
     int start,dest,candyType;
    
    for(int m=1; m<=M; m++){
       
        cin>>dest>>candyType;
        if(m==1){
            // 2번쨰 쿼리를 위한 스타트지점!!
            start=dest;
           
            if(candyAble[candyType]){
                cout<<"PLAY"<<"\n";
            }else{
                cout<<"CRY"<<"\n";
            }
        }else{
            if(lca(start,dest,candyType)){
                cout<<"PLAY"<<"\n";
            }else{
                 cout<<"CRY"<<"\n";
            }
            // M==1이 아닐때도 시작지점 업데이트 해줘야!
             start=dest;
        }
    }
    
    
    
    return 0;
}