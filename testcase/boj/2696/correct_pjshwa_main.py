import sys
import heapq as hq

input = sys.stdin.readline
R = int(input())
for _ in range(R):
    N = int(input())
    arr = []
    for _ in range((N - 1) // 10 + 1): arr.extend(list(map(int, input().split())))

    left_max = []
    right_min = []
    count = 0
    tenth_check = 0
    res = []
    for i in range(N):
        num = arr[i]
        if len(left_max) == len(right_min): #최대힙 left 생성
            hq.heappush(left_max, (-num, num))
        else:
            hq.heappush(right_min, (num, num)) #최소힙 right 생성
        if right_min and right_min[0][1] < left_max[0][1]: #최대힙(left)의 루트가 중앙값 최소힙의 루트보다 크면 바꾸기
            maxx = hq.heappop(left_max)[1]
            minn = hq.heappop(right_min)[1]
            hq.heappush(right_min, (maxx, maxx))
            hq.heappush(left_max, (-minn, minn))
        if i % 2 == 0:
            count += 1 #중앙값 출력 갯수
            res.append(left_max[0][1])
    print(count)
    for median in res:
        print(median, end = " ")
        tenth_check += 1
        if tenth_check == 10: #열번 출력했다면
            print()
            tenth_check = 0
    print()
