from bisect import bisect_left, bisect_right
from collections import defaultdict

def solution(words, queries):
    # 1) 길이별 버킷과 뒤집은 버킷
    bucket = defaultdict(list)
    rbucket = defaultdict(list)
    for w in words:
        L = len(w)
        bucket[L].append(w)
        rbucket[L].append(w[::-1])

    # 2) 길이별 사전순 정렬
    for L in bucket.keys():
        bucket[L].sort()
        rbucket[L].sort()

    # 3) 접두사 구간 개수 세는 함수
    def count_with_prefix(sorted_list, prefix, L):
        # prefix 길이 p, 나머지(L-p)를 'a'~'z'로 채운 범위를 잡아 개수 세기
        p = len(prefix)
        lo = prefix + 'a' * (L - p)
        hi = prefix + 'z' * (L - p)
        return bisect_right(sorted_list, hi) - bisect_left(sorted_list, lo)

    # 4) 쿼리 처리 + 캐싱
    cache = {}
    ans = []
    for q in queries:
     #   if q in cache:
      #      ans.append(cache[q])
       #     continue

        L = len(q)
        if L not in bucket:
            #cache[q] = 0
            ans.append(0)
            continue

        if q[0] != '?':  # 접미 '?' → 접두사 고정
            prefix = q.split('?')[0]
            res = count_with_prefix(bucket[L], prefix, L)
        else:            # 접두 '?' → 접미사 고정 == 뒤집어서 접두사 검색
            prefix = q[::-1].split('?')[0]  # 뒤집은 쿼리의 접두사
            res = count_with_prefix(rbucket[L], prefix, L)

        #cache[q] = res
        ans.append(res)

    return ans
