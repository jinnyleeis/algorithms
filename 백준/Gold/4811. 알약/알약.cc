#include <bits/stdc++.h>
using namespace std;


int n=1;
long long dp[64][64]; // 남은 약의 수 - w : 전체 , h  : 반쪽 자리 
// 남은 약의 수 w+h는 결국 시간과 일대일 대응이므로, 
// 시간을 dp의 상태에 기록할 필요가 없을 것임 


long long move(int n, int w, int h){
  
 
  // bc ~~
  if(dp[w][h]!=-1)return dp[w][h];
  //더 이상 남은 약의 수가 없다면, 종료
  if(w==0 && h==0)return 1;// 말단 노드는 여기서 return 1할 것임 
  
  // dp에 없는, 말단 이외의 노드는 
  // 아래의 ret 변수에 말단에서 결정된 결과를 누적할 것임 
  // 그래서 이를 마지막에 return 할 것임
  // 또 중간 노드의 부모 노드는 이 누적값을 받아서 리턴하겠지? 
  
  long long ret=0; // 재귀 호출해서 구한 결과를 누적할 변수가 필요함 
  // 우선 
  
  // w+h!=0이면, w || h 중 적어도 하나는 약이 남아 있을 것임 
  // 만약 w,h both 남아 있다면 둘 다 재귀 호출 하면 됨
  
  // 한쪽 짜리 꺼낸 경우, 한쪽을 반쪽으로 쪼갠 후 반쪽 한 개를 섭취함 
  // 따라서, w -> w-1, h -> h+1 이 될 것임
  if(w>0)ret+=move(n-1,w-1,h+1);
  if(h>0)ret+=move(n-1,w,h-1);
  
  return dp[w][h]=ret;
    
}

int main() {
    while (n!=0) {
        cin>>n;
        memset(dp, -1, sizeof(dp));  // dp 배열 초기화
        if(n!=0){
        cout<<move(n,n-1,1)<<"\n";}
       
    }

    return 0;
}
