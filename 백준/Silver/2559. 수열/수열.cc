#include <bits/stdc++.h>

using namespace std;

int days, term;
vector<int> temp;
int temperature;

int main() {
    cin >> days >> term;
    
    for (int i = 0; i < days; i++) {
        cin >> temperature;
        temp.push_back(temperature);
    }
    
    int current_sum = 0;
    for (int i = 0; i < term; i++) {
        current_sum += temp[i];
    }
    
    int max_sum = current_sum;
    for (int i = term; i < days; i++) {
        current_sum += temp[i] - temp[i - term];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    
    cout << max_sum << endl;

    return 0;
}