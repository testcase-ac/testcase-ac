# This generator creates a 20x20 grid with all 1's except the bottom-right cell is 0.
# For this grid, the number of valid paths equals C(38, 19) = 35345263800,
# which exceeds 32-bit int range and causes the wrong solution (which uses int dp) to overflow.

def main():
    N = 20
    print(N)
    for i in range(N):
        row = []
        for j in range(N):
            if i == N - 1 and j == N - 1:
                row.append('0')
            else:
                row.append('1')
        print(' '.join(row))

if __name__ == "__main__":
    main()
