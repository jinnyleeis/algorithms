
def solution(land):
    answer = 0
    
    dp = [ [-1 for col in row ] for row in land ]
    
    N=len(land)
    
    # 주의 : 시작 레벨을 0이 아닌, 1로 해야. 
    # 즉, 현재 레벨의(lv) 특정 변수를 variable로 (cur_col : frame의 옵션), lv-1까지는 고정된 블랙박스로.
    # -> lv-1까지는 고정되었다고 보므로, 해당 고정값을 현재 레벨에서 불가능한 케이스를 걸러내는데 사용 (cur_col!=prev_col)
    
    # bottom-up에서 base case 설정하는거 까먹지 말아야 한다!!! - level 0은 이전 레벨이 없으므로 점화식 적용 불가.
    for col in range(0,4):
        dp[0][col] = land[0][col]
    
    for c_row in range(1,N): # 레벨기준. 현재까지의 최댓값
        for c_col in range(0,4):
            p_row=c_row-1
            for p_col in range(0,4):
                if c_col == p_col:
                    continue
                dp[c_row][c_col]=max(dp[p_row][p_col]+land[c_row][c_col],dp[c_row][c_col])
    
    for c_col in range(0,4):
        answer=max(answer,dp[N-1][c_col])
        
    

    return answer