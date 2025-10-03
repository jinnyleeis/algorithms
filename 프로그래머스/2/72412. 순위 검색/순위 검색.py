
# * [조건]을 만족하는 사람 중 코딩테스트 점수를 X점 이상 받은 사람은 모두 몇 명인가?
"""
지원서에 입력한 4가지의 정보와 획득한 코딩테스트 점수를 하나의 문자열로 구성한 값의 배열 info
개발팀이 궁금해하는 [문의조건이 문자열 형태로 담긴 배열 query]가 매개변수
각 문의조건에 해당하는 사람들의 숫자를 순서대로 배열에 담아 return 하도록

4개 조건(언어/직군/경력/소울푸드) 중 어떤 건 정확히 매칭, 어떤 건 상관없음(‘-’) 이 섞여 있음.
이걸 쿼리 시점에 매번 “해당하는 모든 사람”을 선형 검색으로 찾으면 느리니까, 
미리 인덱스를 만들어 두기. 

100프로 매칭 혹은 와일드카드 매칭이고, 해당 사람의 점수보다 더 이하의 점수를 
기준으로 두었을 때, 해당 사람은 해당 쿼리 조건을 만족할 거니까.
"""
from collections import defaultdict # 튜플 키 - value score로 관리하기 위해.

from bisect import bisect_left # 이분 탐색 간편화를 위해.
# idx = bisect_left(scores, x)

from itertools import combinations # 와일드 카드 위치 지정 후 조합 생성 위해 2^4의.


def solution(info, query):
    answer = []
    # 1) 전처리: 4개 속성의 모든 와일드카드 조합을 key로 만들고, 각 key에 점수 append
    db = defaultdict(list)  # []
    for row in info:
        temp_lang, temp_job, temp_career, temp_food, temp_score = row.split()
        temp_score = int(temp_score)
        temp_attrs = [temp_lang, temp_job, temp_career, temp_food]
        
        # 인덱스 위치xx 몇 '개'를 - 와일드카드로 만들지.
        for i in range(0,5):
            """
            네 개 속성 중에서 r개 위치를 뽑음. (combinations 활용)
            range(4) = [0,1,2,3]
            ex. r=2일 때 → (0,1), (0,2), (0,3), (1,2), (1,3), (2,3)
            """
            for idxs in combinations(range(0,4),i):
                key = temp_attrs[:] # 현재 지원자의 속성 배열을 복사 - 와일드 카드등해서 변환하면서 
                # 인덱스 생성할 용도로 
                for i in idxs: # 해당 위치 변환 
                    key[i] = '-'
                    # 리스트를 -> 튜플화해서 키로 활용.
                db[tuple(key)].append(temp_score)
    for key in db.keys(): #db.key() → ❌
        db[key].sort()
                
    for row in query:
            temp_lang, temp_job, temp_career, temp_food, temp_score = row.replace(" and ", " ").split(" ")
            # db[tuple([temp_lang, temp_job, temp_career, temp_food])] - key error가능성
            scores = db.get(tuple([temp_lang, temp_job, temp_career, temp_food]),[])
            
             # scores 는 오름차순 정렬, x 이상인 첫 위치를 bisect_left로 찾기
            idx = bisect_left(scores, int(temp_score)) # TypeError: '<' not supported between instances of 'int' and 'str'

            answer.append(len(scores) - idx)


    
   
    return answer