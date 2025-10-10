def solution(n, m, x, y, r, c, k):
    # --- 전처 심판: 처음부터 물리적으로 불가능한가? ---
    def manhattan(a, b, c, d):
        return abs(a - c) + abs(b - d)

    need0 = manhattan(x, y, r, c)
    if need0 > k or ((k - need0) % 2 == 1):
        return "impossible"

    # --- 심판 규칙: 다음 칸에서 남은 걸음으로 목표에 도달 가능? ---
    def can_reach(nx, ny, rem):
        need = manhattan(nx, ny, r, c)
        return need <= rem and ((rem - need) % 2 == 0)

    # 사전 순 최소가 되도록 d, l, r, u 순으로 시도
    moves = [
        ('d', 1, 0),
        ('l', 0, -1),
        ('r', 0, 1),
        ('u', -1, 0),
    ]

    curx, cury = x, y
    remain = k
    path = []

    # --- 말 놓기(컷) k번: 매번 사전 순으로 가능한 첫 컷을 확정 ---
    for _ in range(k):
        for ch, dx, dy in moves:
            nx, ny = curx + dx, cury + dy
            if 1 <= nx <= n and 1 <= ny <= m and can_reach(nx, ny, remain - 1):
                path.append(ch)
                curx, cury = nx, ny
                remain -= 1
                break
        else:
            # 어떤 방향도 심판 통과 못하면 불가능
            return "impossible"

    return "".join(path)

