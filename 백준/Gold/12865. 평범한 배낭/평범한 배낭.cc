 
#include <bits/stdc++.h>
using namespace std;

int dp[100][100000]; 
// nth부터 ~ 1)까지 고려했을 때, 남은 무게가 2)일때 최대 value 

// 헷갈리니까 아래 두개를 별개의 배열로 분리해놓자
int w[100];
int v[100];


int mx_v;
int cw;
int n,k;

//탑다운은 뒤에서부터 앞에까지 고려 즉, n-> idxth 

int dpfn(int idx,int cw){
    
  if(idx==n||cw<=0)return 0;
  //물건 다 탐색, 담을 무게가 없을 시 -> 더해질 가치가 없으므로 
  
  if(dp[idx][cw]!=-1)return dp[idx][cw]; 
  // 이미 이 경우를 계산했을 때 메모이제이션 한 값을 이용한다. 
  int result1=0;
  int result2=0;
  // 점화식 
  // idx 물건을 담지 않을 경우
  result1=dpfn(idx+1,cw);
 
  
  //idx 물건을 담을 경우 
  // 주의 이때 무게 제한 조건을 검사해야 한다!!!
 if(cw>=w[idx]){
  result2=dpfn(idx+1,cw-w[idx])+v[idx];}
      
  
  
   dp[idx][cw]=max(result1,result2);
  
  return dp[idx][cw];

}

int main()
{
    
   cin>>n>>k; // 물품의 수와 무게
   for(int i=0; i<n; i++){
       cin>>w[i]>>v[i]; // 무게, 가치 
      
   }
   
   memset(dp,-1,sizeof(dp));
  
   
   dpfn(0,k);
   
  // cout<<dp[n-1][k]<<"\n";
  cout<<dp[0][k]<<"\n"; // dp 설계가 애초에 뒤에서부터 (리프) 쌓아나가서 계산되는 형태이므로!
 
   

    return 0;
}