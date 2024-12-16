#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스도쿠 판을 저장하는 2차원 배열
int m[9][9];

// 특정 위치에 숫자를 놓는 것이 유효한지 검사하는 함수
int isValid(int row, int col, int num) {
    // 같은 행에 같은 숫자가 있는지 확인
    for(int i = 0; i < 9; i++) {
        if(m[row][i] == num)
            return 0; // 유효하지 않음
    }

    // 같은 열에 같은 숫자가 있는지 확인
    for(int i = 0; i < 9; i++) {
        if(m[i][col] == num)
            return 0; // 유효하지 않음
    }

    // 같은 3x3 박스에 같은 숫자가 있는지 확인
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for(int i = startRow; i < startRow + 3; i++) {
        for(int j = startCol; j < startCol + 3; j++) {
            if(m[i][j] == num)
                return 0; // 유효하지 않음
        }
    }

    return 1; // 유효함
}

// 백트래킹을 이용하여 스도쿠 판을 해결하는 함수
int solveSudoku() {
    int row, col;
    int found = 0;

    // 빈 칸을 찾음
    for(row = 0; row < 9; row++) {
        for(col = 0; col < 9; col++) {
            if(m[row][col] == 0) {
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }

    // 모든 칸이 채워졌으면 종료
    if(!found)
        return 1;

    // 1부터 9까지의 숫자를 시도
    for(int num = 1; num <= 9; num++) {
        if(isValid(row, col, num)) {
            m[row][col] = num; // 숫자를 채움

            if(solveSudoku()) // 재귀 호출
                return 1;

            m[row][col] = 0; // 백트래킹
        }
    }

    return 0; // 해결 불가능
}

int main() {
    // 스도쿠 판 입력 받기
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            scanf("%d", &m[i][j]);
        }
    }

    // 스도쿠 판 해결
    if(solveSudoku()) {
        // 해결된 스도쿠 판 출력
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
