def solution(play_time, adv_time, logs):
    def to_sec(t):
        h, m, s = map(int, t.split(":"))
        return h*3600 + m*60 + s
    def to_time(x):
        h, x = divmod(x, 3600)
        m, s = divmod(x, 60)
        return f"{h:02d}:{m:02d}:{s:02d}"

    play = to_sec(play_time)
    adv = to_sec(adv_time)
    if adv > play:
        adv = play

    diff = [0]*(play+2)
    for log in logs:
        s, e = log.split("-")
        s, e = to_sec(s), to_sec(e)
        diff[s] += 1
        diff[e] -= 1

    viewers = [0]*(play+1)
    cur = 0
    for t in range(play+1):
        cur += diff[t]
        viewers[t] = cur

    prefix = [0]*(play+1)
    prefix[0] = viewers[0]
    for t in range(1, play+1):
        prefix[t] = prefix[t-1] + viewers[t]

    max_sum = -1
    best_start = 0
    if adv == 0:  # 혹시 모를 경계 처리(문제 스펙상 필요 없을 수도)
        return "00:00:00"

    end = adv-1
    if end <= play:
        max_sum = prefix[end]
        best_start = 0

    for start in range(1, play-adv+1):
        end = start + adv - 1
        cur_sum = prefix[end] - prefix[start-1]
        if cur_sum > max_sum:
            max_sum = cur_sum
            best_start = start

    return to_time(best_start)




