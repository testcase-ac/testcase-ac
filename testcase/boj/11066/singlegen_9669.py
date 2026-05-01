# This generator creates a single test case with many large chapters.
# The wrong solution initializes l = 10,000,000 as the INF for DP split cost,
# which is too small. For sufficiently large K, the true minimal split cost part
# (dp_left + dp_right) exceeds 10,000,000, so the solution clamps it to 10,000,000,
# underestimating the true cost and producing a wrong answer.
# K=200 with all sizes=10000 reliably triggers this.

def main():
    t = 1
    n = 200
    print(t)
    print(n)
    print(" ".join(["10000"] * n))

if __name__ == "__main__":
    main()
