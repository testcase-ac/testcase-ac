# Generate a “maximum” testcase for n=100, m=100000
n = 100
m = 100000
print(n)
print(m)
cnt = 0
# We have at most 100*99 = 9900 distinct directed edges i->j (i!=j).
# To reach m=100000 we simply repeat printing that full set until we hit 100000.
for rep in range(11):         # 11 * 9900 = 108900 ≥ 100000
    for i in range(1, n+1):
        for j in range(1, n+1):
            if i == j:
                continue
            print(i, j, 100000)
            cnt += 1
            if cnt == m:
                break
        if cnt == m:
            break
    if cnt == m:
        break
