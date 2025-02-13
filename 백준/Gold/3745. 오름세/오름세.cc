
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;


typedef pair<int,int> pii;
typedef long long ll;
int n;
const int MAX=(1<<17); // 십만은 이걸로 잡자 10^5 

int tree[2*MAX+1]; //+1은 루트노드는 1부터 시작할 것이므로.
int a[MAX];

struct cmp{
    
    bool operator()(const pii& a, const pii& b){
        
        // 값이 같으면, 인덱스 큰거 먼저 리턴되게끔
        // 1 2 3 4 5 -> 5 4 3 2 1
        if(a.first==b.first)return a.second < b.second; 
        return a.first > b.first; // 값 작은 것  먼저 리턴 되게끔 
        
    }
    
};


void update(int idx,int val){
    
    int treeidx=idx+MAX-1; //전처리 후 인덱스
    tree[treeidx]=val; 
 //   cout<< tree[treeidx]<<"\n";
    
    while(treeidx>1){
        treeidx/=2;
        tree[treeidx]=max(tree[treeidx*2],tree[treeidx*2+1]);
        
    }
    
    
    
}



 // range query l=1로 고정. r만 달라짐 
 int rangequery(int l,int r){
     
     l=l+MAX-1;
     r=r+MAX-1-1; // x가 주어지면, 
     // 실제로는 그 이전인 x-1까지의 최장 부분 수열의 길이가 필요한 것이므로 -1을 더 추가했다!!
     int res=0;
     // 아직 필요 범위내, 조사하지 않은 구간이 남아있을 때까지 
     //**전처리 전 인덱스 값이 주어지면, 보통 리프 노드 부터 탐색한다. 
     while(l<=r){
         
      // 
         if(l%2==1){
             // 최소 구간 노드가 오른쪽 노드라면, 해당 노드의 부모 노드는 out of range임 
             // 범위 '내' 한 depth 높은 노드로 올라갈 수 있게, +1을 해주고 2를 나눔 
             // 근데 그전에 우선 해당 인덱스 값 활용하는게 먼저임을 잊지 말자 
            res = max(res, tree[l]);
             l++;
         }
         
        if(r%2==0){
            // 최대 구간 노드가 왼쪽 노드라면, 해당 노드의 부모 노드는 out of range임 
             // 범위 '내' 한 depth 높은 노드로 올라갈 수 있게, -1을 해주고 2를 나눔
             // 그전에 값 활용 먼저!!
             res = max(res, tree[r]);
             r--;
        }
        
         l/=2;
         r/=2;
             
         }
         
         
     return res; // 수행 후 해당 범위 내 최댓값을 return 한다. 
     
     
 }


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while(cin>>n){
    memset(tree,0,sizeof(tree));
    priority_queue<pii,vector<pii>,cmp> q;
    for(int i=1; i<=n; i++){
        
        int num;
        cin>>num;
        q.push(pii(num,i));
        
    }
    
    while(!q.empty()){
        int cost=q.top().first;
        int idx=q.top().second;
        q.pop();
        int x;
        x=rangequery(1,idx); 
        update(idx,x+1);
    }
    
    cout<<tree[1]<<"\n"; // 루트 노드 값 출력
    }
    

    return 0;
}