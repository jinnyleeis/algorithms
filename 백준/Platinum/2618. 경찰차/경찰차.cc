#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// i번쨰 아이템부터~끝까지 아이템 고려할떄, w의 무게가 남았을 떄, 얻을 수 있는 최대 비용 
// 기저  남은고려할 아이템 수가 0개일 떄(다 고려했을 때, 남은 무게가 0일떄 - 더 이상 다른 아이템 조사 불가) 

int dp[1001][1001]; // 해당 두 경찰차가 처리한 직전 사건이 이러할 때, 남은 사건들을 처리할 수 있는 최소 비용 
int choice[1001][1001]; 
// 해당 상태일 때, 최소 비용을 얻기 위해서, 다음 출동할 경찰차로 선택한 경찰차의 번호 
typedef pair<int,int> pii;
pii query[1001]; // 사건 정보 
int W,N;
int fn(int p1, int p2){
    
    // 두 경찰차 중 아무나 마지막 사건 조사 맞춘 이후일 떄(w번째 사건이 마지막 사건임)
    if(p1==W||p2==W)return 0;//주의! 기존에 처리한 사건이므로, w+1이 아니라, w일떄가 알맞은 종료 조건일 것이다!!
    // w+1번쨰 사건은 없으므로, 현재 사건 처리 비용 0일 것임 
    if(dp[p1][p2]!=-1)return dp[p1][p2];
    int thisCase=max(p1,p2)+1; // 이번에 처리해야할 사건의 쿼리번호 
    // 이전 사건 장소에 위치해 있을 것 
    // 종료 기저 말고, 초기 세팅 
    // -1을 념겨주면, 초기 지점에 서있는 것으로 판단하기. 아직 처리한 사건이 0개.
    
    // 만약, 이번 사건을 특정 경찰이 처리했을 시 발생하는 처리 비용을 비교하기 위해 거리 구하기 
    int dist1;
    int dist2;
    if(p1==0){
        dist1=abs(0-query[thisCase].first)+abs(0-query[thisCase].second);
        
    }
    else{
            
            dist1=abs(query[p1].first-query[thisCase].first)+abs(query[p1].second-query[thisCase].second);
        }
        
    if(p2==0){
         dist2=abs(N-1-query[thisCase].first)+abs(N-1-query[thisCase].second);
    }else{
        dist2=abs(query[p2].first-query[thisCase].first)+abs(query[p2].second-query[thisCase].second);
    }
    
    int curp1toend=fn(thisCase,p2)+dist1;
    int curp2toend=fn(p1,thisCase)+dist2; // 현재사건 처리 비용을 더해줌 
    //- 다음 사건을 누가 처리할지는 재귀에서 결정될 것임 
    if(curp1toend<curp2toend){
        
          dp[p1][p2]=curp1toend;
          choice[p1][p2]=1;
    }else{
         dp[p1][p2]=curp2toend;
          choice[p1][p2]=2;
        
    }
  
    
    //출력을 처리하기 위해서, choice 배열에도 알맞은 경찰차 저장하기 
    
    
    return dp[p1][p2];
    
}

void printPath(int p1, int p2){
    
    int thisCase=max(p1,p2)+1;
    if(thisCase==W+1)return;
    int thisCasePolice=choice[p1][p2];
    cout<<choice[p1][p2]<<"\n";
    if(thisCasePolice==1){
         printPath(thisCase,p2);
        
    }else{
        
        printPath(p1,thisCase);
    }
   
    
}


int main() {
    
    cin>>N;
    cin>>W;
    
    memset(dp,-1,sizeof(dp));
    
    for(int i=1; i<=W; i++){
        int x,y;
        cin>>x>>y;
        query[i]=pii(x-1,y-1);
    }
    
    cout<<fn(0,0)<<"\n";
    printPath(0,0);
    
    return 0;
}
