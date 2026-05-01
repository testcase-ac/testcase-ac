# Generates a test case that exploits uninitialized indices in the wrong C solution.
# A is all 100 (so min search never updates a1) and B is all 0 (so max search never updates b1),
# leading to undefined behavior (likely runtime error or wrong result).

def main():
    n = 50
    A = [100] * n
    B = [0] * n
    print(n)
    print(' '.join(map(str, A)))
    print(' '.join(map(str, B)))

if __name__ == "__main__":
    main()
