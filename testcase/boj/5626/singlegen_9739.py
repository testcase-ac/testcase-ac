# Generates a test case that triggers the wrong solution's out-of-bounds neighbor access logic
# Idea:
# - Use N = 5003.
# - Set all heights to -1 except the second-to-last position to 0.
#   This avoids the inner-loop for i > 5000 (preventing column OOB writes),
#   but still makes the code read dp[i-1][-1] at i=5002, which incorrectly
#   maps to dp[5000][5000] due to out-of-bounds indexing. That contaminates
#   the final answer without causing a crash.
# - Ends are left as -1 (the solution forcibly sets them to 0), which is valid.

def main():
    n = 5003
    arr = [-1] * n
    arr[-2] = 0  # set index 5001 to 0; others remain -1
    print(n)
    print(' '.join(map(str, arr)))

if __name__ == "__main__":
    main()
