
def balance_judge(s,end):
    
    if s[:end+1].count("(")==s[:end+1].count(")"):
        return end
    return -1

def split_uv(w):
    for end in range(1,len(w)+1):
        if balance_judge(w,end)!=-(1):
           uend=end
           print(w[:end+1])
           break
    # u,v 리턴
    return w[:uend+1], w[uend+1:], uend
    
def right(s):
    
    if s[0] =='(':
        depth=1
    elif s[0] == ')':
        depth=-1
    
    # depth 판단
    for i in range(1,len(s)):
        if s[i] =='(':
            depth+=1
        elif s[i] == ')':
            depth-=1
    
        
    if depth == 0 and s[:int(len(s)/2)].count('(') >= s[:int(len(s)/2)].count(')'):
        return True
    return False
     
def whole(w):
    # step1
    if(len(w)==0):return ''
             
    # step2
    # - 길이 2 이상일 경우
    u,v,split = split_uv(w)
    print(u,v)
    
    # step3
    if right(u):
        res=u+whole(v)
        return res
    else:
        temp_v=whole(v)
        temp_u=u[1:split]
        # 반전 - flip
        # temp_u = ''.join(')' if '(' else '(' for s in temp_u)
        temp_u = ''.join(')' if s=='(' else '(' for s in temp_u)
        
            
        return "("+temp_v+")"+temp_u
   
def solution(p):
    answer=whole(p)
    return answer