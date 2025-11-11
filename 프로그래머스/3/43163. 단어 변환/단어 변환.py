"""
1. 한번에 한개의 알파벳만 바꿀 수
2. words에 있는 단어로만 변환할 수 있음 

begin이 "hit", target가 "cog"
words가 ["hot","dot","dog","lot","log","cog"]라면
"hit" -> "hot" -> "dot" -> "dog" -> "cog"와 같이 4단계를 거쳐 변환
words 내의 단어들을 중간과정처럼 활용할 수 있다. 

최소 몇 단계의 과정을 거쳐 begin을 target으로 변환할 수 있는지
begin과 target은 같지 않습니다.

일단 worst case를 생각해볼까? 

어떤 노드 X가 큐에서 처음 빠져나오는 순간,
그 전에 큐에는 항상 더 짧은 거리의 노드들만 있었고,
그 노드들 이웃은 이미 다 처리된 상태

어떤 노드 v가 있는데, 
v에 도달하는 여러 경로가 있을 수 있지만,
가장 짧은 경로의 길이를 k라고 하자.

거리 0인 노드들(= 시작점) 다 탐색 -> 거리 1인 노드들 다 탐색 -> ... -> 거리 k-1인 노드들 다 탐색 -> 그리고 나서야 거리 k인 노드들이 큐에서 빠져나오며 탐색됨

v의 최단 거리가 k라면:v는 거리 k 레벨에서 처음 등장할 수밖에 없음 거리 < k인 레벨에서 v가 나올 수는 없음 (그럼 최단 거리가 k가 아니니까)
so, BFS가 v를 처음 방문한 순간의 depth가 곧 최단 거리 k가 된다. 
그리고 BFS는 “이미 방문한 노드”는 다시 큐에 안 넣기 때문에, 더 긴 경로로 v에 다시 오는 건 그냥 무시됨.
"""

from queue import Queue

def solution(begin, target, words):
    answer = 0
    print(words)
    visited = [0 for i in range(0,len(words))]
    print(visited)
    
    q=Queue()
    q.put((begin,0))
    
    res=0
    
    while not q.empty():
        cw,depth= q.get()
        
        if(cw == target):
            res=depth
            break
        
        for i,nw in enumerate(words):
            if visited[i]:
                continue
            if len(cw) == len(nw) and sum(c1 != c2 for c1, c2 in zip(cw, nw)) <= 1:
                q.put((nw,depth+1))
                visited[i]=1
    print(res)
    answer=res

    
    
    return answer