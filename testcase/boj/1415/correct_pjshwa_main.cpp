#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, MAXV = 500'000;
int a[MAX], t[MAXV];
ll d[2][MAXV + 1];

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  int n;
  cin >> n;

  set<int> s;
  for (int i = 0; i < n; i++) cin >> a[i], t[a[i]]++, s.insert(a[i]);

  int i = 0;
  for (auto k : s) a[++i] = k;
  n = s.size();

  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int s = 0; s <= MAXV; s++) d[i & 1][s] = 0;
    for (int s = 0; s <= MAXV; s++) {
      for (int j = 0; j <= t[a[i]] && s + a[i] * j <= MAXV; j++) {
        d[i & 1][s + a[i] * j] += d[(i & 1) ^ 1][s];
      }
    }
  }

  ll ans = 0;
  for (int s = 0; s <= MAXV; s++) {
    if (is_prime(s)) ans += d[n & 1][s];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
