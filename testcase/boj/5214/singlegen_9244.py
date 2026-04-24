import sys

def main():
    # Stress test to trigger MLE/TLE in the wrong solution due to O(M*K^2) edge construction
    # N stations, K=1000 per hyper tube, M=1000 hyper tubes
    # Each hyper tube contains the same 1000 distinct stations, causing massive duplicate edges
    N, K, M = 1000, 1000, 1000
    out = sys.stdout
    out.write(f"{N} {K} {M}\n")
    line = ' '.join(map(str, range(1, K + 1)))
    for _ in range(M):
        out.write(line + "\n")

if __name__ == "__main__":
    main()
