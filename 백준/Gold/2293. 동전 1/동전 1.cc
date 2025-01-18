#include <bits/stdc++.h>
using namespace std;


// 첫째 줄에 n, k가 주어진다. (1 ≤ n ≤ 100, 1 ≤ k ≤ 10,000) 
// 다음 n개의 줄에는 각각의 동전의 가치가 주어진다. 
// 동전의 가치는 100,000보다 작거나 같은 자연수이다.

int dp[10000];
int n,k;
int coins[100];

int main()
{
    cin>>n>>k;
    
    for(int i=0; i<n; i++){
        cin>>coins[i];
    }
    
    dp[0]=1;
    
    for(int i=0; i<n; i++){
        int coin=coins[i];
        for(int j=coin; j<=k; j++){
            dp[j]+=dp[j-coin]; // 이번 동전을 추가적으로 하나 더하면 될 것이므로 
        }
    }
    
    cout<<dp[k]<<"\n";
    
    
    return 0;
}