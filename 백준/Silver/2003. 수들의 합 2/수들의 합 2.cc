#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int arr[10004];
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    int s = 1, e = 1;  // 시작 포인터 s, 끝 포인터 e
    int sum = 0;       // 현재 구간의 합
    int cnt = 0;       // 조건(sum == m)을 만족하는 경우의 수

    // e가 n+1까지 갈 수 있으므로 while문의 조건은 e <= n+1로 
    while (s <= e && e <= n + 1) {
        if (sum >= m) {
            if (sum == m)
                cnt++;
            sum -= arr[s]; // 구간의 시작 위치 값을 빼줌
            s++;           // s를 오른쪽으로 이동
        } else {
            // e가 n+1이면 더 이상 추가할 원소가 없으므로 while문을 종료
            if (e > n)
                break;
            sum += arr[e]; // 구간에 새로운 원소 추가
            e++;           // e를 오른쪽으로 이동
        }
    }

    cout << cnt << "\n";
    return 0;
}
