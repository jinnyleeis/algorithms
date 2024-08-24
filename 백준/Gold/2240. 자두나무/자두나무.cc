#include<bits/stdc++.h>

using namespace std;

int t,w,n,tree,r1,r2,result;

// tc 중 맨 큰 숫자만큼 

int dp[1004][2][31];
int pointSpot[1004];



int go(int ct,int pos,int cnt){

  if(cnt<=-1)return -1e9; // 못살리는 루트인 경우 
   else if(ct==t+1 &&cnt==0)return 0;
   else if(ct==t+1&&cnt>0)return -1e9; // 못살리는 루트인 경우 
  

    // 메모이제이션 이용
    int &ret=dp[ct][pos][cnt];
    if(~ret)return ret; // 이미, dp에 계산한게 있을 경우, 그걸 이용 
    // 로직 (현재 시간 + 다음 후 시간(재귀)) 
    int mx=max(go(ct+1,pos^1,cnt-1),go(ct+1,pos,cnt));
   
    if(pointSpot[ct]==pos)mx+=1;
   
    ret=mx;
    return ret;
    
   
    
   
}


int main()
{
    
    cin>>t>>w;
    for(int i=0; i<t; i++){
        cin>>n;
        pointSpot[i+1]=n-1;//0과 1로 위치를 나타내기 위해!
    }
    
    
    memset(dp,-1,sizeof(dp));
    r1=go(1,0,w);
    r2=go(1,1,w-1);
    result=max(r1,r2);

    cout<<result<<"\n";
 

  

    return 0;
}