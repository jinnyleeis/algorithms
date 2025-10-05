

# ---st/cmp 두 포인터 스타일 버전 ---
def solution(s: str) -> int:
    """
    st/cmp(=다음 블록 시작) 두 포인터로 같은 로직 구현.
    """
    n = len(s)
    if n == 1:
        return 1

    best = n
    for k in range(1, n // 2 + 1):
        st = 0
        compressed_len = 0

        while st < n:
            # 현재 블록
            block = s[st:st + k]
            # 꼬리(길이<k)는 비교 대상이 될 '완전한' 다음 블록이 없음
            # → 반복 카운트는 최소 1부터 시작
            count = 1

            # 다음 블록 시작점
            cmp_idx = st + k
            # 완전한 블록끼리만 비교
            while cmp_idx + k <= n and s[cmp_idx:cmp_idx + k] == block:
                count += 1
                cmp_idx += k

            # 길이 누적: count>1이면 숫자+블록, 아니면 블록만
            # 이때 block 길이는 k가 아니라 실제 남은 길이(min(k, n-st)) 사용
            # (문자열 끝에서 꼬리일 수 있으므로)
            block_len = min(k, n - st)
            compressed_len += (len(str(count)) if count > 1 else 0) + block_len

            # 다음 run으로 이동
            st = cmp_idx

        best = min(best, compressed_len)

    return best








