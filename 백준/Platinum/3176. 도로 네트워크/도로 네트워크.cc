#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>

using namespace std;

const int MAX= 1<<17;
const int MAXP=17;
const int INF=1e9;


typedef pair<int,int> pii;

// 2^(logMAX)승, 2^0승부터
int parent[MAX+1][MAXP+1];
pii value[MAX+1][MAXP+1]; // min , max 저장하기 
int depth[MAX+1];
vector<pii> adj[MAX+1];  // 이건 pq 쓸거 아니므로, 걍 next, weight 순으로 저장하자. 
// tree는 양방향이므로, 양방향 저장하기 

int N,K;
int root;



void initFirstParent(int cur){
    for(auto next : adj[cur]){
        if(depth[next.first] != -1) continue;  // 이미 방문한 노드이면 건너뛰기
        depth[next.first] = depth[cur] + 1;
        parent[next.first][0] = cur;
        value[next.first][0] = pii(next.second, next.second);
        initFirstParent(next.first);
    }
}



pii lca(int a,int b){
    
    // 일단 b가 a보다 위에 있는 걸로 맞추자. 
    if(depth[a]<depth[b]){
        int temp=a;
        a=b;
        b=temp;
    } 
    
    // 그러고, depth 맞추기 탐색 들어간다. 
    int diff=depth[a]-depth[b];
    
    int k=0;
  ///  int temp=2;
    // a를 점프 시킨다!!!
    
    /// 일단 diff라는 수만큼 점프해야 한다는 것은 암.
    
    int minres=INF;
    int maxres=0;
    // 근데 이걸, log(diff)만에 수행하려고 하는 것임 
    
    while(diff){
        
        // a가 b와 같은 depth로 점프해서 도달하기 이전까지 아래의 작업을 수행 
        // 이게, 2^0+ 2^1 + 2^2 // a의 2^0번째 부모의 2^0번째 부모는, a의 2^1번쨰 부모가 되는 것이므로, 
        // 결국 이진수의 자릿수-> 십진수로 바꾸는 과정과 동일하다. 
        // 그렇기 때문에 아래는, diff라는 10진수를 2진수로,
        // least significant bit ~-> most significant bit의 자릿수까지 조사하는 과정임 
       if(diff%2==1){
        //  cout<<a<<parent[a][k]<<"\n";
           minres=min(minres,value[a][k].first);
           maxres=max(maxres,value[a][k].second);
           a=parent[a][k]; // 주의 얘가 밑에 있어야!! 그래야, a~ a의 2^k번쨰 부모 사이의 엣지들 탐색 가능
           // 이거 순서 잘못 썼더니, 1,2의 min/max가 00이 나왔음!!!
         //  cout<<a<<parent[a][k]<<"ddd"<<"\n";
       }
       diff/=2;
    // temp=temp*2;
    // 2의 몇승이 필요한건 아니므로, temp를 버리자. pow 구현할때 temp가 필요한 것임 
       k++; // k를 증가시킨다!!
       
    }
    // 여기까지 거치고 나면 depth가 동일해짐 
    // depth 동일해졌는데, 같은 노드면, 바로 리턴!!!!
    
  
    
    if(a!=b){
        
       for(int k=MAXP; k>=0; k--){
           if(parent[a][k]!=parent[b][k]){
               
               
         
               minres=min(minres,min(value[b][k].first,value[a][k].first));
               maxres=max(maxres,max(value[b][k].second,value[a][k].second));

               // 여기도 제발 점프 전에 min/max
              a=parent[a][k];
              b=parent[b][k];
               
           }
           
           
           
       }
        
        
       minres=min(minres,min(value[a][0].first,value[b][0].first));
       maxres=max(maxres,max(value[a][0].second,value[b][0].second));
       
        
        
        
    }
    
    return pii(minres,maxres);
    
}


void initDP(int N){
    
    
   // dp를 init하는 것은, 2^0번째 부모가 채워진 상태에서 진행된다. 
   // 그런데, 주의할 것은, 루트는 2^0번째 부모도 없을 거란 말임 
   // 아 아예, root는 cur 대상에서 제외해 
   
   // so, parent가 -1이 아닐 때만, 해당 노드를 n(cur)노드로 해서, dp 배열의 column 값을 채워나가자!!
   // k가 밖이여야!! 모든 i에 대해,  k=0이 먼저 채워져있어야 하므로!k0이 다 채워질 때까진 다음으로 증가xx
       for(int k=1; k<=MAXP; k++){
           for(int i=2; i<=MAX; i++){
           // 동일 i면, k-1번째 까지 가능하다. 
           int directParent=parent[i][k-1];
           if(directParent!=-1){ 
               // 이 조건을 건 이유는 모든 cur 노드에 대해서, 2^MAXP 까지 채워지는 것은 당연히 아니므로 
           parent[i][k]=parent[directParent][k-1];
           value[i][k].first=min(value[i][k-1].first,value[directParent][k-1].first);
           // k-1까지 채워진 상태니까, k-1까진 이용 가능. 그 이상부턴 이용 불가능하다.(k~~)
           value[i][k].second=max(value[i][k-1].second,value[directParent][k-1].second);
        //   cout<< parent[i][k]<<" "<<value[i][k].first<<" "<< value[i][k].second<<"\n";
           }
       }
       
   }
 
    
    return;
    
    
}




int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
   
  // cout<<"d"<<"\n";
    cin>>N;
   // cout<<N<<"\n";
    
    for(int i=0; i<(N-1); i++){
        int a,b,c;
        cin>> a >> b >> c;
     //   cout<<a<<b<<c<<"dd"<<"\n";
        /// 몇번째 노드 부터가 1번인지 주어지지 않았으므로, 안전하게 루트 노드를 처음 주어진 노드의 번호로 설정했다. 
      
        adj[a].push_back(pii(b,c));
        adj[b].push_back(pii(a,c));
    }
    
    memset(depth,-1,sizeof(depth));
    memset(parent,-1,sizeof(parent));
    // value는 굳이 초기 세팅 할 필요 없을듯
    
    
    cin>>K;
   // cout<<K<<"\n";
    
    root=1;
    depth[root]=0; // depth의 루트를 1부터 들어가자.
    initFirstParent(root);
   
    initDP(N);

    
    
    for(int i=0; i<K; i++){
        int a,b;
        cin>>a>>b;
        pii result=lca(a,b);
        cout<<result.first<<" "<<result.second<<"\n";
    }
 
    

    return 0;
}