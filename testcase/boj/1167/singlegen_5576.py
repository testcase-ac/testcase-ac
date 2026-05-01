V = 5000
W = 10000

print(V)
for i in range(1, V + 1):
    # Each line: vertex number, then pairs (neighbor weight), ending with -1
    line = [str(i)]
    if i > 1:
        line += [str(i-1), str(W)]
    if i < V:
        line += [str(i+1), str(W)]
    line.append("-1")
    print(" ".join(line))
