import collections

n = m = 0
ny = nx = 0

# 원래 있던 8방향 벡터는 유지하되, 실제 이동은 4방향을 따로 
dx = [1, 1, 0, -1, -1, -1, 0, 1]
dy = [0, -1, -1, -1, 0, 1, 1, 1]

mp = []          # 2차원 맵 (0/1)
dp = None        # 4차원 DP '개념'을 dict로 실현: dp[(y1,x1,y2,x2)] = 최소시간
visited = None   # 방문 여부 set: {(y1,x1,y2,x2)}

def _in_bounds(y, x):
    return 0 <= y < n and 0 <= x < n

def _empty(y, x):
    return _in_bounds(y, x) and mp[y][x] == 0

def _norm(y1, x1, y2, x2):
    """상태 정규화(사전식): (y1,x1) <= (y2,x2) 가 되도록 스왑"""
    if (y2 < y1) or (y2 == y1 and x2 < x1):
        return y2, x2, y1, x1
    return y1, x1, y2, x2

def solution(board):
    """
    board: 0/1 정수의 N x N 리스트
    반환: (N-1,N-1)에 도달하는 최소 시간
    """
    global n, m, mp, dp, visited
    mp = [row[:] for row in board]
    n = m = len(mp)

    # 시작 상태: (0,0) & (0,1) 가로 배치 (항상 0 보장)
    y1, x1, y2, x2 = _norm(0, 0, 0, 1)

    # 4차원 DP 컨셉을 dict로 구현 (희소)
    dp = {}
    visited = set()

    # BFS
    q = collections.deque()
    dp[(y1, x1, y2, x2)] = 0
    visited.add((y1, x1, y2, x2))
    q.append((y1, x1, y2, x2))

    # 4방향 이동용
    d4 = [(-1,0), (1,0), (0,-1), (0,1)]

    while q:
        y1, x1, y2, x2 = q.popleft()
        t = dp[(y1, x1, y2, x2)]

        # 목표 칸에 두 칸 중 하나라도 도달하면 종료
        if (y1, x1) == (n-1, n-1) or (y2, x2) == (n-1, n-1):
            return t

        # ----- 1) 평행이동 (상/하/좌/우) -----
        for dy4, dx4 in d4:
            ny1, nx1 = y1 + dy4, x1 + dx4
            ny2, nx2 = y2 + dy4, x2 + dx4
            if _empty(ny1, nx1) and _empty(ny2, nx2):
                s = _norm(ny1, nx1, ny2, nx2)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)

        # ----- 2) 회전 -----
        if y1 == y2:
            # 가로 상태 → 위/아래로 세로 회전 (각 끝을 축으로)
            # 위로 회전: 두 칸 위가 모두 비어야 함
            if _empty(y1-1, x1) and _empty(y2-1, x2):
                # (y1,x1)을 축으로 위로 회전 → (y1-1,x1) & (y1,x1)
                s = _norm(y1-1, x1, y1, x1)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
                # (y2,x2)을 축으로 위로 회전 → (y2-1,x2) & (y2,x2)
                s = _norm(y2-1, x2, y2, x2)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
            # 아래로 회전: 두 칸 아래가 모두 비어야 함
            if _empty(y1+1, x1) and _empty(y2+1, x2):
                # (y1,x1)을 축으로 아래로 회전 → (y1,x1) & (y1+1,x1)
                s = _norm(y1, x1, y1+1, x1)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
                # (y2,x2)을 축으로 아래로 회전 → (y2,x2) & (y2+1,x2)
                s = _norm(y2, x2, y2+1, x2)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)

        elif x1 == x2:
            # 세로 상태 → 좌/우로 가로 회전
            # 왼쪽 회전: 두 칸 왼쪽이 모두 비어야 함
            if _empty(y1, x1-1) and _empty(y2, x2-1):
                # (y1,x1)을 축으로 왼쪽 회전 → (y1,x1-1) & (y1,x1)
                s = _norm(y1, x1-1, y1, x1)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
                # (y2,x2)을 축으로 왼쪽 회전 → (y2,x2-1) & (y2,x2)
                s = _norm(y2, x2-1, y2, x2)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
            # 오른쪽 회전: 두 칸 오른쪽이 모두 비어야 함
            if _empty(y1, x1+1) and _empty(y2, x2+1):
                # (y1,x1)을 축으로 오른쪽 회전 → (y1,x1) & (y1,x1+1)
                s = _norm(y1, x1, y1, x1+1)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)
                # (y2,x2)을 축으로 오른쪽 회전 → (y2,x2) & (y2,x2+1)
                s = _norm(y2, x2, y2, x2+1)
                if s not in visited:
                    visited.add(s)
                    dp[s] = t + 1
                    q.append(s)

    # 문제 조건상 항상 도달 가능이라 여기 안 옴
    return -1

