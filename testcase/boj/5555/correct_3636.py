s = input()
ans = 0
for i in range(int(input())):
    t = input()
    t += t
    if s in t:
        ans += 1
print(ans)
