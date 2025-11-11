from collections import defaultdict 

# 가장 근접한 개수로 전력망을 나눠야 한다. 
# 연결된 컴포넌트를 나누는걸 생각하면 되나?? - 기준을 모든 edge로 두고 
# 최단 거리 그런게 아니니까, dfs로 걍 개수만 탐색하면 된다. 

def solution(n, wires):
    
    g = defaultdict(list)
    
    for e in wires:
        g[e[0]].append(e[1])
        g[e[1]].append(e[0])
        
    print(g)

    res=9999999
    
    for i in range(0,n-1):
        print(wires[i])
        a_start=wires[i][0]
        b_start=wires[i][1]
        
        # 주의) 별개의 말판!! : 간선을 자르는 매 시도마다 visited를 새로 만들어야 한다!
        visited = [ 0 for i in range(0,n+1)]
        
        #a_cnt=0
        #b_cnt=0
        
        def dfs(c):
            visited[c]=1
            cnt=1
            for n in g[c]:
                # 전체 트리에서 a_start, b_start 각각 DFS를 도는게 아니라, “(a,b) 간선을 잘랐다”는 가정을 반영해야 하므로!
                if (c == a_start and n == b_start) or (n == b_start and n == a_start):
                    continue 
                if visited[n]:
                    continue
                cnt += dfs(n)
            return cnt # 자신까지 포함해서 끝 노드까지의 총 개수 
            
        
        a_cnt = dfs(a_start)
        b_cnt = dfs(b_start)

        res=min(abs(a_cnt-b_cnt),res)
        
    print(res)
        
        

    answer = res
    return answer



"""
현재의 전력망 네트워크를 2개로 분할하려고 함 
이때, 두 전력망이 갖게 되는 송전탑의 개수를 최대한 비슷하게 맞추고자 한다. 





"""