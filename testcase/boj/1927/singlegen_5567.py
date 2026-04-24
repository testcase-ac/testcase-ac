# Generate a max-sized test for the min-heap problem.
# N = 100000 operations: first 50000 pushes (1..50000), then 50000 pops (0).
print(100000)
for i in range(1, 50001):
    print(i)
for _ in range(50000):
    print(0)
