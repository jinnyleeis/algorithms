#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int MAX_LEN = 26;
int n, k;
int ans = 0;         // 읽을 수 있는 단어의 최대 개수
int CNT;             // 추가로 선택해야 하는 글자 수 (기본 5글자 제외)

// 각 단어가 필요로 하는 글자들을 표시 (n<=50, 알파벳 26개)
bool arr[51][26] = {false};
// 선택한 글자들을 표시 (알파벳 26개)
bool choice[26] = {false};

void DFS(int idx, int number) {
    // 추가로 선택한 글자가 CNT개가 되면, 각 단어를 읽을 수 있는지 검사
    if (number == CNT) {
        int Can = 0;
        for (int i = 0; i < n; ++i) {
            bool flag = true;
            for (int j = 0; j < MAX_LEN; ++j) {
                // 단어 i가 j번 글자를 필요로 하는데 선택하지 않았다면 읽을 수 없음
                if (arr[i][j] && !choice[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                Can++;
        }
        ans = max(Can, ans);
        return;
    }
    // 알파벳 전체(0~25)를 다 고려했으면 종료
    if (idx >= MAX_LEN)
        return;
    
    // 이미 기본 글자(a,n,t,i,c)는 선택되어 있으므로, 그 경우에는 DFS만 진행
    if (choice[idx]) {
        DFS(idx + 1, number);
    }
    else {
        // 이 글자를 선택하지 않는 경우
        DFS(idx + 1, number);
        // 이 글자를 선택하는 경우
        choice[idx] = true;
        DFS(idx + 1, number + 1);
        choice[idx] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    // 기본 5글자 없이는 어떤 단어도 읽을 수 없음
    if (k < 5) {
        cout << 0 << "\n";
        return 0;
    }
    // 모든 글자를 가르칠 수 있다면 모든 단어 읽을 수 있음
    if (k == 26) {
        cout << n << "\n";
        return 0;
    }
    
    // 기본으로 반드시 포함되어야 하는 글자: a, n, t, i, c
    choice['a' - 'a'] = true;
    choice['n' - 'a'] = true;
    choice['t' - 'a'] = true;
    choice['i' - 'a'] = true;
    choice['c' - 'a'] = true;
    
    // 단어들을 입력받으며 각 단어가 필요한 글자를 표시
    for (int i = 0; i < n; ++i) {
        string A;
        cin >> A;
        // 단어 전체에 대해 필요한 글자를 체크 (문제 조건상 접두사 "anta", 접미사 "tica"가 있으므로)
        for (char curr : A) {
            arr[i][curr - 'a'] = true;
        }
    }
    
    // 추가로 선택할 수 있는 글자 수 (기본 5글자 제외)
    CNT = k - 5;
    
    DFS(0, 0);
    
    cout << ans << "\n";
    return 0;
}
