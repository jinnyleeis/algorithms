#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc_num;
    cin >> tc_num;

    for (int i = 0; i < tc_num; i++) {
        int dress_num;
        cin >> dress_num;

        map<string, int> dress_types;

        for (int n = 0; n < dress_num; n++) {
            string dress_name, dress_type;
            cin >> dress_name >> dress_type;
            dress_types[dress_type]++;
        }

        int total_combinations = 1;
        for (const auto &pair : dress_types) {
            total_combinations *= (pair.second + 1);
        }

        // 알몸인 상태(모든 옷을 입지 않은 경우)를 제외
        total_combinations -= 1;

        cout << total_combinations << "\n";

        // 초기화
        dress_types.clear();
    }

    return 0;
}
