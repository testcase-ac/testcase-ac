# Generate a "maximum" test case for the hacking problem:
# N = 10 000, M = 100 000.
# We make a star so that only node 1 can hack all others (9 999 nodes),
# and then dump duplicate edges (2→1) to pad M up to 100 000
N = 10_000
M = 100_000
print(N, M)
# Star edges: for i = 2..N, i trusts 1
for i in range(2, N + 1):
    print(i, 1)
# Padding: duplicate edge (2, 1) to reach total M edges
pad = M - (N - 1)
for _ in range(pad):
    print(2, 1)
