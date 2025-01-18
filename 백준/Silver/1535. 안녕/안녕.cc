#include <bits/stdc++.h>
using namespace std;


int L[21];
int J[21];
int dp[21][101];
int l=100;
int n;


int dpfn(int i, int w){
    
    if((i == n)&&w>0)return 0; // 마지막 사람 n-1까지 조사했는데 체력이 정상적으로 남아있었으면
    if(w<=0)return -1e9; //0부터 죽은 것이므로 
    if(dp[i][w]!=-1)return dp[i][w];
    
    int result1=0,result2=0;
    
    
   
    if(w<L[i]){  // 이번에 인사 가능일까? 
        result1=dpfn(i+1,w-0)+0;
        
    }else{
    result2=max(dpfn(i+1,w-L[i])+J[i],dpfn(i+1,w-0)+0);}
    
    
    return dp[i][w]=max(result1,result2);
    
}

int main()
{
    
    cin>>n;
    
    for(int i=0; i<n; i++){
        cin>>L[i];
    }
    for(int i=0; i<n; i++){
        cin>>J[i];
    }
    
    memset(dp,-1,sizeof(dp));
    
    cout<<dpfn(0,l)<<"\n";

    return 0;
}