#include<bits/stdc++.h>


using namespace std;

int ret,n;

int dy[]={-1,-1,0,1,1,1,0,-1};
int dx[]={0,1,1,1,0,-1,-1,-1};

int m[100][100];

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
    
    
    
    // 오버플로우 처리!!
    if(y>=n||x>=n)return 0;
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
        
        // 계속 가로 2 
        ret+=move(y+dy[2],x+dx[2],0);
        // 대각선 3 
        ret+=move(y+dy[3],x+dx[3],2);
        
            break;  
            
            
        case 1: // 세로 
           
           
        // 3 대각선 
        ret+=move(y+dy[3],x+dx[3],2);
        
        // 4 세로 
        ret+=move(y+dy[4],x+dx[4],1);
        
          
            break;
        case 2: // 대각선 
            
        // 가로 2 
        ret+=move(y+dy[2],x+dx[2],0);
        
        // 대각선 3 
        ret+=move(y+dy[3],x+dx[3],2);
        
         // 세로 4 
        ret+=move(y+dy[4],x+dx[4],1);
            break;
        default: // 없음 
            break;
    }
    
   
    return 0;
}





int main() {
    
    cin>>n;
    for(int i=0; i<n; i++){
       for(int j=0; j<n; j++){
           cin>>m[i][j];
       }
    }
    
    move(0,1,0); // 맨 처음엔 가로로 시작한다. 
    cout<<ret<<"\n";
  
    
    return 0;
}