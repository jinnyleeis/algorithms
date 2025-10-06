from collections import defaultdict                               # L01
from bisect import bisect_left                                    # L02
from itertools import combinations                                # L03

def solution(info, query):                                        # L04
    answer = []                                                   # L05

    # 1) 전처리: 속성 4개의 모든 와일드카드 조합을 key로 만들고 점수 push
    db = defaultdict(list)                                        # L06
    for row in info:                                              # L07
        lang, job, career, food, score = row.split()              # L08
        score = int(score)                                        # L09
        attrs = [lang, job, career, food]                         # L10

        # r = 0..4개 위치를 '-'로 치환한 모든 조합(2^4) 생성
        for r in range(0, 5):                                     # L11
            for idxs in combinations(range(4), r):                # L12
                key = attrs[:]                                    # L13
                for pos in idxs:                                  # L14
                    key[pos] = '-'                                # L15
                db[tuple(key)].append(score)                      # L16

    # 2) 각 key의 점수 오름차순 정렬(이분 탐색 준비)
    for key in db.keys():                                         # L17
        db[key].sort()                                            # L18

    # 3) 질의 처리
    for row in query:                                             # L19
        lang, job, career, food, x = row.replace(' and ', ' ').split()  # L20
        x = int(x)                                                # L21
        key = (lang, job, career, food)                           # L22
        scores = db.get(key, [])                                  # L23

        # x 이상이 처음 나타나는 위치
        i = bisect_left(scores, x)                                # L24
        answer.append(len(scores) - i)                            # L25

    return answer                                                 # L26
