#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    for(int i = 1; i <= N; i++) {
        // 공백 출력
        for(int j = 0; j < N - i; j++) {
            printf(" ");
        }
        
        if(i == 1) {
            // 첫 번째 줄은 별 하나
            printf("*\n");
        }
        else if(i < N) {
            // 중간 줄은 별, 공백, 별
            printf("*");
            for(int j = 0; j < 2*(i-1)-1; j++) {
                printf(" ");
            }
            printf("*\n");
        }
        else {
            // 마지막 줄은 모든 위치에 별
            for(int j = 0; j < 2*N-1; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    
    return 0;
}
