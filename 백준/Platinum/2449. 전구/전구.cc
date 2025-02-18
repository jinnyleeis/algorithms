#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>
#include<set>
using namespace std;


const int MAX=200;

int dp[MAX][MAX]; 


int N,K;

const int INF=1e9;

int colors[MAX];




// 구간 곱 최소 비용 

int main(){
    
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            // 구간 1인건 여기서 처리됨
            dp[i][j]= ((i==j) ? 0 : INF);
        }
    }
    
    cin>>N>>K;
    
    for(int i=0; i<N; i++){
        cin>>colors[i];
    }
    
    
    for(int len=2; len<=N; len++){
        int lastIndex=(N-1);
        // 주의 3-3=0이다. 안헷갈리게  s<=lastIndex-len+1 이거 말고,
        for(int s=0; s + (len - 1) < N; s++){
            int e=s+len-1;
            
            //1개 1개 -> 총 2개 ~~~ N개(0부터~n-1까지)
            for(int k=s; k<=(e-1); k++){
                
                int cost= (colors[s]==colors[k+1]) ? 0: 1;
                dp[s][e]=min(dp[s][e], dp[s][k]+dp[k+1][e]+cost);
            }
            
        }
    }
    
    cout<<dp[0][N-1]<<"\n";
    return 0;
}