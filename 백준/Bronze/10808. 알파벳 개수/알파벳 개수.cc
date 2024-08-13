#include <bits/stdc++.h>


using namespace std;

map<char, int> m; // 키:문자 값-수

int main(){

    string s; // 입력받을 단어 100자 이하

    

    cin >> s ;

    for (char c = 'a'; c <= 'z'; c++) {
        m[c] = 0;
    }
    
    for(char c : s) {
     
    m[c]++; // 문자열을 순회하며 문자 개수 카운트 
    }

    //sort(m.begin(), m.end()); // 문자열을 오름차순으로 정렬

    for(auto c:m) {

        cout <<c.second<< ' '; // 문자 개수 출력


    }



    return 0;
}