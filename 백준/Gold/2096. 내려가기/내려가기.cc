#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N;
    cin >> N;
    
    int dp_min[3], dp_max[3];
    int next_min[3], next_max[3];
    
    cin >> dp_min[0] >> dp_min[1] >> dp_min[2];
    dp_max[0] = dp_min[0];
    dp_max[1] = dp_min[1];
    dp_max[2] = dp_min[2];
    
    for (int i = 1; i < N; i++){
        int a, b, c;
        cin >> a >> b >> c;
        
        next_min[0] = a + min(dp_min[0], dp_min[1]);
        next_min[1] = b + min({dp_min[0], dp_min[1], dp_min[2]});
        next_min[2] = c + min(dp_min[1], dp_min[2]);
        
        next_max[0] = a + max(dp_max[0], dp_max[1]);
        next_max[1] = b + max({dp_max[0], dp_max[1], dp_max[2]});
        next_max[2] = c + max(dp_max[1], dp_max[2]);
        
        for (int j = 0; j < 3; j++){
            dp_min[j] = next_min[j];
            dp_max[j] = next_max[j];
        }
    }
    
    int max_ans = max({dp_max[0], dp_max[1], dp_max[2]});
    int min_ans = min({dp_min[0], dp_min[1], dp_min[2]});
    cout << max_ans << " " << min_ans << "\n";
    
    return 0;
}