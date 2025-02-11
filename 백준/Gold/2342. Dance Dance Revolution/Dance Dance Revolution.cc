#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std; 

typedef long long ll; 

ll dp[100002][5][5];

const int INF=1e9;

vector<int> query;

ll moveCost(int cur, int next) {

	if (cur == 0)return 2; // 아직 정중앙에 위치했다면,
	if (cur == next)return 1; // 그냥 가만히 
	if (abs(cur - next) == 2)return 4; // 반대방향이면,
	return 3;
	// 그냥 이건 바로 return 3로 처리해도 될듯 - 짜피 남은건 이 경우밖에 없으니까!


}




// 뒤에서부터 할 필요x x-> 어짜피 다 해야함 - 쿼리의 조합이 어떤지에 따라서 너무 달라짐


int main()
{
    
    ios::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
    
   fill(&dp[0][0][0], &dp[0][0][0] + 100002 * 5 * 5, INF);
   

   while(true){
       
       int q;
       cin>>q; 
       if(q==0)break;
       query.push_back(q);
   }
   
   int N=query.size();
   
   dp[0][0][0]=0; // 0은 정중앙!!  left / right 
   // 이것 이외에, 나머지는 비용이 inf 아예 없는 비용임 
   
   // 시작점이 0이면, 기저 move cost에서 처리해줬으므로, 반목문을 1부터 돌릴 수 있다!!
   
   
   // 쿼리 신경쓰지말고,
   // 아 쿼리를 신경써야!!! - 그래야 총 비용이 누적을 대신할 수!! -그냥 누적값만 놔두면, 
   // 나중에 쿼리 1->2->3-4 이런거 모르잖아, 중간에 어떘는지. 
   // 쿼리같은거 지정 안해주고, 딱 출발지/목적지만 
   // 주어주고 최종까지 갈 수 있는 거리가 얼마야? - 이런 마지막 누적값만 물어볼 땐 
   // 이 방식도 괜찮을 것 같은데
   // 매 순간 발을 어떻게 움직였을 떄, 누적 비용이 나올지를 이걸로 계산해놓는다!!
  
   for(int i=1; i<=N; i++){
       
       int q=query[i-1]; // 이번 i 번째에 해당 쿼리의 위치로 움직여야 한다!!
       // 하나의 발을!!
       for(int l=0; l<=4; l++){
           for(int r=0; r<=4; r++){
             if (dp[i - 1][l][r] == INF) continue;

             // 매 순간 발을 어떻게 
            // 기저부터 생각해서, lr은 제대로 계산되었다고 가정 
            // (즉, 00 이외에 왼/오른발이 같은 칸에 위치했을리는 없게ㅔ
            // 그럼 그 다음인 i번쨰에서도 같은 칸에 안 위치할 수 있도록 조건을 걸어주어야!
             
             // 왼쪽발을 이동했다고 할 떄 <- 아무떄나 이동하는게 아니라, 
             // 왼쪽발 이동시, 오른발이랑 안같아진다면
             
             // 같은 지점은 inf로 남아있을 수 있을 것임!!
            // 111111 쿼리가 이렇게 오면, 한발만 계속 움직이면 된다!!
            // 000 이외의 것은 무한대로 채워질 것임 
            
            
            // 즉, 둘 다 다르면, 둘 다 계산 되는 것임 
            // r과 다르면, - 계산 가능 
            if(i==1){
                dp[i][q][0]=dp[0][0][0]+moveCost(0,q);
                dp[i][0][q]=dp[0][0][0]+moveCost(0,q);
                
            }else{
           
             
            if(q!=r){
                dp[i][q][r] = min(dp[i][q][r], dp[i-1][l][r] + moveCost(l,q));
                // q는 반복문에 따라 변하지 않고 고정 - l과 r이 달라짐 
                
            }
            if(q!=l){
                dp[i][l][q] = min(dp[i][l][q], dp[i-1][l][r] + moveCost(r,q));
                
            }

             //  cout<< i<<"왼"<<q<<"오"<<r<<"값"<<dp[i][q][r]<<"\n";
               
                 
             }
           
             
         
             // r
             //if(q)
               
            }
               
           }
       }
       
        
       
      
       
  
   
    ll res=INF;
    for(int l=0; l<=4; l++){
        for(int r=0; r<=4; r++){
        if(res>dp[N][l][r]){
            
            res=dp[N][l][r];
        }
        }
    }
   cout<<res<<"\n";
   
   /*
    for(int i=0; i<=N; i++){
       
       int q=query[i-1]; // 이번 i 번째에 해당 쿼리의 위치로 움직여야 한다!!
       // 하나의 발을!!
        for(int l=0; l<=4; l++){
           for(int r=0; r<=4; r++){
               if(dp[i][l][r]<INF){
            //   cout<<"타임"<<i<<" :"<<dp[i][l][r]<<"\n";}
           }
       }
    }
*/
    return 0;
}