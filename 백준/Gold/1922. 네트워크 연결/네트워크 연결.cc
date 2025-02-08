#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
#include <queue>
using namespace std;


// 2*10^8

/*

N = 10^3 M=10^5

Union-Find 알고리즘은 O(1) 즉 상수 시간 복잡도를 가지기 때문에
-> parent 배열 만들어서, o(1)로 참고할 수 있게? 

간선을 정렬하는 로직이 전체 시간 복잡도를 좌우하게 되는데,

가장 일반적인 퀵 정렬을 예로 들면, 
퀵 정렬의 시간 복잡도인 O(ElogE)가 크루스칼 알고리즘의 시간 복잡도가 된다.

//E : 간선의 개수

//V : 정점의 개수

10^5log10^5 -> 시간 복잡도 널널!!

*/
// 특정 x - y 점의 - 가중치 


int totalW;
int totalE;

int N,M;
int parent[1001]; // 직속 parent - 루트 말고 
// is greater가 아니라, 그냥 greater임

struct edge{
    
    int x;
    int y;
    int weight;
    
};

typedef struct edge edge;

// priority_queue <T,vector<T>,compare> pq;
// compare = 우선 순위를 어떻게 정하느냐를 정의한 구조체
//  edge 구조체의 우선 순위를 재정의 하기 때문에, edge 구조체 대장체를 인자를 2개 

struct cmp{
    
    // 오름차순 정렬 하고 싶으면, e2<e1면 true 리턴하게 sort랑 
    // 반대로 작성해야!! - 주의 
    bool operator()(edge &e1,edge &e2){
        if(e1.weight >= e2.weight){
            return true;
        }else{
            return false;
        }
    }
};

priority_queue<edge,vector<edge>, cmp> q;


int find(int a){
    if(parent[a]==a)return a;
  
    return find(parent[a]);
};



void unionfn(int a, int b){
    int rootA=find(a);
    int rootB=find(b);
    
    if(rootA==rootB){
        return;
    }
   // parent[rootB]=a; // rootB의 부모를 a로 업데이트!!
   //a가 아니라, rootA!!
    parent[rootB]=rootA;
    
    return;
};

int main(){
    cin>>N;
    cin>>M;
    
    for(int i=0; i<M; i++){
        int x,y,cost;
        cin>>x>>y>>cost;
        edge temp;
        temp.x=x;
        temp.y=y;
        temp.weight=cost;
        q.push(temp);
        
    }
    
    
    
    // mst - 크루스칼로 수행하기
    
    
    // 일단 트리의 부모 배열 다 자기 자신으로-> 지금 다 disjoint set의 상태이다.
   for(int i=0; i<=N; i++){
       parent[i]=i;
   }
   
   while(totalE<(N-1)){
       
       edge curMinEdge = q.top();
       q.pop();
       
    //   if(parent[curMinEdge.x]!=parent[curMinEdge.y]){
    // 주의 parent는 직속 부모를 저장하고 있다!! find를 씌워서 루트를 찾아야 할 것이다!!!
    
         if(find(curMinEdge.x)!=find(curMinEdge.y)){

           // 아직 연결 되지 않음 
       unionfn(curMinEdge.x,curMinEdge.y);
           
        // 같으면, 이미 연결된 것이므로, 해당 엣지는 버려진다!
       totalW+=curMinEdge.weight;
       totalE++;
           
       }
       
       
   }
    
    cout<<totalW<<"\n";
  
    return 0;
}