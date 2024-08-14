#include <bits/stdc++.h>


using namespace std;
int m,n,k;
int sx,sy,ex,ey;
int cnt_block;
vector<int> s;

int a[105][105];
int visited[105][105];

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};

int count_num;




void dfs(int y,int x){


visited[y][x] = 1;
cnt_block++;

for(int i=0; i<4; i++){
 int newY=y+dy[i];
 int newX=x+dx[i];
  
  // 맵 기본 세팅: 오버플로우,방문 가능 여부 체크 -> 아닐 시에만 밑에 시행되도록 
if(newY<0||newY>=m||newX<0||newX>=n||a[newY][newX]==1)continue;
// 방문 여부 체크 
if(visited[newY][newX])continue;

dfs(newY,newX); // 넘어가. 
   
    
}

    
}
    


  

int main()
{
    


    

cin>>m>>n>>k;


for(int i=0; i<k; i++){
    cin>> sx>>sy>>ex>>ey;
    sy=m-sy;
    ey=m-ey;
    // 좌표 뒤집어서 조절 편하게 저장
   for(int y=ey; y<sy; y++){
       for(int x=sx; x<ex; x++){
           a[y][x]=1;
       }
   }
}






for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
        
        if (a[i][j]==0 &&!visited[i][j]) {
            cnt_block=0;
            dfs(i,j);
        count_num++; // 사각형의 수 
        s.push_back(cnt_block);
     }
        
    
}

}
  

    cout<<count_num<<"\n";
    sort(s.begin(),s.end());
    for(auto i:s){
        cout<< i <<" ";
    }
   
    


 return 0;
}