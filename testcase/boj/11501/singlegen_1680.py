print(1)
N = 1000000
print(N)
ls = [1 for _ in range(N-1)]
ls.append(10000)
print(' '.join(str(i) for i in ls))
