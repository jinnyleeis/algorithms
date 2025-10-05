# ---------------------------
# 회전 (zip 없이 인덱스만)
# ---------------------------
def rotate_right(mat):
    """시계 90도 회전"""
    n = len(mat)
    res = [[0]*n for _ in range(n)]
    for r in range(n):
        for c in range(n):
            res[c][n-1-r] = mat[r][c]
    return res

def rotate_left(mat):
    """반시계 90도 (필요시 사용)"""
    n = len(mat)
    res = [[0]*n for _ in range(n)]
    for r in range(n):
        for c in range(n):
            res[n-1-c][r] = mat[r][c]
    return res

def rotate_180(mat):
    """180도 (필요시 사용)"""
    n = len(mat)
    res = [[0]*n for _ in range(n)]
    for r in range(n):
        for c in range(n):
            res[n-1-r][n-1-c] = mat[r][c]
    return res


# -----------------------------------
# 오프셋(ox, oy)에서의 겹침 검사 
# -----------------------------------
def overlay_ok(lock, key, ox, oy):
    """
    lock(NxN), key(MxM)을 lock 좌표계에서 (ox, oy)만큼 평행이동했을 때:
      - 겹치는 영역에서 1&1(돌기-돌기) 충돌이 있으면 False
      - 겹치는 영역을 OR로 메우고 난 뒤 lock 전체가 모두 1이면 True
      - 아니면 False
    ox: 열 방향 오프셋(+면 오른쪽), oy: 행 방향 오프셋(+면 아래쪽)
    """
    N = len(lock)
    M = len(key)

    # lock 좌표계에서의 교집합 범위
    li0 = max(0, oy)
    li1 = min(N, oy + M)
    lj0 = max(0, ox)
    lj1 = min(N, ox + M)

    # 교집합이 없으면 홈(0)을 채울 수 없으므로 실패
    if li0 >= li1 or lj0 >= lj1:
        return False

    # filled: lock을 복사해서 교집합에서 OR 시뮬레이션
    filled = [row[:] for row in lock]

    for li in range(li0, li1):
        ki = li - oy  # key의 행 인덱스(항상 0..M-1)
        for lj in range(lj0, lj1):
            kj = lj - ox  # key의 열 인덱스(항상 0..M-1)
            kv = key[ki][kj]
            lv = lock[li][lj]

            # 돌기-돌기 충돌 금지
            if kv == 1 and lv == 1:
                return False

            # 홈(0)을 열쇠(1)로 채우기
            if lv == 0 and kv == 1:
                filled[li][lj] = 1

    # lock 전체가 전부 1인지 확인(모든 홈이 채워졌는가?)
    for i in range(N):
        for j in range(N):
            if filled[i][j] == 0:
                return False
    return True


# ---------------------------
# 솔루션
# ---------------------------
def solution(key, lock):
    N = len(lock)
    M = len(key)

    cur = [row[:] for row in key]  # 현재 회전 상태의 키

    # 0°, 90°, 180°, 270° 회전 각각 시도
    for _ in range(4):
        # 가능한 오프셋 스윕: -(M-1) .. (N-1)
        for oy in range(-(M-1), N):
            for ox in range(-(M-1), N):
                if overlay_ok(lock, cur, ox, oy):
                    return True
        # 다음 회전
        cur = rotate_right(cur)

    return False


# ---------------------------
# 테스트
# ---------------------------
if __name__ == "__main__":
    key = [[0, 0, 0],
           [1, 0, 0],
           [0, 1, 1]]
    lock = [[1, 1, 1],
            [1, 1, 0],
            [1, 0, 1]]
    print(solution(key, lock))  # 기대값: True
