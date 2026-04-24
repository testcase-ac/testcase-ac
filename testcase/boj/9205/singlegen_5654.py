# Generate a maximal test file for the beer‐walking problem.
# t = 50 test cases, each with n = 100 convenience stores.
# We snake around inside the allowed coordinate box (|coord| ≤ 32767),
# taking exactly 1000m (Manhattan) per segment so that each leg is feasible.

def gen():
    t = 50
    print(t)
    for _ in range(t):
        n = 100
        print(n)
        # start at (0, 0)
        x, y = 0, 0
        print(x, y)
        # 100 stores, each step is (Δx, Δy) = (300, ±700) so |Δx|+|Δy| = 1000
        for i in range(1, n+1):
            if i % 2 == 1:
                x += 300
                y += 700
            else:
                x += 300
                y -= 700
            print(x, y)
        # festival one more 1000m step
        x += 300
        y += 700
        print(x, y)

if __name__ == '__main__':
    gen()
