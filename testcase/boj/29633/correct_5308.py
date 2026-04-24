from fractions import Fraction

dp = [[Fraction(0) for _ in range(51)] for _ in range(201)]
choices = [[] for _ in range(201)]

def main():    
    M = int(input())
    K = int(input())
    
    dp[1][1] = Fraction(1, 1)
    for k in range(2, K+1):
        dp[1][k] = Fraction(0, 1)
    choices[1] = [1]

    for n in range(2, M+1):
        cur_choice = choices[n]
        for t in range(1, n+1):
            tmp = Fraction(1, n) + Fraction(t-1, n) * dp[t-1][2] + Fraction(n-t, n) * dp[n-t][2]
            if tmp > dp[n][1]:
                dp[n][1] = tmp
                cur_choice = [t]
            elif tmp == dp[n][1]:
                cur_choice.append(t)
        choices[n] = cur_choice

        for k in range(2, K+1):
            nxt_k = 1 if k == K else k+1
            for t in cur_choice:
                dp[n][k] += Fraction(t-1, n) * dp[t-1][nxt_k] + Fraction(n-t, n) * dp[n-t][nxt_k]
            dp[n][k] = dp[n][k] * Fraction(1, len(cur_choice))

    for i in range(1, M+1):
        print(len(choices[i]), end=" ")
        for x in choices[i]:
            print(x, end=" ")
        print()

if __name__ == "__main__":
    main()
