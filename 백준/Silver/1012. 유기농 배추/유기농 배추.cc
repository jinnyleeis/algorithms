#include <bits/stdc++.h>


using namespace std;
int n,m,num;

int a[51][51];
int visited[51][51];

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};

vector<int> counts;
int count_num;





void dfs(int y,int x){


visited[y][x] = 1;

for(int i=0; i<4; i++){
 int newY=y+dy[i];
 int newX=x+dx[i];
  
  // 맵 기본 세팅: 오버플로우,방문 가능 여부 체크 -> 아닐 시에만 밑에 시행되도록 
if(newY<0||newY>=n||newX<0||newX>=m||a[newY][newX]==0)continue;
// 방문 여부 체크 
if(visited[newY][newX])continue;

dfs(newY,newX); // 넘어가. 
    
    
}



    
}
    


  

int main()
{
    
int c;
cin>>c;
for(int t=0; t<c; t++){
    

cin>>m>>n>>num; // 이번엔 특이하게 가로를 더 먼저 입력받음 

// 배열 초기화
        memset(a, 0, sizeof(a));
        memset(visited, 0, sizeof(visited));
        count_num = 0;

for(int i=0; i<num; i++){
  
int y,x;
cin>>x>>y;
a[y][x]=1;

    
}

for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
        
        if (a[i][j] == 1 && !visited[i][j]) {
          //  visited[i][j]=1; -여기가 아니라, dfs 맨 앞에 이게 있어야 하는 이유? 
          // main에서 for문 돌린거 말고도 dfs 내에서 재귀적으로 파고든것에도 visited 1해야 하므로
            dfs(i, j);
        count_num++;
     }
        
    
}
  
    
  
    
    
}

    counts.push_back(count_num);
   
   
   
    
}

for(auto c: counts){
   cout<<c<<"\n";
   }
 return 0;
}