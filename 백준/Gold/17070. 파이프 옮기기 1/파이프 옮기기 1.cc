#include<bits/stdc++.h>


using namespace std;

int ret,n;

int dy[]={-1,-1,0,1,1,1,0,-1};
int dx[]={0,1,1,1,0,-1,-1,-1};

int m[20][20];

int dp[20][20][3]; // 상태값을 dp에 저장 

/*
목표 : 한쪽 끝이 (n,n)에 닿게 하는 것이 목표임 

state 
1. 0 : 가로 
2. 1 : 세로 
3. 2 : 대각선 

state가 무엇인지에 따라 차지하고 있는 크기도 다름 
기존 머리 부분 (a,b)로 한다면, 

0: 가로

가로 (a,b-1) (a,b)

1 세로 : (a-1,b)(a,b)

2 대각선 
(a-1,b-1)(a,b-1)(a-1,b)(a,b)
 
 state가 무엇인지에 따라 다음으로 이동 가능한 방향도 다름 
 이 이동 가능을 dy, dx의 조합으로 이를 나타내자! 




***/



int move(int y,int x,int state){
    
    

 // 오버플로우 처리!! - 범위 벗어나는 오버플로우 처리하는거 까먹지 말자
    if(y>=n||x>=n)return 0;
    if (dp[y][x][state] != -1) return dp[y][x][state];
    
    int ret = 0;

    if(state==0){
    if(m[y][x-1]==1||m[y][x]==1)return 0;
    }else if(state==1){
        if(m[y-1][x]==1||m[y][x]==1)return 0;
        
    }else if(state==2){
        
        if(m[y-1][x-1]==1||m[y-1][x]==1||m[y][x-1]==1||m[y][x]==1)return 0;
        
    }
    
    
    if(x==n-1&&y==n-1)return 1; // 종료 조건 

    
    
    // 만약 이동하면 어떤 문제가 발생할지 조사한 후, 이동한다. 
    switch (state) {
        case 0: // 가로 
        
        int c1,c2;
        // 계속 가로 2 
        c1=move(y+dy[2],x+dx[2],0);
        // 대각선 3 
        c2=move(y+dy[3],x+dx[3],2);
        dp[y][x][0]=c1+c2;
        ret+=dp[y][x][0];
            break;  
            
            
        case 1: // 세로 
        
        int c3,c4;
           
        // 3 대각선 
      c3=move(y+dy[3],x+dx[3],2);
        
        // 4 세로 
       c4=move(y+dy[4],x+dx[4],1);
       
       
        dp[y][x][1]=c3+c4;
        ret+=dp[y][x][1];
          
            break;
        case 2: // 대각선 
        
        int c5,c6,c7;    
        // 가로 2 
        c5=move(y+dy[2],x+dx[2],0);
        
        // 대각선 3 
        c6=move(y+dy[3],x+dx[3],2);
        
         // 세로 4 
        c7=move(y+dy[4],x+dx[4],1);
        
        
        dp[y][x][2]=c5+c6+c7;
        ret+=dp[y][x][2];
            break;
        default: // 없음 
            break;
    }
    
   
return dp[y][x][state] = ret;
}





int main() {
    
    cin>>n;
    for(int i=0; i<n; i++){
       for(int j=0; j<n; j++){
           cin>>m[i][j];
       }
    }
    
       // DP 테이블 초기화 (-1로)
    memset(dp, -1, sizeof(dp));
    
    move(0,1,0); // 맨 처음엔 가로로 시작한다. 
    cout<<dp[0][1][0]<<"\n";
  
    
    return 0;
}
