#include<bits/stdc++.h>

using namespace std;

int t,n,mx;

// tc 중 맨 큰 숫자만큼 

int dp[10004];
vector<int> tc;

vector<int> atoms={1,2,3};

void countWays(int n){
    
    dp[0]=1;
    for(auto atom:atoms){
        for(int i=atom; i<=n; i++){
            dp[i]+=dp[i-atom];
        }
    }
    
    
    
}


int main()
{
    
    cin>>t;
    for(int i=0; i<t; i++){
       
        cin>>n;
        tc.push_back(n);
       
    }
    
    
   auto mxIter = max_element(tc.begin(), tc.end());
   // 반복자 역참조
   int mx = *mxIter;    
    
    countWays(mx);
    
    
    for(auto n:tc){
        
       cout<<dp[n]<<"\n";
    } 
        

   
 

    return 0;
}