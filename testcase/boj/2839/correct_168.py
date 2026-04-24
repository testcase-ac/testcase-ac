# 다이나믹 프로그래밍으로 12 미만의 값들을 미리 구함

DP_list = [0, -1,-1, 1,-1, 1,
               2,-1, 2, 3, 2, 3]

# 12 이후로는 값들이 규칙적으로 변함

mod_list = [0, 1, 2, 1, 2]
n = int(input())

if n < 12: print(DP_list[n])
else: print( n//5 + mod_list[n%5] )