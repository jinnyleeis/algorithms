#include <iostream>
using namespace std;

int N, K;
const int MAX = 200;
int a[MAX+1][2];// 내구도 / 로봇 존재 여부 

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> K;
    int size = 2 * N;
    
    for (int i = 0; i < size; i++){
        cin >> a[i][0];
        a[i][1] = 0; // 로봇 없는 상태임 
    }
    
    int step = 0;
    int start = 0;
    
    while (true){
        step++;
        
        // 회전 : start 이동 - 상대적 칸의 위치 start 기준점으로
        start = (start - 1 + size) % size;
        int down = (start + N - 1) % size;
        
       
        a[down][1] = 0;
        
        // 로봇 : 앞의 로봇 여부에 따라 이동 가능 여부 결정이므로 역순으로
        for (int i = N - 2; i >= 0; i--){
            int cur = (start + i) % size;     
            int next = (cur + 1) % size;     
            
            if(a[cur][1] == 1 && a[next][1] == 0 && a[next][0] >= 1){
             
                a[cur][1] = 0;
              
                if(next != down)
                    a[next][1] = 1;
                a[next][0]--; // 이동 칸 내구도 감소 시킴 
            }
        }
        
        // 올리기 
        if(a[start][0] > 0 && a[start][1] == 0){
            a[start][1] = 1;
            a[start][0]--;
        }
        
        
        int cnt = 0;
        for (int i = 0; i < size; i++){
            if(a[i][0] == 0) cnt++;
        }
        if(cnt >= K) break;
    }
    
    cout << step << "\n";
    return 0;
}
