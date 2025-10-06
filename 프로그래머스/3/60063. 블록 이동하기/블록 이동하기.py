from queue import Queue                     

H, V = 0, 1                                                      
MOVES = [(-1,0), (1,0), (0,-1), (0,1)]                         

def in_bounds(y, x, N):   
    if(y<0 or y>=N or x<0 or x>=N):
        return False
    return True

# 경계 내에 있고, empty인 경우
def empty(y, x, Board, N):
    return in_bounds(y,x,N) and Board[y][x]==0
  

# 해당 말 범위를 리턴한다. 
def cells_of(y, x, ori):  
    if ori==H:
        return (y,x),(y,x+1)
    else: 
        return (y,x),(y+1,x)
   

# 이건, 그 회전할 때 범위까지 생각해야한다!!!!
# 기존 위치에서 --> 새로운 위치 중간의 과정까지 고려해야하는 경우다. -> 아 이건 neighbors에서.
# can_place는 정지된 말 자체의 위치에 대해서만.
# 기본적인 오버플로우랑 / 장애물 여부 체크도.
def can_place(y, x, ori, Board, N):  
    (y1,x1), (y2,x2) = cells_of(y,x,ori)
    return empty(y1,x1,Board, N) and empty(y2,x2,Board, N) # 둘 다 비어있어야 해당 위치로 이동 가능하다.
    
    
def neighbors(y, x, ori, Board, N):   
    res = []
    # 기본 상하좌우의 이동 
    for dy,dx in MOVES:
        # 기준 왼/위쪽 (더 출발점이란 가까운 애 기준으로 조사하고 can_place에서 한번에.)
        ny=y+dy
        nx=x+dx
        if(can_place(ny,nx,ori,Board,N)):
            res.append((ny,nx,ori))
    
    if ori == H:
        # 아래로 세우기: 아랫줄 두 칸이 0
        if empty(y+1, x, Board, N) and empty(y+1, x+1, Board, N):
            if can_place(y,   x,   V, Board, N): res.append((y,   x,   V))
            if can_place(y,   x+1, V, Board, N): res.append((y,   x+1, V))
        # 위로 세우기: 윗줄 두 칸이 0
        if empty(y-1, x, Board, N) and empty(y-1, x+1, Board, N):
            if can_place(y-1, x,   V, Board, N): res.append((y-1, x,   V))
            if can_place(y-1, x+1, V, Board, N): res.append((y-1, x+1, V))

    if ori == V:
        # 왼쪽으로 눕히기: 왼쪽열 두 칸이 0
        if empty(y,   x-1, Board, N) and empty(y+1, x-1, Board, N):
            if can_place(y,   x-1, H, Board, N): res.append((y,   x-1, H))
            if can_place(y+1, x-1, H, Board, N): res.append((y+1, x-1, H))
        # 오른쪽으로 눕히기  ← 결과 좌표는 (y,x,H), (y+1,x,H)
        if empty(y,   x+1, Board, N) and empty(y+1, x+1, Board, N):
            if can_place(y,   x,   H, Board, N): res.append((y,   x,   H))  
            # 이거 새로운 출발점쪽 기준점 좌표여야 하므로
            # was (y, x+1, H)
            if can_place(y+1, x,   H, Board, N): res.append((y+1, x,   H))     
            # was (y+1, x+1, H)
    return res

    
def is_goal(y, x, ori, N):
    (y1,x1), (y2,x2) = cells_of(y, x, ori)
    return (y1==N-1 and x1==N-1) or (y2==N-1 and x2==N-1)
    
def bfs(y,x,ori,N,Board):
    q = Queue()
    q.put(((y,x,ori),0))

    # -------------------------------
    # (여기만 수정) 리스트가 아니라 dict로!
    # -------------------------------
    visited = {}                       # ← 딕셔너리로 변경
    visited[(y,x,ori)] = True

    while not q.empty():
        ((y,x,ori),value) = q.get()
        if is_goal(y, x, ori, N):
            return value
        
        for ny,nx,nd in neighbors(y, x, ori, Board, N):
            if visited.get((ny,nx,nd), False):
                continue
            q.put(((ny,nx,nd),value+1))
            visited[(ny,nx,nd)]=True
    return -1
    

def solution(Board):  
    N=len(Board)
    #print(N)
    return bfs(0,0,H,N,Board)



