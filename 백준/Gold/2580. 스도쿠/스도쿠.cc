#include<bits/stdc++.h>

using namespace std;

int m[9][9];

bool isValid(int row, int col, int num) {
    // 해당 행에 같은 숫자가 있는지 확인
    for (int i = 0; i < 9; i++) {
        if (m[row][i] == num) return false;
    }

    // 해당 열에 같은 숫자가 있는지 확인
    for (int i = 0; i < 9; i++) {
        if (m[i][col] == num) return false;
    }

    // 해당 3x3 박스에 같은 숫자가 있는지 확인
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (m[i][j] == num) return false;
        }
    }

    return true;
}

bool solveSudoku() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (m[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(row, col, num)) {
                        m[row][col] = num;
                        if (solveSudoku()) return true;
                        m[row][col] = 0; // 백트래킹
                    }
                }
                return false;
            }
        }
    }
    return true; // 모든 칸이 채워졌을 때
}

int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> m[i][j];
        }
    }
    
    // 문제에서 경우의 수 1개 무조건 있다곤 했지만 일단 걍 조건문 걸어 
    if(solveSudoku()){
    
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << m[i][j] << " ";
            }
            cout << "\n";
        }
        
    }
    

    return 0;
}