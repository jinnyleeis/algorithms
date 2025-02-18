#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>
#include<set>
using namespace std;


const int MAX=200;
const int MAXCOLOR=20;

int dp[MAX][MAX]; 
// 특정 컬러로 바꾸는 것이 목표일 때, 변화 구간이 몇개 남았을 때, 바꾸는 최소 비용 
// 구간이 짧으면 그거 dp로 가져와서 사용하고!! - 실제로 어디 위치인지는 중요하지 않다!!

int N,K;

const int INF=1e9;

int colors[MAX];


// 일단 다 남았을 때, 최소 
vector<int> spots;




int main(){
    
    
    
    
    cin>>N >>K;
    for(int i=0; i<N; i++){
        cin>>colors[i];
        if(i>=1&& colors[i]!=colors[i-1])spots.push_back(colors[i-1]);
       
    }
     spots.push_back(colors[N-1]);
    
    int M=spots.size();
    

    
   // memset(dp,INF,sizeof(dp)); 
   // 제발.. memeset으로 inf 초기화 불가능하다ㅠㅠㅠ
    
  
   for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
         dp[i][j] = (i == j ? 0 : INF);
     
        }
    }

  for(int l=2; l<=M; l++){
      for(int i=0; i+l-1<M; i++){
          int j =i+l-1;
          for(int k=i; k<=(j-1); k++){
              int cost=spots[i]==spots[j]? 0 : 1;
            dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+cost);
          }
          
          
      }
  }
    
    cout<<dp[0][M-1]<<"\n";
    return 0;
}