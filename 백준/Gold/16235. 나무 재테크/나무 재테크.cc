#include <bits/stdc++.h>
using namespace std;

int newN[11][11];

// 각각의 칸의 value가 vector에 해당. 
// vector의 size로, 각각의 칸에 존재하는 나무의 수를 구할 수 있다. 
vector<int> m[11][11]; 

int curN[11][11];
int N,M,K;
int result;

int dy[]={-1,-1,0,1,1,1,0,-1};
int dx[]={0,1,1,1,0,-1,-1,-1};


void springSummer(){
    // ** 각각의 칸+나무별로 조사 ** //
    
    // 1단계:자신의 나이만큼 양분을 먹음(오름차순으로, 양분 못먹으면 죽음) 
    // -> 2단계 : 나이 1살 증가 
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(m[i][j].size()==0)continue; // 해당 칸에 나무가 없으면 조사 필요 없음 
            // 죽을 나무가 있을 시, 해당 칸에 추가될 양분의 양 
            vector<int> tempTrees;
            int amount=0; 
            sort(m[i][j].begin(),m[i][j].end());
            for(int tree: m[i][j]){
                if(tree<=curN[i][j]){
                    curN[i][j]-=tree;
                    tree+=1;
                    tempTrees.push_back(tree);
                }else{
                    
                    // 여름 
                    amount+=tree/2;
                }
                
            }
            m[i][j]=tempTrees;
             // 여름 
            curN[i][j]+=amount;
        }
    }
    
    
}


void fall(){
      for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(m[i][j].size()==0)continue; 
            for(int tree: m[i][j]){
                if(tree%5==0){
                   for(int d=0; d<8; d++){
                       int newY=i+dy[d];
                       int newX=j+dx[d];
                       if(newY>=N||newX>=N||newY<0||newX<0)continue;
                       // 해당 조건을 만족할 시, 나이가 1인 나무가 번식
                       m[newY][newX].push_back(1); 
                   }
                    
                }
            }
        }
           
      }
}


void winter(){
     for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            curN[i][j]+=newN[i][j];
        }
     }
    
    
}

int main()
{
    
    cin>>N>>M>>K;
    
    fill(&curN[0][0],&curN[0][0]+11*11,5);
    
    // 겨울에 N*N 땅의 각 칸에 추가될 양분 계산 
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>newN[i][j];
        }
    }
    
    
    // M : 나무의 수 
    for(int i=0; i<M; i++){
        int y,x,age;
       cin>>y>>x>>age;
       m[y-1][x-1].push_back(age);
       
    }
    
    // K회 4계절 사이클 돌리기
    for(int i=0; i<K; i++){
        springSummer();fall();winter();
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            result+=m[i][j].size();
        }
    }
    
    cout<<result<<"\n";
    

    return 0;
}