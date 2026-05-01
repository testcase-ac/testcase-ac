# 출처: https://velog.io/@cria2000/백준-1515-수-이어-쓰기python
import sys
nums = sys.stdin.readline().rstrip()
n = 0
idx = 0
while True:
    n += 1
    for s in str(n):
        if nums[idx] == s:
            idx += 1
            if idx >= len(nums):
                print(n)
                exit()
