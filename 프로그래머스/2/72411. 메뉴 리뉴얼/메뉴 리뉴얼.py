"""
 이전에 각 손님들이 주문할 때 가장 많이 함께 주문한 단품메뉴들을 코스요리 메뉴로 구성하기로

-  최소 2가지 이상의 단품메뉴로 구성
-  최소 2명 이상의 손님으로부터 주문된 [단품메뉴 조합]에 대해서만 코스요리 메뉴 후보에 포함

- 각 조합에 같이 포함되어있기만 하면 됨.
해당 조합은 2개 이상
조합 a 가 조합 b 내에 포함되어 있어도 됨


각 손님들이 [주문한 단품메뉴들]이 문자열 형식으로 담긴 배열 orders
추가하고 싶어하는 코스요리를 구성하는 단품메뉴들의 [갯수]가 담긴 배열 course

새로 추가하게 될 코스요리의 메뉴 구성을 문자열 형태로 배열에 담아 return 

-----------------------------------------------------------------

정답은 각 코스요리 메뉴의 구성을 문자열 형식으로 배열에 담아 
사전 순으로 오름차순 정렬해서 return

배열의 각 원소에 저장된 문자열 또한 
알파벳 오름차순으로 정렬되어야 합니다.

만약 가장 많이 함께 주문된 메뉴 구성이 여러 개라면, 
모두 배열에 담아 return 하면 됩니다.

orders와 course 매개변수는 
return 하는 배열의 길이가 1 이상이 되도록 주어집니다.
"""

from itertools import combinations
from collections import Counter
    

def solution(orders, course):
    answer=[]
    raw_combi = []
    # 조합을 만들자. 각 그것에 대해. 
    for n in course:
        for e in orders:
             if len(e) >= n:  
                e=sorted(e)
                raw_combi.extend(combinations(e,n))
            
    #print(raw_combi)
    
    res = Counter(raw_combi)
    for c in course:
        # 길이가 c인 조합만 추리기 -> 이유? 그 길이에서의 최빈값을 추리기 위해
        candidates = [comb for comb, cnt in res.items() if len(comb) == c]
        if not candidates:
            continue
            
        # 최대 등장 빈도. 문자의 길이 최대가 아닌.
        max_candidates_per_c = max([res[comb] for comb in candidates])
        
        # 해당 최대 등장빈도에 해당하는 해당 c 길이의 요소들 
        # answer 배열에 담기
        if max_candidates_per_c >=2:
            for comb in candidates:
                if res[comb] == max_candidates_per_c:
                    answer.append("".join(comb))
                    
    # 인덴트 위치 주의
    return sorted(answer)
            
        
    #print(res)
    
            
    
            
    

    return answer