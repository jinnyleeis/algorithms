def to_sec(t: str) -> int:                                     # L01
    h, m, s = map(int, t.split(":"))                           # L02
    return h*3600 + m*60 + s                                   # L03

def to_time(x: int) -> str:                                    # L04
    h, x = divmod(x, 3600)                                     # L05
    m, s = divmod(x, 60)                                       # L06
    return f"{h:02d}:{m:02d}:{s:02d}"                          # L07

def build_prefix(logs, play: int):                             # L08
    diff = [0]*(play+2)                                        # L09
    for log in logs:                                           # L10
        s, e = log.split("-")                                  # L11
        s, e = to_sec(s), to_sec(e)                            # L12
        diff[s] += 1                                           # L13
        diff[e] -= 1                                           # L14

    viewers = [0]*(play+1)                                     # L15
    cur = 0                                                    # L16
    for t in range(play+1):                                    # L17
        cur += diff[t]                                         # L18
        viewers[t] = cur                                       # L19

    prefix = [0]*(play+1)                                      # L20
    prefix[0] = viewers[0]                                     # L21
    for t in range(1, play+1):                                 # L22
        prefix[t] = prefix[t-1] + viewers[t]                   # L23
    return prefix                                              # L24

def window_sum(prefix, start: int, adv: int) -> int:           # L25
    end = start + adv - 1                                      # L26
    if start == 0:                                             # L27
        return prefix[end]                                     # L28
    return prefix[end] - prefix[start-1]                       # L29

def solution(play_time: str, adv_time: str, logs):             # L30
    play = to_sec(play_time)                                   # L31
    adv  = to_sec(adv_time)                                    # L32
    if adv == 0 or play == 0:                                  # L33
        return "00:00:00"                                      # L34
    if adv > play:                                             # L35
        adv = play                                             # L36

    prefix = build_prefix(logs, play)                          # L37

    best_start = 0                                             # L38
    best_sum   = window_sum(prefix, 0, adv)                    # L39

    for start in range(1, play - adv + 1):                     # L40
        s = window_sum(prefix, start, adv)                     # L41
        if s > best_sum:                                       # L42
            best_sum = s                                       # L43
            best_start = start                                 # L44

    return to_time(best_start)                                 # L45

