#include<bits/stdc++.h>
using namespace std;

#define INF 2000000000

int group1[1001];
int group2[1001];
int n,m;
int dp[1001][1001];
int group1len;
int group2len;

// optimal structure : dp[i][j]= min(c[i]+dp[i+1][j+1],0+dp[i][j+1])

int dpfn(int i,int j){
    
int cost;
int result1, result2;
    
    int &ret=dp[i][j];
    if(ret!=-1)return ret;
    if(i==group1len)return 0;
    if((group1len-i)>(group2len-j))return INF;
   cost=abs(group1[i]-group2[j]);
   
   
      // 매칭 ㅇㅇ 인 경우, i를 건너뜀 
   result1=cost + dpfn(i + 1, j + 1);
   // 매칭 x인 경우, j+1해서 i와의 짝을 찾음 
   result2=0+dpfn(i,j+1);
   
   return ret=min(result1,result2);
    
    
}

int main()
{
   
    cin >> n >> m;
    
 //  n>m면, m이 group1, n이 group2 
 if(n>m){
     group1len=m;
     group2len=n;
     
    for(int i=0; i<n; i++){
        cin >> group2[i];
    }
     for(int i=0; i<m; i++){
        cin >> group1[i];
    }
 }
else{
     group1len=n;
     group2len=m;
     
     for(int i=0; i<n; i++){
        cin >> group1[i];
    }
     for(int i=0; i<m; i++){
        cin >> group2[i];
    }
    
}
 
   sort(group1, group1 + group1len);
    sort(group2, group2 + group2len);
// -1로 초기화 
  memset(dp,-1,sizeof(dp));
  cout<<dpfn(0,0)<<"\n";

    return 0;
}