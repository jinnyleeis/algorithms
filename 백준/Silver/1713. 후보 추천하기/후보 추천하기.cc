#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N, k;  // 사진틀의 개수와 전체 추천 횟수
    cin >> N >> k;
    
    // 학생 번호는 1부터 100까지 있으므로 배열 크기를 101로 설정
    int rec[101] = {0};   // 각 학생의 추천 횟수
    int when[101] = {0};  // 사진틀에 게시된 시점 (추천 순서)
    int cnt = 0;          // 현재 사진틀에 채워진 사진 수
    
    for (int i = 1; i <= k; ++i) {
        int stdn;
        cin >> stdn;
        
        // 이미 사진틀에 게시된 학생인 경우 추천 횟수 증가
        if(rec[stdn] > 0){
            rec[stdn]++;
        } 
        else {
            // 새 사진틀이 남아있는 경우
            if (cnt < N) {
                rec[stdn]++;
                when[stdn] = i;
                cnt++;
            }
            else {
                // 사진틀이 꽉 찬 경우, 현재 사진틀에 게시된 학생들 중에서
                // 추천 수가 가장 적고 (동률이면 게시된 지 오래된) 학생을 찾아서 삭제한다.
                int change = 0;
                int reco = 1001; // 추천횟수의 최댓값보다 큰 값으로 초기화
                for (int j = 1; j <= 100; j++) {
                    if (rec[j] > 0) {  // j번 학생이 사진틀에 게시되어 있다면
                        if (rec[j] < reco) {  // 추천 횟수가 더 적다면
                            reco = rec[j];
                            change = j;
                        } else if (rec[j] == reco) {  // 추천 횟수가 같다면
                            if (when[j] < when[change]) {  // 더 오래된 경우
                                change = j;
                            }
                        }
                    }
                }
                // 사진틀에서 삭제
                rec[change] = 0;
                when[change] = 0;
                // 새 후보 사진을 게시 (추천 횟수를 1로 초기화)
                rec[stdn] = 1;
                when[stdn] = i;
            }
        }
    }
    
    // 최종 사진틀에 남아있는 학생들의 번호를 증가하는 순서대로 출력
    vector<int> result;
    for (int i = 1; i <= 100; i++) {
        if (rec[i] > 0)
            result.push_back(i);
    }
    
    sort(result.begin(), result.end());
    
    for (int num : result)
        cout << num << " ";
    
    return 0;
}
