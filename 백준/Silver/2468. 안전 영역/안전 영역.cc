
#include <bits/stdc++.h>


using namespace std;
int n,m,num,value,max_value,max_count;

int a[105][105];
int visited[105][105];

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};

int count_num;



void dfs(int y,int x,int rain_height){


visited[y][x] = 1;

for(int i=0; i<4; i++){
 int newY=y+dy[i];
 int newX=x+dx[i];
  
  // 맵 기본 세팅: 오버플로우,방문 가능 여부 체크 -> 아닐 시에만 밑에 시행되도록 
if(newY<0||newY>=n||newX<0||newX>=n||a[newY][newX]<=rain_height)continue;
// 방문 여부 체크 
if(visited[newY][newX])continue;

dfs(newY,newX,rain_height); // 넘어가. 
   
    
}

    
}
    


  

int main()
{
    


    

cin>>n; 




for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
        cin>> value;
        a[i][j]=value;
        if(max_value<value){
            max_value=value;
        }
        
        
        
       
    }
    
}




for(int m=0; m<max_value; m++){
    count_num=0;
     memset(visited, 0, sizeof(visited));

for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
        
        if (a[i][j]>m &&!visited[i][j]) {
            dfs(i,j,m);
        count_num++;
     }
        
    
}

}
  
    
 if(max_count<count_num)max_count=count_num;
    
    
}


   cout<<max_count<<"\n";
   
    


 return 0;
}