# Generate a maximum‐size test for the LCA‐on‐tree problem:
# N = 100 000 nodes in a simple chain (1–2–3–…–100000),
# M = 100 000 queries pairing i with (N−i+1), to exercise deep/flat LCAs.

N = 100000
print(N)
# tree edges: a simple path (chain)
for i in range(1, N):
    print(i, i+1)

M = 100000
print(M)
# queries: (1,100000), (2,99999), …, (100000,1)
for i in range(1, M+1):
    print(i, N - i + 1)
