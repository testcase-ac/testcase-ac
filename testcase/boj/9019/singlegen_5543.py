# Generate a “stress” input for the DSLR problem:
# – Max out the number of test-cases (assume T can go up to 10_000).
# – Use every A in [0…9999], paired with a B that is “far away” ((A+5000)%10000).
# This forces the solver to run a full BFS from nearly every node.
T = 10_000
print(T)
for a in range(T):
    b = (a + 5000) % 10000
    # ensure A ≠ B
    if a == b:
        b = (b + 1) % 10000
    print(a, b)
