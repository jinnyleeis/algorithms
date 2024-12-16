#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 최대 체스판 크기
#define MAX 300

// 이동 가능한 8가지 방향
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 큐 구조체 정의
typedef struct {
    int x;
    int y;
    int moves;
} Queue;

int main() {
    int T;
    scanf("%d", &T);
    
    while(T--) {
        int l;
        scanf("%d", &l);
        
        int start_x, start_y, end_x, end_y;
        scanf("%d %d", &start_x, &start_y);
        scanf("%d %d", &end_x, &end_y);
        
        // 방문 배열 초기화
        int visited[MAX][MAX];
        memset(visited, 0, sizeof(visited));
        
        // 큐 초기화
        Queue queue[MAX*MAX];
        int front = 0, rear = 0;
        
        // 시작 위치 enqueue
        queue[rear].x = start_x;
        queue[rear].y = start_y;
        queue[rear].moves = 0;
        rear++;
        visited[start_x][start_y] = 1;
        
        int result = -1;
        
        // BFS 수행
        while(front < rear) {
            Queue current = queue[front++];
            
            // 도착지에 도달하면 결과 저장 후 종료
            if(current.x == end_x && current.y == end_y) {
                result = current.moves;
                break;
            }
            
            // 8가지 방향으로 이동
            for(int i = 0; i < 8; i++) {
                int new_x = current.x + dx[i];
                int new_y = current.y + dy[i];
                
                // 체스판 범위 내인지 확인
                if(new_x >= 0 && new_x < l && new_y >= 0 && new_y < l && !visited[new_x][new_y]) {
                    queue[rear].x = new_x;
                    queue[rear].y = new_y;
                    queue[rear].moves = current.moves + 1;
                    rear++;
                    visited[new_x][new_y] = 1;
                }
            }
        }
        
        printf("%d\n", result);
    }
    
    return 0;
}
