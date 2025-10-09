from collections import defaultdict
"""
말판 terms + today(가능세계)
말 - 하나의 개인정보 privacies(말들)

말판에 말의 부분 (+ 1 )
   1) 년/월/일, 2) 조항 종류 

조항을 키로하여 
terms의 유효기간을 찾고, 

말의 계약일 + 유효기간과 today를 비교하는 - 컷 판정을 진행한다. (즉, 프레임은 별도로 없다.)
하지만, 비교를 위해 단위를 days 수로 통일해야할 필요가 있다. 

변환 시 주의 
- 모든 달은 28일까지 있다고 가정합니다.

 이때 파기해야 할 개인정보의 번호를 오름차순으로 1차원 정수 배열에 담아 return 하도록 solution 함수를 완성해 주세요.
 
 A라는 약관의 유효기간이 12 달이고, 
 2021년 1월 5일에 수집된 개인정보가 A약관으로 수집되었다면 
 해당 개인정보는 2022년 1월 4일까지 보관 가능하며 2022년 1월 5일부터 파기해야 할 개인정보입니다.

"""

def todays(s):
    y,m,d=map(int,s.split('.'))
    return (y-0)*12*28+(m-1)*28+(d-1)+1

def ex_date(계약일숫자,조항기간숫자):
    return 계약일숫자+조항기간숫자-1

def judge(계약일문자, 오늘문자,조항기간월단위숫자):
    계약일숫자=todays(계약일문자)
    오늘숫자=todays(오늘문자)
    #조항기간숫자 = int(조항기간월단위숫자)*12
    조항기간숫자 = int(조항기간월단위숫자)*28
    유효일자숫자 = ex_date(계약일숫자, 조항기간숫자)
    print("유효일자숫자",유효일자숫자)
    print("오늘숫자",오늘숫자)
    print((유효일자숫자 >= 오늘숫자))
    return (유효일자숫자 >= 오늘숫자)


def solution(today, terms, privacies):
    
    terms_dict = defaultdict(int)
    answer=[]
    오늘문자=today
    
    for t in terms:
        temp=t.split()
        조항문자=temp[0]
        조항기간월단위숫자=int(temp[1])
        terms_dict[조항문자]=조항기간월단위숫자

    
    for i in range(len(privacies)):
        p=privacies[i]
        temp= p.split()
        계약일문자=temp[0]
        조항문자=temp[1]
        조항기간월단위숫자=terms_dict[조항문자]
        print("조항기간 월",조항기간월단위숫자)
        if not judge(계약일문자,오늘문자,조항기간월단위숫자):
            answer.append(i+1)
            
    answer.sort()
    print(answer)
            
    
        
    
    return answer