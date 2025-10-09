from collections import defaultdict

# 시작
best = 0


def backtrack(sheep, wolf, candidates, info, tree):
    global best
    best = max(best, sheep)

    for v in list(candidates):
        ns, nw = sheep, wolf
        if info[v] == 0: ns += 1
        else: nw += 1

        if ns <= nw:           # 제약 위반 → 이 분기는 종료
            continue

        next_cand = (candidates - {v}) | set(tree[v])  # 후보집합 전개
        backtrack(ns, nw, next_cand, info, tree)

def solution(info, edges):
    
    # 트리 dd 만들기
    tree = defaultdict(list)
    for parent, child in edges:
        tree[parent].append(child)

    start_cand = set(tree[0]) # children of root
    backtrack(sheep=1, wolf=0, candidates=start_cand, info=info, tree=tree)
    
    return best
