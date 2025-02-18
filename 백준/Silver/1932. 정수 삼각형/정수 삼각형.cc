#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<limits>
#include<vector>
#include<set>
using namespace std;


const int MAX=500;

// 정수 삼각형 - 인덱스 기준을 정하자!!
/*
굳이 인덱스 복잡하게 할필요가 있나?.. 
걍, 삼각형 모양 유지안하고 왼쪽으로 밀자 모든층이 0부터 시작하게끔
*/

int N;
int dp[MAX][MAX]; 
int cost[MAX][MAX]; 
//직전까진 x-1번쨰 레벨까지 선택하고
// 이제 x번째 레벨에서 y를 선택했을 때, 얻을 수 있는 최대 비용


int fn(int level,int x){
    if(level==N)return 0; // n-1까지가 범위. N부턴 얻을 수 있는 비용이 없음!!
    if(x<0||x>level)return 0; // 오버플로우!! -불가능한 경우 
    if(dp[level][x]!=-1)return dp[level][x];
    
    int res=max(fn(level+1,x),fn(level+1,x+1))+cost[level][x];
   
    return dp[level][x]=res;
    
}

int main(){
    
    memset(dp,-1,sizeof(dp));
    
    cin>>N;
    for(int i=0; i<N; i++){
        for(int j=0; j<=i; j++){
            cin>>cost[i][j];
        }
        
    }
    // 0번쨰 레벨에선 0번쨰 밖에 선택할게 없다!!
    cout<<fn(0,0)<<"\n";


    return 0;
}