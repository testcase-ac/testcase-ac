# Generates a test where the number of maximum-length paths exceeds 1e9+7,
# but the wrong solution prints the raw count without modulo.
# Construction: two layers with y=0 and y=1, and disjoint x ranges.
# Any pair (x from layer 0, x from layer 1) forms a valid jump, so
# max length = 2 and number of ways = A*B > 1e9+7.

def main():
    A = 60000
    B = 60000
    n = A + B
    print(n)
    # Layer 1: y = 0, x = 1..A
    for i in range(1, A + 1):
        print(i, 0)
    # Layer 2: y = 1, x = A+1..A+B
    for i in range(1, B + 1):
        print(A + i, 1)

if __name__ == "__main__":
    main()
