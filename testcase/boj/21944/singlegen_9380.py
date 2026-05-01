import sys

def main():
    out = sys.stdout
    N = 100000
    out.write(str(N) + "\n")
    # Distribute problems evenly across 100 algorithm groups, all with minimal difficulty 1
    for i in range(1, N + 1):
        P = i
        L = 1
        G = (i - 1) % 100 + 1
        out.write(f"{P} {L} {G}\n")
    M = 10000
    out.write(str(M) + "\n")
    # Heavy recommend3 queries that force scanning essentially all problems each time
    for _ in range(M):
        out.write("recommend3 1 1\n")

if __name__ == "__main__":
    main()
