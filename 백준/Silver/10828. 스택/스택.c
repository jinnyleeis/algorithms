#include <stdio.h>
#include <string.h>

#define MAX 10000

int main() {
    int N;
    scanf("%d", &N);
    
    int stack[MAX];
    int top = -1;
    
    char command[10];
    int X;
    
    for(int i = 0; i < N; i++) {
        scanf("%s", command);
        
        if(strcmp(command, "push") == 0) {
            scanf("%d", &X);
            stack[++top] = X;
        }
        else if(strcmp(command, "pop") == 0) {
            if(top == -1)
                printf("-1\n");
            else
                printf("%d\n", stack[top--]);
        }
        else if(strcmp(command, "size") == 0) {
            printf("%d\n", top + 1);
        }
        else if(strcmp(command, "empty") == 0) {
            if(top == -1)
                printf("1\n");
            else
                printf("0\n");
        }
        else if(strcmp(command, "top") == 0) {
            if(top == -1)
                printf("-1\n");
            else
                printf("%d\n", stack[top]);
        }
    }
    
    return 0;
}
