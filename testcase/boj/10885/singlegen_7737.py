# Generator to break the wrong solution by exploiting comparison of modulo values instead of real magnitudes.
# We construct two non-zero segments separated by a zero:
#   - First segment has K copies of 2 (product = 2^K)
#   - Second segment has B copies of 2 (product = 2^B)
# We choose K > B but with (2^K mod MOD) < (2^B mod MOD).
# The correct answer is 2^K mod MOD, but the wrong code picks max by modulo value
# and will incorrectly choose 2^B mod MOD.

def main():
    MOD = 10**9 + 7
    # Try a few B values and find a K <= 100000 such that pow(2,K,MOD) < pow(2,B,MOD)
    # with K > B (so actual magnitude 2^K > 2^B).
    for B in [20, 25, 30, 15, 10, 5]:
        thr = pow(2, B, MOD)
        found = None
        for K in range(B + 1, 100001):
            if pow(2, K, MOD) < thr:
                found = K
                break
        if found is not None:
            K = found
            N = K + 1 + B
            arr = [2] * K + [0] + [2] * B
            print(1)
            print(N)
            print(' '.join(map(str, arr)))
            return

    # Fallback exhaustive search (very unlikely to be needed)
    for B in range(1, 61):
        thr = pow(2, B, MOD)
        found = None
        for K in range(B + 1, 100001):
            if pow(2, K, MOD) < thr:
                found = K
                break
        if found is not None:
            K = found
            N = K + 1 + B
            arr = [2] * K + [0] + [2] * B
            print(1)
            print(N)
            print(' '.join(map(str, arr)))
            return

    # Last-resort simple case (should never execute)
    B = 1
    K = 2
    N = K + 1 + B
    arr = [2] * K + [0] + [2] * B
    print(1)
    print(N)
    print(' '.join(map(str, arr)))

if __name__ == '__main__':
    main()
