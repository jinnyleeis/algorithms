#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>
#include <queue>
#include <limits> 

using namespace std;


int W,B;

char board[4][4];
int score[]={0,0,0,1,1,2,3,5,11};


int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dx[8] = {-1,  0,  1, 1, 1, 0, -1, -1};


bool visited[4][4]; // 각 단어별로 존재.
set<string> founds;
vector<string> words;

// 편의를 위해 idx 1번부터 알맞은 값을 저장하자.
// 하지만, 한 주사위는 단어에 한 번만 사용할 수 있다. 

/*
단어의 목록 
게임 보드 

최대 점수, 가장 긴 단어, 찾은 단어의 수 출력 
한 Boggle에서 같은 단어를 여러 번 찾은 경우에는 한 번만 찾은 것으로 센다. 
*/


struct Trie{
    
    
    bool isEnd;
    Trie* next[26]; // 알파벳이 인덱스로 표현되게끔!!
    
    Trie(){
        isEnd=false;
        // 초기화 
        for(int i=0; i<26; i++){
            next[i]=nullptr;
        }
    }
    
    ~Trie(){
       for(int i=0; i<26; i++){
            delete next[i];
        }
    }
    
    // 특정 문자열을 트라이 연결 리스트로 insert하는 방법 
    // 그러기 위해선 main에서 받은 문자열을 참조할 수 있게 넘겨줘야
    // 그리고 맨 첫글자부터 끝까지 재귀 호출 될 것이므로, 
    // idx도 0부터 넘겨받을 수 있어야 한다. 
    void insert(string &s,int idx){
        
        if((int)s.size()==idx){
            isEnd=true; 
             // trie의 끝을 나타내기 위해 
            return;
        }
        
        int alphaIdx=s[idx]-'A';
        if(!next[alphaIdx]){
            next[alphaIdx]=new Trie();
        }
      //  next[alphaIdx]->insert(&s,idx+1); 호출시 & 빼는거 제발 주의 
      next[alphaIdx]->insert(s,idx+1);
        
    }
    
    // 트라이 트리 내에 특정 단어가 있는지 확인하는게 아니라, 
    // 보드로 트리의 단어만들 수 있는지 
    // 즉, 보드 내 특정 단어 루트에서부터 
    
    void searchBoard(string temp, int y,int x){
     
        // 그럼 현재 단어 처리해야할 것임 
        int curBoardAlpha=board[y][x]-'A';
        if(!next[curBoardAlpha]){
            return;
            // ! 빼고 작성해버림 첨에 
        }
        
        
        // 부모 노드에서 해당 알파벳에 대응되는자식 노드로 이동해야, isend 등의 값 확인 가능 
        Trie* childNode=next[curBoardAlpha];
         
        // 이 단어까지 추가하면 나오는 단어 
         temp.push_back(board[y][x]);
        
         if(childNode->isEnd){
         founds.insert(temp);//set은 insert
         }
        
        if((int)temp.size()==8){
            return; // 글자 수 제한 8 - 더 탐색xx
        }
        
        
        for(int i=0; i<8; i++){
            int ny=y+dy[i];
            int nx=x+dx[i];
            
            if(ny<0 || nx<0 || ny>=4 || nx>=4){
                continue;
            }
            
            // 오버플로우와 방문여부 체크 
            if(visited[ny][nx]){
                continue;
            }
          
            
            visited[ny][nx]=true;
            // 다음 노드로 건너뜀 - 함수도 새로운 노드의 함수임
            childNode->searchBoard(temp,ny,nx);
            visited[ny][nx]=false; 
            // cur에서 Next의 visited 방문 배열 처리 
            // - DP말고, 백트래킹에선 가능함
            
            
        }
        
    }
    
};



int main() {
    
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    cin >> W;
    for(int i=0; i<W; i++){
        //실수: 첨에 단어를 입력받지 않고, 빈 문자열("")을 그대로 벡터에 추가하게 작성함
        string temp;
        cin>>temp;
        words.push_back(temp);
    }
     
     
    
     

    
    Trie* root=new Trie();
    
    for(auto &s:words){
         root->insert(s,0);
    }
    
    cin>>B;
    for(int b=0; b<B; b++){
            founds.clear();
            
  

        
        // 글자로 보드 채우기
        for(int i=0; i<4; i++){
            string temp;
            cin>>temp;
            for(int j=0; j<4; j++){
                board[i][j]=temp[j];
            }
        }
        
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            visited[i][j]=false;
        }
    }
        
               
// 초기화
int maxScore=0;
int maxLength=0;
int wordCnt=0;
string maxLenWords="";

        
        /*
        방문 배열 쓰면, 각각의 칸을 시작점으로 삼아도 
        경우의 수 겹치지 않을 것임
        */
         for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                //시작지점도 방문지점 표시 중요
                visited[i][j]=true;
                root->searchBoard("",i,j);
                visited[i][j]=false;
                
            }
            }
                
          
          
          // 점수 계산 
        for(auto &s:founds){
         maxScore+=score[s.size()];
        }
        
       for(auto &word:founds){
         
           if((int)word.size()>maxLength||(((int)word.size()==maxLength) && (word<maxLenWords))){
            maxLenWords=word;
            maxLength=word.size();
           }
       }
       
       wordCnt=(int)founds.size();
    
        
        // 출력 수행 
        cout << maxScore << " " << maxLenWords << " " << wordCnt << "\n";
      
    }
        
         return 0;
    }
    