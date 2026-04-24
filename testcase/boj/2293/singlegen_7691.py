# Generates a testcase that exposes negative indexing bug in the wrong solution
# Coins 1..100, target k=100. Correct answer is p(100)=190569292, but
# the wrong solution accesses dp[j - coin] for j < coin, reading before array
# and will most likely produce a wrong result.

print("100 100")
for i in range(1, 101):
    print(i)
