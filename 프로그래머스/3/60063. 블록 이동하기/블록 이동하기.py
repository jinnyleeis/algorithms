from collections import deque                                   # L01

H, V = 0, 1                                                      # L02
MOVES = [(-1,0), (1,0), (0,-1), (0,1)]                          # L03

def in_bounds(y, x, N):                                         # L04
    return 0 <= y < N and 0 <= x < N                            # L05

def empty(y, x, Board, N):                                      # L06
    return in_bounds(y, x, N) and Board[y][x] == 0              # L07

def cells_of(y, x, ori):                                        # L08
    if ori == H:                                                # L09
        return (y, x), (y, x+1)                                 # L10
    else:                                                       # L11
        return (y, x), (y+1, x)                                 # L12

def can_place(y, x, ori, Board, N):                             # L13
    (y1, x1), (y2, x2) = cells_of(y, x, ori)                    # L14
    return empty(y1, x1, Board, N) and empty(y2, x2, Board, N)  # L15

def neighbors(y, x, ori, Board, N):                             # L16
    res = []                                                    # L17
    # 1) 평행이동 4방향
    for dy, dx in MOVES:                                        # L18
        ny, nx = y + dy, x + dx                                 # L19
        if can_place(ny, nx, ori, Board, N):                    # L20
            res.append((ny, nx, ori))                           # L21

    # 2) 회전
    if ori == H:                                                # L22
        # 위로 세우기: 윗줄 2칸이 0
        if y-1 >= 0 and Board[y-1][x] == 0 and Board[y-1][x+1] == 0:  # L23
            if can_place(y-1, x, V, Board, N):                  # L24
                res.append((y-1, x, V))                         # L25
            if can_place(y-1, x+1, V, Board, N):                # L26
                res.append((y-1, x+1, V))                       # L27
        # 아래로 세우기: 아랫줄 2칸이 0
        if y+1 < N and Board[y+1][x] == 0 and Board[y+1][x+1] == 0:   # L28
            if can_place(y, x, V, Board, N):                    # L29
                res.append((y, x, V))                           # L30
            if can_place(y, x+1, V, Board, N):                  # L31
                res.append((y, x+1, V))                         # L32
    else:  # ori == V                                           # L33
        # 왼쪽으로 눕히기: 왼줄 2칸이 0
        if x-1 >= 0 and Board[y][x-1] == 0 and Board[y+1][x-1] == 0:  # L34
            if can_place(y,   x-1, H, Board, N):                # L35
                res.append((y,   x-1, H))                       # L36
            if can_place(y+1, x-1, H, Board, N):                # L37
                res.append((y+1, x-1, H))                       # L38
        # 오른쪽으로 눕히기: 오른줄 2칸이 0
        if x+1 < N and Board[y][x+1] == 0 and Board[y+1][x+1] == 0:   # L39
            if can_place(y,   x, H, Board, N):                  # L40
                res.append((y,   x, H))                         # L41
            if can_place(y+1, x, H, Board, N):                  # L42
                res.append((y+1, x, H))                         # L43
    return res                                                  # L44

def is_goal(y, x, ori, N):                                      # L45
    (a1, b1), (a2, b2) = cells_of(y, x, ori)                    # L46
    return (a1 == N-1 and b1 == N-1) or (a2 == N-1 and b2 == N-1)  # L47

def solution(Board):                                                 # L48
    N = len(Board)                                              # L49
    start = (0, 0, H)                                           # L50
    q = deque([(start, 0)])                                     # L51
    visited = set([start])                                      # L52
    while q:                                                    # L53
        (y, x, ori), d = q.popleft()                            # L54
        if is_goal(y, x, ori, N):                               # L55
            return d                                            # L56
        for ny, nx, nori in neighbors(y, x, ori, Board, N):     # L57
            state = (ny, nx, nori)                              # L58
            if state not in visited:                            # L59
                visited.add(state)                              # L60
                q.append((state, d+1))                          # L61
    return -1                                                   # L62
