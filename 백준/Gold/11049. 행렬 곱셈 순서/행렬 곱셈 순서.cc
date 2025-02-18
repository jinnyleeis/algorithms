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
typedef pair<int,int> pii;
pii matrix[MAX];
const int INF=1e9;
//직전까진 x-1번쨰 레벨까지 선택하고
// 이제 x번째 레벨에서 y를 선택했을 때, 얻을 수 있는 최대 비용


int fn(int s,int e){
    if(s==e)return 0; // 구간 사이즈가 1이면  - 행렬 하나이므로, 곱셈비용 없음 
    if(dp[s][e]!=INF)return dp[s][e];
    
    for(int k=s; k<=e-1; k++){
        int cost=(matrix[s].first*matrix[k].second*matrix[e].second);
       dp[s][e]=min(dp[s][e],fn(s,k)+fn(k+1,e)+cost);
        
    }
    
    
    return dp[s][e];
    
}

int main(){
    
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            dp[i][j]=INF;
        }
    }
    
    cin>>N;
    for(int i=0; i<N; i++){
            cin>>matrix[i].first>>matrix[i].second;
        }
        
    
    // 0번쨰 레벨에선 0번쨰 밖에 선택할게 없다!!
    cout<<fn(0,N-1)<<"\n";


    return 0;
}