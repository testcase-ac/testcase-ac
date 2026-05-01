# Generates a test case that breaks the provided wrong solution.
# The wrong solution, for n >= 100000, outputs indices based only on the first two values.
# We provide n=100000 with alternating values 0 and 1 starting with 0 < 1.
# Correct compression should alternate 0 and 1, but the wrong solution will output 0..99999.

def main():
    n = 100000
    arr = [(i % 2) for i in range(n)]  # 0,1,0,1,...
    print(n)
    print(' '.join(map(str, arr)))

if __name__ == "__main__":
    main()
