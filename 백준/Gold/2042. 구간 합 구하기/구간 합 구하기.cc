#include<bits/stdc++.h>
using namespace std;  

int n, ucnt, scnt;
vector<long long> results; // 결과를 long long으로 변경


/* 
#1. 초기화 
1) 크기 정하기 
1. 2^k <= N인 최솟값 k를 구한다. 
2. 2^k*2 크기의 배열을 만든다. 
3. 이중에서, 2^k번째부터 ~ 2^k+1-1까지 2^k 개의 자리에 순서대로 원소를 채워넣는다. 

2) 부모 노드 값 채우기 /2 한 부분에 각각의 로직에 알맞도록 값을 채운다. 

// 

#2. 질의에 해당하는 노드 선택하기 
0. 인덱스 변환 given index + 2^k-1 
1. start index %2 = 1이면,  선택 
2. end index %2 = 0이면, 선택
3. (start + 1) / 2 부모 레벨 start index로 선택 
4. (end + -1) /2 부모 레벨 end index로 선택 
* 
#3. 선택된 노드들에 대해 마지막 연산하기 
이중에서 다 더하거나 그러면 됨 
*/


int main()
{
   ios::sync_with_stdio(false);
   cin.tie(NULL);
   
   cin >> n >> ucnt >> scnt;
   // 초기화 
   // 1. 2^k <= N인 최솟값 k를 구한다. 
   int k = 0;
   long long power = 1; 
   while (power <= n) {
       k++;
       power <<= 1; // 하나씩 *2승씩 해나간다. 
   }
   
   long long size = pow(2, k);
   
   // 2. 2^k*2 크기의 배열을 만든다. 
   long long vals[size*2]; 
   
   // 초기화
   memset(vals, 0, sizeof(vals));
   
   // 3. 이중에서, 2^k번째부터 ~ 2^k+1-1까지 2^k 개의 자리에 순서대로 원소를 채워넣는다. 
   for(long long i = 0; i < n; i++){
       long long temp; 
       cin >> temp;
       vals[i + size] = temp;
   }
   
   // 4. 부모 노드 값 채우기
   for(long long i = size*2 -1; i > 1; i--){
       vals[i/2] += vals[i]; 
   }
   
   for(int i = 0; i < (ucnt + scnt); i++){
     long long a, b, c;
      cin >> a >> b >> c;
    
      if(a == 1){
           // update 
          long long diff = c-vals[b+size-1];
          
          int pos=b+size-1;
          
         while(pos>0){
             // 루트 노드(1)까지 업데이트!!
            vals[pos]+=diff;
            pos=pos/2;
            
           /* b=b/2; 
             이거 틀린 이유!! b가 아니라, b+size-1가 리프 노드 자식 인덱스 이므로, 
            이것을 /2해야 알맞게 계산될 것이다!!
           */
            
         }
      }
      else if(a == 2){
          // 구간 합 구하기 로직 
          long long sidx = b + size - 1;
          long long eidx = c + size - 1;
        
          long long res = 0; // 결과를 저장할 변수
          
          while(sidx <= eidx){
              if(sidx % 2 == 1){
                  res += vals[sidx];
                 
              }
              if(eidx % 2 == 0){
                  res += vals[eidx];
                  
              }
              sidx= (sidx+1)/2;
              eidx= (eidx-1)/2;
          }
          
          results.push_back(res);
      }
       
   }
    
    for(int i = 0; i < results.size(); i++) {
            cout << results[i] << "\n";
    }
   
    return 0;
}
