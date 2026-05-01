# Generates a small test that triggers out-of-bounds access in the wrong solution
# The wrong code allocates arrays of size [200][200] but indexes from 1..M and 1..N inclusive,
# so setting M >= 201 or N >= 201 causes out-of-bounds. We choose M=201, N=1 for minimal size.

def main():
    M, N = 201, 1
    print(f"{M} {N}")
    # Each of the M lines must contain exactly N digits (1..9). Use '9'.
    for _ in range(M):
        print("9")

if __name__ == "__main__":
    main()
