# Generates a worst-case TLE-inducing test for the wrong O(M*N) solution
# Problem: IOIOI (count occurrences of P_N in S)
# This test sets N close to M/2 and S as all 'I's, causing the wrong
# solution to perform ~O(M^2) checks and likely time out.

def main():
    N = 499_999  # 2N+1 = 999,999
    M = 1_000_000
    print(N)
    print(M)
    print('I' * M)

if __name__ == "__main__":
    main()
