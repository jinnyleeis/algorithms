#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>
#include<set>
using namespace std;


const int MAX=1000;

// 정수 삼각형 - 인덱스 기준을 정하자!!
/*
굳이 인덱스 복잡하게 할필요가 있나?.. 
걍, 삼각형 모양 유지안하고 왼쪽으로 밀자 모든층이 0부터 시작하게끔
*/

int N,T;
int dp[MAX][MAX];  //이진 분할이니까, 근우만 신경써도 됨.  
int cards[MAX];
const int INF=1e9;
//직전까진 x-1번쨰 레벨까지 선택하고
// 이제 x번째 레벨에서 y를 선택했을 때, 얻을 수 있는 최대 비용
// turn이, e-s+1 
// n이 500일 때, 499,0 -> 500 근우 turn 


// n이 5일 때, 4-0+1 = 5 근우 turn

// 해봤자, Dp여서 각각의 구간 1번씩만 고려. 시간 복잡도 n^2(10^6) - 테케, 50개 5*10^7 세이프

int fn(int s,int e){
 //  if(s>e||e>=N)return 0; // 각각, fn(s+1,e)의 기저 / fn(s,e+1)의 기저에 해당!! 
 
 
  if(s==e){
       if(N%2==0){
       

           return 0;
       }else if(N%2==1){
           // 마지막은 근우일 것!!
            // dp[s][e]=cards[s];
        return cards[s];
       }
      
  }
  
    if(dp[s][e]!=-1)return dp[s][e];
    
    int turn=((e-s+1)%2 == N%2) ? 1:0; // 1이면, 근우, 0이면 명우 
    
    int gain1=0;
    int gain2=0;
    
    if(turn==1){
        gain1=cards[s];
        gain2=cards[e];
        dp[s][e]=max(fn(s+1,e)+gain1,fn(s,e-1)+gain2);
    
    }else{
        //
        // 명우도 남아있는 카드 중에서, 최선의 카드를 가져갈 것임을 고려하지 않았다!!!!
         gain1=0;
         gain2=0;
         // 즉, 명우의 차례일 땐, 자신이 젤 많이 가져갈 것을 고려, 즉, 근우가 min일 경우를 선택할 것임!!
         
    dp[s][e]=min(fn(s+1,e)+gain1,fn(s,e-1)+gain2);

         
    }
    // 근우의 turn일 때만 gain을 더한다!!
    // 제발 e는 다음이 e-1이다!!
   
    
    return dp[s][e];
    
}

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>T;
    for(int t=0; t<T; t++){
        
   memset(cards,0,sizeof(cards));
   
     cin>>N;
    for(int i=0; i<N; i++){
            cin>>cards[i];
        }

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
           
            dp[i][j]=-1;
        }
    }

    
  
        
       
        
    
    cout<<fn(0,N-1)<<"\n";
    
    }
    


    return 0;
}
