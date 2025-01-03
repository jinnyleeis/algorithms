#include <bits/stdc++.h>
using namespace std;

// M(최대 무게) 최대 10,000
// N(물건 종류) 최대 100
// 각 물건 개수 K 최대 10,000
// 이진 분할 시, 각 물건당 최대 log2(10000) ~ 14개 이하로 분할
// 전체 아이템 수 최대로 대략 100 * 14 = 1400 여유있게 20000 정도 잡아둠
static const int MAX_ITEMS = 20000;

// 분할 후 저장할 (무게, 가치) 배열
int Wtemp[MAX_ITEMS];
int Vtemp[MAX_ITEMS];

int dp[10001]; // dp[cap] = cap 무게까지 담을 때의 최대 가치

int main(){
  

    int N, M;
    cin >> N >> M;

    // 묶음 아이템을 저장할 인덱스
    int itemCount = 0;

    // 1) 각 물건 정보를 이진 분할하여 (weight, value) 묶음 아이템으로 변환
    for(int i = 0; i < N; i++){
        int w, v, k;
        cin >> w >> v >> k; // 무게, 가치, 개수

        // 이진 분할
        int base = 1;
        while(k > 0){
            int take = min(base, k);
            Wtemp[itemCount] = w * take;
            Vtemp[itemCount] = v * take;

            itemCount++;
            k -= take;
            base <<= 1; // base *= 2;
        }
    }

    // 2) 이제 0/1 배낭으로 itemCount개의 아이템을 dp에 반영
    //    cap은 큰 쪽부터 내려가면서 dp 갱신
    for(int i = 0; i < itemCount; i++){
        int weight = Wtemp[i];
        int value = Vtemp[i];
        for(int cap = M; cap >= weight; cap--){
            dp[cap] = max(dp[cap], dp[cap - weight] + value);
        }
    }

    cout << dp[M] << "\n";
    return 0;
}