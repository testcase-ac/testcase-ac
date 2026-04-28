n, k, x = map(int, input().split())
mod = 998244353
ans = (x * (x + 1) // 2) ** 2
ans = (ans * k) % mod
ans = (ans * pow(x, n + k - 2, mod)) % mod
print(' '.join([str(ans) for _ in range(n - k + 1)]))
