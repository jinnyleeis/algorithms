#include <iostream>
using namespace std;
typedef long long ll;
int t;

// 확장 유클리드 알고리즘
// 함수는 a*x + b*y = gcd(a, b)를 만족하는 x, y와 gcd(a,b)를 반환한다.
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; 
        y = 0;
        return a;
    }
    ll g = extended_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    cin>>t;
    for(int i=0; i<t; i++){
    ll K, C;
    cin >> K >> C;
    
    const ll LIMIT = 1000000000LL;  // 10^9
  
    // 특수 케이스 처리
    if (C == 1) {
        // C가 1이면, 식은 y = K * X + 1이 되어 최소 y는 K+1이다.
        ll ans = K + 1;
        if (ans > LIMIT)
            cout << "IMPOSSIBLE\n";
        else
            cout << ans << "\n";
        continue;
    }
    if (K == 1) {
        // K가 1이면, y = 1이 해가 된다.
        cout << 1 << "\n";
        continue;
    }
    
    // 일반 케이스: 식은 C*y ≡ 1 (mod K)
    // 즉, C*y - 1가 K의 배수가 되어야 한다.
    // 이는 C의 모듈러 역원 문제와 동일하다.
    ll x, y;
    ll g = extended_gcd(C, K, x, y);
    
    if (g != 1) {
        // gcd(C, K)가 1이 아니라면 해가 없다.
        cout << "IMPOSSIBLE\n";
         continue;
    }
    
    // x는 C의 모듈러 역원 (즉, C*x ≡ 1 (mod K))인데, 음수일 수 있으므로 조정한다.
    ll ans = (x % K + K) % K;
    if (ans == 0) ans = K;  // (이론상 gcd=1이면 0이 되는 경우는 없음)
    
    if (ans > LIMIT)
        cout << "IMPOSSIBLE\n";
    else
        cout << ans << "\n";
        
    }
        
     return 0;
}