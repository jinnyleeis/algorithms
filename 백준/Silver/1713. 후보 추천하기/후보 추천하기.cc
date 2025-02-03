#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    
    vector<int> q;       // 사진틀에 게시된 학생 번호
    vector<int> num;     // 각 학생의 추천 횟수
    vector<int> posted;  // 각 학생이 사진틀에 게시된 시각 (추천이 들어온 순서, 0부터 시작)

    for (int i = 0; i < m; i++){
        int student;
        cin >> student;
        
        // 이미 사진틀에 게시되어 있는 경우
        auto it = find(q.begin(), q.end(), student);
        if (it != q.end()){
            int idx = it - q.begin();
            num[idx]++;  // 추천 횟수 증가
        } 
        else {
            // 사진틀에 빈 공간이 있는 경우 바로 추가
            if (q.size() < n){
                q.push_back(student);
                num.push_back(1);
                posted.push_back(i); // 현재 추천 순서를 기록
            }
            else {
                // 사진틀이 꽉 찼다면, 삭제 후보를 결정
                int removeIndex = 0;
                int minRec = num[0];
                int minTime = posted[0];
                
                for (int j = 1; j < q.size(); j++){
                    // 추천 횟수가 더 적은 경우
                    if (num[j] < minRec){
                        minRec = num[j];
                        minTime = posted[j];
                        removeIndex = j;
                    }
                    // 추천 횟수가 같으면, 게시된 시간이 더 오래된(작은) 경우
                    else if (num[j] == minRec && posted[j] < minTime){
                        minTime = posted[j];
                        removeIndex = j;
                    }
                }
                
                // 결정된 후보 삭제
                q.erase(q.begin() + removeIndex);
                num.erase(num.begin() + removeIndex);
                posted.erase(posted.begin() + removeIndex);
                
                // 새 학생 추가
                q.push_back(student);
                num.push_back(1);
                posted.push_back(i);
            }
        }
    }
    
    // 최종 사진틀에 남은 학생 번호를 오름차순으로 정렬 후 출력
    sort(q.begin(), q.end());
    for (int student : q)
        cout << student << " ";
    
    return 0;
}
