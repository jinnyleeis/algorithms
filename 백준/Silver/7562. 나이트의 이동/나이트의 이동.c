#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 300
#define QUEUE_SIZE (MAX * MAX)

// 나이트의 이동을 저장하는 구조체
typedef struct {
    int x;      // 현재 위치의 x 좌표
    int y;      // 현재 위치의 y 좌표
    int depth;  // 이동 횟수
} Move;

// 큐 구조체
typedef struct {
    Move data[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 큐 초기화 함수
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

// 큐에 요소 추가 (enqueue)
int enqueue(Queue *q, Move m) {
    if(q->rear >= QUEUE_SIZE) {
        // 큐가 가득 찼을 경우
        return 0;
    }
    q->data[q->rear++] = m;
    return 1;
}

// 큐에서 요소 제거 (dequeue)
int dequeue(Queue *q, Move *m) {
    if(q->front == q->rear) {
        // 큐가 비어있을 경우
        return 0;
    }
    *m = q->data[q->front++];
    return 1;
}

int main() {
    int T;  // 테스트 케이스 수
    scanf("%d", &T);
    
    // 나이트의 이동 방향 (8가지)
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    while(T--) {
        int l;  // 체스판의 크기
        scanf("%d", &l);
        
        int cx, cy, tx, ty;  // 현재 위치와 목표 위치
        scanf("%d %d", &cx, &cy);
        scanf("%d %d", &tx, &ty);
        
        // 시작 위치가 목표 위치와 같은 경우
        if(cx == tx && cy == ty) {
            printf("0\n");
            continue;
        }
        
        // 방문 배열 초기화
        int visited[MAX][MAX];
        memset(visited, 0, sizeof(visited));
        
        // 큐 초기화
        Queue q;
        initQueue(&q);
        
        // 시작 위치 enqueue
        Move start;
        start.x = cx;
        start.y = cy;
        start.depth = 0;
        enqueue(&q, start);
        visited[cx][cy] = 1;
        
        int found = 0;  // 목표 도달 여부
        Move current;
        
        while(dequeue(&q, &current)) {
            // 현재 위치에서 가능한 모든 이동 시도
            for(int i = 0; i < 8; i++) {
                int new_x = current.x + dx[i];
                int new_y = current.y + dy[i];
                int new_depth = current.depth + 1;
                
                // 체스판 범위 내에 있는지 확인
                if(new_x < 0 || new_x >= l || new_y < 0 || new_y >= l)
                    continue;
                
                // 이미 방문한 위치인지 확인
                if(visited[new_x][new_y])
                    continue;
                
                // 목표 위치에 도달한 경우
                if(new_x == tx && new_y == ty) {
                    printf("%d\n", new_depth);
                    found = 1;
                    break;
                }
                
                // 방문하지 않은 위치라면 enqueue하고 방문 표시
                Move next;
                next.x = new_x;
                next.y = new_y;
                next.depth = new_depth;
                enqueue(&q, next);
                visited[new_x][new_y] = 1;
            }
            if(found)
                break;
        }
        
        // 목표 도달하지 못한 경우 (문제의 조건에 따라 항상 도달 가능하므로 이 부분은 사실상 필요 없음)
        if(!found) {
            printf("-1\n");
        }
    }
    
    return 0;
}
