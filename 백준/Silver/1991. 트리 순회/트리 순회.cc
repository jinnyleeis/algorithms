#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;



int N;

struct node{
  
 // int idx; - 필요없음 
 // - 순회는 인덱스 기준으로 하는게 아니라, 자식-부모 관계를 기준으로 하는 것임
//  int val;
//val도 필요없음 - 입력 순서를 인덱스로 해서기억할 필요가 없음 
// - 대신 인덱스를 해당 알파벳의 순서로 설정해야

  int left=-1;
  int right=-1; 
  
};


node a[27]; // full bt 아니면, 배열의 인덱스 방식을 활용하지 말자!!

// 기준 루트를 ~어디에
// 1. 전위 1 - > 2 -> 3 
// 2. 중위 2 -> 1 -> 3
// 3. 후위 2 -> 3 -> 1 

void pre(int nodeidx){
    if(nodeidx==-1)return;
    char temp=nodeidx+'A';
    cout<<temp;
    
    int leftidx = a[nodeidx].left; 
    int rightidx = a[nodeidx].right;
    pre(leftidx);
    pre(rightidx);
    
}

// 자식이 0인 건 없으므로(A에 이게 대응되므로!), left,right가 0이면 자식이 없다고 보면됨 

void in(int nodeidx){
    if(nodeidx==-1)return;

    
    int leftidx = a[nodeidx].left; 
    int rightidx = a[nodeidx].right;
    in(leftidx);
    
     char temp=nodeidx+'A';
     cout<<temp;
     
    in(rightidx);
    
}


void post(int nodeidx){
    if(nodeidx==-1)return;
  
    
    int leftidx = a[nodeidx].left; 
    int rightidx = a[nodeidx].right;
    post(leftidx);
    post(rightidx);
    
    char temp=nodeidx+'A';
    cout<<temp;
    
}

int main(){
    
    cin>>N;
    
  
    
    for(int i=0; i<N; i++){
        char p,l,r;
        cin>>p>>l>>r;
        if(l!='.'){
      //  a[i].val=p-'A'; // A면 0번 - 각각의 알파벳을 가리키게. 
       a[p-'A'].left=l-'A'; // b면 1번 
        }
        
        if(r!='.'){
       a[p-'A'].right=r-'A';// c면 2번 
        }
    }
    
    pre(0);
    cout<<"\n";
    in(0);
    cout<<"\n";
    post(0);
    
    
    
    return 0;
}
