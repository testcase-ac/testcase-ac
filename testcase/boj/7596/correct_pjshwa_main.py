import sys
r = sys.stdin.readline

n = int(r())
idx = 1
while(n != 0):
    songs_list = []
    for _ in range(n):
        songs_list.append(r().rstrip())
    songs_list.sort()
    print(idx)
    for item in songs_list: print(item)
    n = int(r())
    idx += 1