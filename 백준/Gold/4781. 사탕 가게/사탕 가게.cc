#include<bits/stdc++.h>
using namespace std;



int dp[10001];
int cost[5000];
int k[5000];
vector<int> result;
bool isExit=false;

int main()
{
   
    
   
   
   
   while(!isExit){
       
int N=0;
float M=0.00;
 memset(dp,0,sizeof(dp));
 memset(cost,0,sizeof(cost));
 memset(k,0,sizeof(k));





// 케이스 입력 
   cin>>N>>M;
   


     if((N==0)&&(M==0.00)){isExit=true;break;}
        int money = round(M * 100);

   
   for(int i=0; i<N; i++){
       
int c;
float p;
   cin>>c>>p;
   k[i]=c;// 칼로리 
   cost[i]=p*100; // 가격 
   }
   
 for(int i=0; i<N; i++){
     // 무조건 cost[i]부터 시작해야. cost[i]를 이용하려면,
     //가능한 돈이 cost[i]보다 커야하므로!!
     
     for(int limit = cost[i]; limit<=money; limit++){
       
        dp[limit]=max(dp[limit],dp[limit-cost[i]]+k[i]);
        // 1항:이번 i번쨰 아이템은 안고려해서 Limit 안줄음
        // 2항: 이번 i번째 아이템은 고려해서 limit 줄음 
        // 여기선 unbounded로, 중복계산 가능하게끔 limit 증가시키면서 dp 채워나감
          }
     }
 
 result.push_back(dp[money]);
   
   
   
}


for(auto i : result) {
        cout <<i << "\n";
    }


    

    return 0;
}