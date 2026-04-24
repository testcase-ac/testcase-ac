# Generates a worst-case test for the given wrong solution causing TLE due to excessive duplicate scanning
# N up to 2000. Use many zeros and balanced -1 and 1 so that many pairs sum to 0 (which has many duplicates).
# Composition: 666 x -1, 668 x 0, 666 x 1 (total 2000)

def main():
    N = 2000
    neg_ones = 666
    zeros = 668
    pos_ones = 666
    arr = [-1] * neg_ones + [0] * zeros + [1] * pos_ones
    print(N)
    print(' '.join(map(str, arr)))

if __name__ == "__main__":
    main()
