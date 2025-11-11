from typing import List, Tuple

def solution(N: int, stages: List[int]) -> List[int]:
    # A. 말판: 1..N(+1) 전 좌표를 깔아 빈 칸도 포함
    stay = [0]*(N+2)                      # stay[i] = i에 멈춘 사람 수
    for s in stages:
        #if 1 <= s <= N+1:
        stay[s] += 1
    print(stay)

    # B. 초기 배치: 레이스 중인 전체 말 수
    remain = len(stages)
    rates: List[Tuple[int, float]] = []   # (stage, rate)

    # C. 전수 스윕: 게이트 1→N 심판
    for i in range(1, N+1):
        fail_rate = (stay[i] / remain) if remain > 0 else 0.0
        rates.append((i, fail_rate))
        remain -= stay[i]                 # 다음 게이트로 넘어가며 남은 말 갱신 ( 현재 말고 다음을 이한)

    # D. 결승선 판독: 정렬 (실패율 desc, 번호 asc)
    rates.sort(key=lambda t: (-t[1], t[0]))
    return [i for i, _ in rates]



