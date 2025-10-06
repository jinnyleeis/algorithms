from itertools import combinations                               # L01
from collections import defaultdict                              # L02

def solution(orders, course):                                    # L03
    """
    메뉴 리뉴얼: 주문 문자열들에서 course 길이별로
    가장 많이 함께 주문된 조합을 뽑아 사전순 반환.
    """                                                          # L04-06
    cs = set(course)                                             # L07
    foodMap = {k: defaultdict(int) for k in course}              # L08
    maxCnt  = {k: 0 for k in course}                             # L09

    # 주문 카운팅
    for s in orders:                                             # L10
        arr = sorted(s)                                          # L11
        for k in course:                                         # L12
            if k > len(arr):                                     # L13
                continue                                         # L14
            for comb in combinations(arr, k):                    # L15
                key = ''.join(comb)                              # L16
                foodMap[k][key] += 1                             # L17
                if foodMap[k][key] > maxCnt[k]:                  # L18
                    maxCnt[k] = foodMap[k][key]                  # L19

    # 후보 추출
    answer = []                                                  # L20
    for k in course:                                             # L21
        m = maxCnt[k]                                            # L22
        if m < 2:                                                # L23
            continue                                             # L24
        for key, val in foodMap[k].items():                      # L25
            if val == m:                                         # L26
                answer.append(key)                               # L27

    return sorted(answer)                                        # L28

# 샘플 실행
if __name__ == "__main__":                                       # L29
    ex1_orders = ["ABCFG","AC","CDE","ACDE","BCFG","ACDEH"]      # L30
    ex1_course = [2,3,4]                                         # L31
    print(solution(ex1_orders, ex1_course))                      # L32

    ex2_orders = ["ABCDE","AB","CD","ADE","XYZ","XYZ","ACD"]     # L33
    ex2_course = [2,3,5]                                         # L34
    print(solution(ex2_orders, ex2_course))                      # L35

    ex3_orders = ["XYZ","XWY","WXA"]                             # L36
    ex3_course = [2,3,4]                                         # L37
    print(solution(ex3_orders, ex3_course))                      # L38
