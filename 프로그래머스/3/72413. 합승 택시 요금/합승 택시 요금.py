def floyd_warshall(n, fares):                                     # F01
    INF = 10**12                                                  # F02
    dist = [[INF]*(n+1) for _ in range(n+1)]                      # F03
    for i in range(1, n+1):                                       # F04
        dist[i][i] = 0                                            # F05
    for u, v, w in fares:                                         # F06
        if w < dist[u][v]:                                        # F07
            dist[u][v] = dist[v][u] = w                           # F08

    for k in range(1, n+1):                                       # F09
        for i in range(1, n+1):                                   # F10
            dik = dist[i][k]                                      # F11
            if dik == INF:                                        # F12
                continue                                          # F13
            for j in range(1, n+1):                               # F14
                nk = dik + dist[k][j]                             # F15
                if nk < dist[i][j]:                               # F16
                    dist[i][j] = nk                               # F17
    return dist                                                   # F18

def solution(n, s, a, b, fares):                               # F19
    dist = floyd_warshall(n, fares)                               # F20
    return min(dist[s][k] + dist[k][a] + dist[k][b]               # F21
               for k in range(1, n+1))                            # F22

