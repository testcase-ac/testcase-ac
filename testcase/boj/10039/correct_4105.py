
ls = []
for i in range(5):
    ls.append(int(input()))
print(sum([(i if i>=40 else 40) for i in ls])//5)
