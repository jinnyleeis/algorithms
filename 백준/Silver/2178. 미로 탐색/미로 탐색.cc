/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>


using namespace std;
int n,m;
int a[101][101];
int visited[101][101];

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};


 int startY=0;
 int startX=0;
 int endY;
 int endX;


void path(){
    
// 초기화 
queue<pair<int,int>> q;

q.push({startY,startX});
visited[startY][startX]=1;




while(q.size()){
    
int y,x;
    
tie(y,x)=q.front();
q.pop();



for(int i=0; i<4; i++){
 int newY=y+dy[i];
 int newX=x+dx[i];
  
  // 맵 기본 세팅: 오버플로우,방문 가능 여부 체크 -> 아닐 시에만 밑에 시행되도록 
if(newY<0||newY>=n||newX<0||newX>=m||a[newY][newX]==0)continue;
// 방문 여부 체크 
if(visited[newY][newX])continue;

q.push({newY,newX});
visited[newY][newX]=visited[y][x]+1;
}




    
}
    
}
    


  

int main()
{
    

cin>>n>>m;

endY=n-1;endX=m-1;

for(int i=0; i<n; i++){
string line;
cin>>line;
    for(int j=0; j<m; j++){
            a[i][j] = line[j] - '0';  // 문자 '0'의 ASCII 값을 빼서 숫자로 변환
    }
}
  

    path();
    
    
    
        cout<<visited[endY][endX];
    
   
 
    
    return 0;
    
}