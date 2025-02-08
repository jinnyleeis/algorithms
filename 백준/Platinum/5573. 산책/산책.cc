#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;


int H, W;
long long N;
long long dp[1004][1004];   
int arr[1004][1004];      
int finaly=0,finalx=0;

void followPath(int y, int x){

// 1)
if(y==H || x==W){
    finaly=y,finalx=x;
    
    return;
}


// by 1) + 가능한 이동 방향 때문에, 별도의 오버플로우 처리가 필요없음


// 재귀 메인 로직 
 if(arr[y][x]==0){
     followPath(y+1,x);
     
 }else if(arr[y][x]==1){
      followPath(y,x+1);
 }


return;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    memset(dp,-1,sizeof(dp));
    
    // 입력
    cin >> H >> W >> N;
    
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            cin >> arr[i][j]; // 0='아래', 1='오른쪽'
        }
    }
    
    // N-1번째 산책을 한 결과 만들어진 산책로의 상태
    // 즉, N번쨰 산책을 할 산책로의 모습을 dp로 담아놓자.
    
    dp[0][0]=N-1;
    
    
    
    //인덱스 00부터 시작해야 하는 이유, 
    // 그럴때 미리 구해놓은 기저 00이 안망가지게 continue 포함하는 것 잊지 말것
    // * 주의 0 사용하면 i-1/ j-1일떄 처리 제대로 해줘야. 단축 평가 사용하기 이럴땐
    // 그리고 인덱스 복붙할때 x/y 혼동 안했는지 체크 주의
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
    if(dp[i][j]!=-1)continue;
    
    int leftCnt=0,upCnt=0;
    // 초기값이 '아'이면, 
    if(((i-1)>=0) && arr[i-1][j]==0){
        
        leftCnt=dp[i-1][j]/2+dp[i-1][j]%2;
        
        // 초기값이 '오'이면,
    }else if( ((i-1)>=0) && arr[i-1][j]==1){
        leftCnt=dp[i-1][j]/2;
        
    }
    
    
    // 초기값이 '아'이면,
    if(((j-1)>=0) && arr[i][j-1]==0){
        upCnt=dp[i][j-1]/2;
        
        // 초기값이 '오'이면,
    }else if(((j-1)>=0) && arr[i][j-1]==1){
        upCnt=dp[i][j-1]/2+dp[i][j-1]%2;
        
    }
    dp[i][j]=leftCnt+upCnt;
            
        }
    }
    
    
    // 업데이트된 dp를 바탕으로 초기값으로 세팅되어 있는 산책로를 업데이트
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            arr[i][j]=(arr[i][j]+dp[i][j]%2)%2;
            // 정확한 방문횟수가 아니라, 
            // 방문횟수가 짝수인지 홀수인지에 따라 업데이트만 진행하면 되므로,
            // dp[i][j]가 아닌, dp[i][j]%2를 더해준다!!
        }
    }
    
    
    // 업데이트된 산책경로를 따라 탐색 시작 -> 종료 지점의 좌표 구하기 
    followPath(0,0);
    
    // 주의 +1해야하는 이유 실제 문제에선 좌표가 1부터 시작하는 걸로 가정했으므로 
    cout<<finaly+1<<" "<<finalx+1<<"\n";

    return 0;
}