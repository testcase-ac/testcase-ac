# generator for a worst-case input: every haybale has flavor 1, spiciness 1,
# N is maximum (100000) and the required flavor M is 1.
# For this instance every contiguous interval is feasible, so the wrong
# program explores an exponential number of sub-intervals and times out.

def main():
    N = 100000
    M = 1
    print(f"{N} {M}")
    one_line = "1 1"
    for _ in range(N):
        print(one_line)

if __name__ == "__main__":
    main()
