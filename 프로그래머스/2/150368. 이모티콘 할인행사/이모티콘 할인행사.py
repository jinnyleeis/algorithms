from collections import defaultdict
from itertools import product

def 할인율적용계산(가격, 할인율):
    return int(가격 * (100 - 할인율) / 100)

def solution(users, emoticons):
    # --- 전처리판: 이모티콘별 할인율→할인가 테이블 ---
    임티할인케이스들 = defaultdict(dict)
    할인율케이스들 = [10, 20, 30, 40]
    for i, e in enumerate(emoticons, start=1):
        for s in 할인율케이스들:
            임티할인케이스들[i][s] = 할인율적용계산(e, s)

    # --- 심판판: 모든 할인 배치를 전수탐색하여 전체 합산 ---
    # best는 (가입자수, 매출) 튜플로 관리 — 튜플 비교로 1순위 가입자, 2순위 매출을 동시에 최적화
    best_subs, best_revenue = -1, -1

    # 이모티콘 m개 각각에 4가지 할인율 → 4^m 모든 배치를 전수
    for 할인배치 in product(할인율케이스들, repeat=len(emoticons)):
        total_subs = 0
        total_revenue = 0

        # 배치에 대해 모든 유저 평가
        for 비율, 가격 in users:
            user_sum = 0
            # 현재 배치에서 유저가 사는 이모티콘 금액 합
            for idx, disc in enumerate(할인배치, start=1):
                if disc >= 비율:
                    user_sum += 임티할인케이스들[idx][disc]

            # 기준 가격 이상이면 구독 전환(매출 0), 아니면 구매 유지(매출 += user_sum)
            if user_sum >= 가격:
                total_subs += 1
            else:
                total_revenue += user_sum

        # 최적 갱신 (1순위: 가입자 수, 2순위: 매출)
        if (total_subs, total_revenue) > (best_subs, best_revenue):
            best_subs, best_revenue = total_subs, total_revenue

    return [best_subs, best_revenue]
