#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5 + 10, MOD = 1e9 + 7;
int F[MAX + 1];

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ans = (ans + F[__gcd(i + 1, N + 1)]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  F[1] = 1;
  for (int i = 2; i <= MAX; i++) F[i] = (F[i - 1] + F[i - 2]) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
