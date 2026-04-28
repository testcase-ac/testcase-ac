import sys;r=sys.stdin.readline;mush_list=[];s=0
for _ in range(10): mush_list.append(int(r()))
for i in range(10):
    if abs(100-s)>=abs(100-s-mush_list[i]):s+=mush_list[i]
    else:break
print(s)