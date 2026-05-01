# This test maximizes runtime for the wrong solution by avoiding collisions and forcing step-by-step movement
# R=C=100, M=10000, every cell has a shark with speed 1000 and direction right (3).
# With identical direction and speed per row, movement is a bijection on columns, so no collisions occur.
# The wrong solution simulates each of the 10000 sharks with 1000 unit steps for each of 100 columns => ~1e9 iterations => TLE.

def main():
    R, C = 100, 100
    M = R * C
    print(R, C, M)
    z = 1
    s = 1000
    d = 3  # right
    for r in range(1, R + 1):
        for c in range(1, C + 1):
            print(r, c, s, d, z)
            z += 1

if __name__ == "__main__":
    main()
