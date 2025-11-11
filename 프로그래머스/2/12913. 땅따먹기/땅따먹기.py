# 런타임 에러의 이유 : dp를 쓰는걸 깜빡함 정신차려라 친구야
# 한 칸에서 다음 행으로 내려갈 때 3개 열로 분기 → 호출 수가 대략 4 * 3^(N-1) 수준으로 폭발하잖닝 그래서 dp 재귀꼴 만든건데 dp 오디가쏘

"""
문제의 처음부터 끝까지 항상 만족시키는 상태의 진행 단계
row 0 1 2 ... N-2 N-1개의 state level이 존재함
dp[row][col]의 설계 현재 레벨에서부터[(row,col)에서(row 레벨)] ~
끝 레벨에까지(N-1,v(col)) 얻을 수 있는 최대 점수 

"""

import sys 
sys.setrecursionlimit(200000)  # N 최대 100000 대비 여유

def fn(c_row,c_col,N,land,dp):
    if c_row == N: 
        return 0
    if dp[c_row][c_col]!=-1:
        return dp[c_row][c_col]
    
    res=0
    for n_col in range(0,4):
        if n_col == c_col:
            continue   
        n_row = c_row+1
        res = max(fn(n_row,n_col,N,land,dp)+land[c_row][c_col],res)
        
        dp[c_row][c_col]=res
        
    return dp[c_row][c_col]
    
    
def solution(land):
    answer = 0
    
    dp =[ [ -1 for c in row] for row in land]
    
    N=len(land)
    #print(m)
    
    for col in range(0,4):
        answer=max(answer,fn(0,col,N,land,dp))
        
    print(answer)


    return answer