import re
from collections import defaultdict 

# 전처리판

# 1. 키워드 수 추출

def 인덱스페이지명매핑(인덱스,페이지내용,매핑딕셔너리):
    라인들=페이지내용.splitlines()
    for l in 라인들:
        # content="..."/> 또는 content="..." /> 모두 매칭
        m = re.search(r'<meta property="og:url" content="([^"]+)"\s*/?>', l)
        if m:
            페이지주소=m.group(1)
            매핑딕셔너리[페이지주소]=인덱스

def 키워드수추출(인덱스,페이지내용, 키워드,기본점수딕셔너리):
    pattern = r'(?<![A-Za-z])' + 키워드.lower() + r'(?![A-Za-z])'
    matches = re.findall(pattern, 페이지내용.lower())
    키워드수=len(matches)
    print(키워드수)
    기본점수딕셔너리[인덱스]=키워드수

def 외부링크수추출(인덱스,페이지내용,외부링크수딕셔너리):
    라인들=페이지내용.splitlines()
    for l in 라인들:
        # 한 줄에 여러 <a> 있을 수 있으므로 findall로 전부 카운트
        matches = re.findall(r'<a href="https://[^"]+"', l)
        if matches:
            외부링크수딕셔너리[인덱스] += len(matches)

def 링크점수추출(인덱스,페이지내용,링크점수딕셔너리,기본점수딕셔너리,외부링크수딕셔너리):
    outdeg = 외부링크수딕셔너리[인덱스]
    if outdeg == 0:
        링크점수 = 0.0
    else:
        링크점수 = 기본점수딕셔너리[인덱스] / outdeg
    링크점수딕셔너리[인덱스]=링크점수

def 매칭점수계산(인덱스,페이지내용):
    라인들=페이지내용.splitlines()
    for l in 라인들:
        m = re.search(r'<a href="(.*)"/>', l)
        if m:
            페이지주소=m.group(1)
            [매핑딕셔너리[페이지주소]]

# ---------------------
# 심판판 

def solution(word, pages):
    매핑딕셔너리=defaultdict(int)
    기본점수딕셔너리=defaultdict(float)
    외부링크수딕셔너리=defaultdict(float)
    링크점수딕셔너리=defaultdict(float)
    매칭점수딕셔너리=defaultdict(float)
    참조당하는기록딕셔너리=defaultdict(list)
    
    for i in range(len(pages)):
        p=pages[i]
        인덱스페이지명매핑(i,p,매핑딕셔너리)
        외부링크수추출(i,p,외부링크수딕셔너리)
        키워드수추출(i,p,word,기본점수딕셔너리)
        링크점수추출(i,p,링크점수딕셔너리,기본점수딕셔너리,외부링크수딕셔너리)

    print("매핑",매핑딕셔너리)
    print("기본",기본점수딕셔너리)
    print("각 링크점수",링크점수딕셔너리)
    
    # 참조당하는수추출----
    for i in range(len(pages)):
        print("-----페이지별--- ",i)
        p=pages[i]
        라인들=p.splitlines()
        for l in 라인들:
            # 한 줄에 여러 링크 가능 → 모두 수집
            링크들 = re.findall(r'<a href="(https://[^"]+)"', l)
            for 페이지주소 in 링크들:
                print(페이지주소,"와 매핑발견")
                if 페이지주소 in 매핑딕셔너리.keys():
                    연결페이지인덱스=매핑딕셔너리[페이지주소]
                    참조당하는기록딕셔너리[연결페이지인덱스].append(i)
                
    print("참조당하는기록",참조당하는기록딕셔너리)

    for i in range(len(pages)):
        print("-----페이지별--- ",i)
        p=pages[i]
        매칭점수딕셔너리[i]=기본점수딕셔너리[i]
        for 참조페이지 in 참조당하는기록딕셔너리[i]:
            누적될값=링크점수딕셔너리[참조페이지]
            print("초기매칭점수값",매칭점수딕셔너리[i],"누적될값",링크점수딕셔너리[참조페이지])
            매칭점수딕셔너리[i]=매칭점수딕셔너리[i]+누적될값
            print(매칭점수딕셔너리[i])
        print("-----끝--- ",i)       

    for i in 매칭점수딕셔너리:
        print("매칭점수내용",i,매칭점수딕셔너리[i])
            
    res = sorted(매칭점수딕셔너리.items(), key=lambda x: (-x[1], x[0]))
    print(res)

    answer=res[0][0]
    return answer

