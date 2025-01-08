
#include<bits/stdc++.h>
using namespace std;

int dp[51][51][51][51]; // n(y쪽 좌표),m(x쪽 좌표),이전 오락실 번호, 방문할 오락실 수
int N,M,C;
int n,m;
int mp[51][51];
//int currentC;
int mod=1000007;

int dpfn(int y,int x,int pnum, int cnt){
    
    // bc 체크 
    if((y==N-1)&&(x==M-1)){ // 도착 
        if((mp[y][x]==0)&&(cnt==0))return 1; // 성공
        if((pnum<mp[y][x])&&cnt==1)return 1; // 성공
        return 0; // 위의 두 경우 제외하고 나머진 실패 
    }
    
    // 오버플로우 체크
    if(y<0||y>N-1||x<0||x>M-1)return 0;  // 실패
    
    
    
    int &ret=dp[y][x][pnum][cnt];
    
    // 이미 동일 조건 하에서, 방문했던 지점인지 체크 
    if(ret!=-1)return ret;
    ret = 0;
    // dp가 아직 채워지지 않은 경우 채워야 할 것임 
    
    if(mp[y][x]){// 오락실인 경우 
        if(pnum>=mp[y][x])return 0;
        cnt--;
        ret=(dpfn(y+1,x,mp[y][x],cnt)+dpfn(y,x+1,mp[y][x],cnt))% mod;
        return ret;
        
    }
    // 오락실이 아닌 경우는 조사할 필요나, cnt 설정 할 필요가 없음 
   
    ret=(dpfn(y+1,x,pnum,cnt)+dpfn(y,x+1,pnum,cnt))% mod;
    
    return ret;
    
    
}

int main()
{
        ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);

    cin>> N >> M >> C ;
    memset(dp,-1,sizeof(dp));
    memset(mp,0,sizeof(mp));
    
    for(int i=1; i<=C; i++){
        cin>>n>>m;
        mp[n-1][m-1]=i;
    }
    
    for(int i=0; i<=C; i++){
        // sn,sm,이전 오락실 번호(아직x므로)=0, C(방문해야하는 오락실 수)
       // currentC=i;
        cout<<dpfn(0,0,0,i)<<" ";
    }
    
  
    return 0;
}