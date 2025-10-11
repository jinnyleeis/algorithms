def solution(n, m, x, y, r, c, k):
    # 1-based
    def dist(ax, ay, bx, by):
        return abs(ax - bx) + abs(ay - by)

    need0 = dist(x, y, r, c)
    if need0 > k or ((k - need0) % 2 == 1):
        return "impossible"

    # 사전순: d < l < r < u
    moves = [('d', 1, 0), ('l', 0, -1), ('r', 0, 1), ('u', -1, 0)]

    # 현재 층: 각 칸의 사전순 최소 문자열(없으면 None)
    cur = [[None] * (m + 1) for _ in range(n + 1)]
    cur[x][y] = ""  # 시작점, 0글자

    # t 번 이동을 마친 뒤의 표에서 -> t+1 로 확장
    for t in range(k):
        rem_after = k - (t + 1)  # 다음 칸에서 남을 이동 수
        nxt = [[None] * (m + 1) for _ in range(n + 1)]
        for i in range(1, n + 1):
            row = cur[i]
            for j in range(1, m + 1):
                base = row[j]
                if base is None:
                    continue
                # 현재 (i,j)에서 네 방향 시도
                for ch, dx, dy in moves:
                    ni, nj = i + dx, j + dy
                    if not (1 <= ni <= n and 1 <= nj <= m):
                        continue
                    # 다음 칸에서 남은 rem_after 로 목표에 도달 가능?
                    need = dist(ni, nj, r, c)
                    if need > rem_after or ((rem_after - need) % 2 == 1):
                        continue
                    cand = base + ch
                    best = nxt[ni][nj]
                    if best is None or cand < best:
                        nxt[ni][nj] = cand
        cur = nxt

    return cur[r][c] if cur[r][c] is not None else "impossible"

